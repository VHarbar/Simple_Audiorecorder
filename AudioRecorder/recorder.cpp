#include "recorder.h"
#include "ui_recorder.h"
#include <QAudioDeviceInfo>
#include <QAudio>
#include<QAudioRecorder>
#include<QAudioInput>
#include<QUrl>


Recorder::Recorder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Recorder)
{
    ui->setupUi(this);
    audioRecorder = new QAudioRecorder(this);
    QAudioEncoderSettings recordSettings;
    recordSettings.setCodec("audio/pcm");
    recordSettings.setSampleRate(16000);
    recordSettings.setBitRate(32);
    recordSettings.setQuality(QMultimedia::HighQuality);
    recordSettings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
    connect(ui->chosser, &QPushButton::clicked, this, &Recorder::b_autoChoose);
    audioRecorder->setEncodingSettings(recordSettings);
}

Recorder::~Recorder()
{
    delete ui;
}
void Recorder::b_autoChoose()
{
    auto info = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    foreach (auto i, info) qDebug() <<i.deviceName();
    audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());
}


