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
    connect(ui->chosser, &QPushButton::clicked, this, &Recorder::b_autoChoose);
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

