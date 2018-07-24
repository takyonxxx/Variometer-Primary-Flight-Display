#ifndef GENERATOR_H
#define GENERATOR_H
#include <QtMath>
#include <QAudioFormat>
#include <QByteArray>
#include <QObject>
#include <QtEndian>
#include <QIODevice>

class Generator : public QIODevice
{
    Q_OBJECT

public:
    Generator(const QAudioFormat &format, qint64 durationUs, int sampleRate, QObject *parent);
    ~Generator();

    void start();
    void stop();   
    void generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate);

private:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;

private:
    qint64 m_pos;
    QByteArray m_buffer;
};

#endif // GENERATOR_H
