#ifndef BEEPTHREAD_H
#define BEEPTHREAD_H

#include <QThread>
#include <QtWidgets>
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <Generator.h>
#include <QAudioOutput>
#include <QByteArray>
#include <QIODevice>
#include <PiecewiseLinearFunction.h>

#define DURATION_MS 1000
const int DataSampleRateHz = 44100;
const int BufferSize      = 32768;

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

class BeepThread : public QThread
{
    Q_OBJECT
public:
    explicit BeepThread(QObject *parent = 0);
    void run();

    void startBeep();
    void stopBeep();
    void resumeBeep();
    void setVolume(qreal volume);
    void SetVario(qreal vario, qreal tdiff);
    PiecewiseLinearFunction *m_varioFunction;
    PiecewiseLinearFunction *m_toneFunction;

private:
    void initializeAudio();
    void createAudioOutput();
    void SetFrequency(qreal value);

private:
    QAudioDeviceInfo m_device;
    Generator *m_generator;  
    Generator* tmp;
    QAudioOutput *m_audioOutput;
    QByteArray m_buffer;
    qreal m_vario;
    qreal m_tone;
    qreal m_tdiff;
    qreal m_outputVolume;
    bool m_running;
    qreal m_toneSampleRateHz;
    qreal m_durationUSeconds;
    QAudioFormat m_format;

signals:        
    void finished();
};

#endif // BEEPTHREAD_H
