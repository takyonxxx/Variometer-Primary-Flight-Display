#include "BeepThread.h"

BeepThread::BeepThread(QObject *parent) :
    QThread(parent)
  ,   m_device(QAudioDeviceInfo::defaultOutputDevice())
  ,   m_generator(0)
  ,   tmp(0)
  ,   m_audioOutput(0)
  ,   m_buffer(BufferSize, 0)
  ,   m_vario(0.0)
  ,   m_tone(0.0)  
  ,   m_tdiff(0.0)
  ,   m_outputVolume(0.0)
  ,   m_running(false)
  ,   m_toneSampleRateHz(0)
  ,   m_durationUSeconds(0)
{
    m_toneSampleRateHz = 750.0;
    m_durationUSeconds = DURATION_MS * 1000.0;

    m_varioFunction = new PiecewiseLinearFunction();
    m_varioFunction->addNewPoint(QPointF(0, 0.4763));
    m_varioFunction->addNewPoint(QPointF(0.441, 0.3619));
    m_varioFunction->addNewPoint(QPointF(1.029, 0.2238));
    m_varioFunction->addNewPoint(QPointF(1.559, 0.1565));
    m_varioFunction->addNewPoint(QPointF(2.471, 0.0985));
    m_varioFunction->addNewPoint(QPointF(3.571, 0.0741));
    m_varioFunction->addNewPoint(QPointF(5.0, 0.05));

    m_toneFunction = new PiecewiseLinearFunction();
    m_toneFunction->addNewPoint(QPointF(0, m_toneSampleRateHz));
    m_toneFunction->addNewPoint(QPointF(0.25, m_toneSampleRateHz + 100));
    m_toneFunction->addNewPoint(QPointF(1.0, m_toneSampleRateHz + 200));
    m_toneFunction->addNewPoint(QPointF(1.5, m_toneSampleRateHz + 300));
    m_toneFunction->addNewPoint(QPointF(2.0, m_toneSampleRateHz + 400));
    m_toneFunction->addNewPoint(QPointF(3.5, m_toneSampleRateHz + 500));
    m_toneFunction->addNewPoint(QPointF(4.0, m_toneSampleRateHz + 600));
    m_toneFunction->addNewPoint(QPointF(4.5, m_toneSampleRateHz + 700));
    m_toneFunction->addNewPoint(QPointF(6.0, m_toneSampleRateHz + 800));

    SetFrequency(m_toneSampleRateHz);

    initializeAudio();
}

// run() will be called when a thread starts
void BeepThread::run()
{       
    while (m_running)
    {
        if(m_vario >= 0.25)
        {
            if(m_vario > 0)
            {
                m_tone = m_toneFunction->getValue(m_vario);
            }
            else if(m_vario < 0)
            {
                m_tone = m_toneSampleRateHz;
            }

            tmp = new Generator(m_format, m_durationUSeconds, m_tone, this);
            tmp->start();
            delete m_generator;
            m_generator = tmp;

            m_audioOutput->start(m_generator);
            Sleeper::msleep(m_varioFunction->getValue(m_vario) * 1000);
            m_audioOutput->suspend();
            Sleeper::msleep(m_varioFunction->getValue(m_vario) * 1000);
        }
    }
    emit finished();
}


void BeepThread::initializeAudio()
{
    m_format.setSampleRate(DataSampleRateHz);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(m_device);
    if (!info.isFormatSupported(m_format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }

    createAudioOutput();
}

void BeepThread::createAudioOutput()
{
    delete m_audioOutput;
    m_audioOutput = 0;
    m_audioOutput = new QAudioOutput(m_device, m_format, this);
}

void BeepThread::startBeep()
{
    SetFrequency(m_toneSampleRateHz);
    m_running = true;
}

void BeepThread::stopBeep()
{
    m_running = false;
    m_audioOutput->stop();
}

void BeepThread::resumeBeep()
{
    m_audioOutput->resume();
}

void BeepThread::setVolume(qreal volume)
{
    m_audioOutput->setVolume(qreal(volume/100.0f));
}

void BeepThread::SetVario(qreal vario, qreal tdiff)
{    
    if(m_vario != vario && m_running)
    {
        m_vario = vario;
        m_tdiff = tdiff;       
    }
}

void BeepThread::SetFrequency(qreal value)
{
    tmp = new Generator(m_format, m_durationUSeconds, value, this);
    tmp->start();
    delete m_generator;
    m_generator = tmp;
}

