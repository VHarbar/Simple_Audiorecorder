#include "recorder.h"
#include "ui_recorder.h"
#include <QAudioDeviceInfo>
#include<QAudioRecorder>
#include<QUrl>
#include<QDir>


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
    QString path=("\D:\\test\\");
    QDir currentDir(path);
    QStringList items = currentDir.entryList(QDir::AllEntries |QDir::NoDotAndDotDot);
    ui->listWidget->addItems(items);
    connect(ui->chosser,&QPushButton::clicked,this,&Recorder::b_autoChoose);
    connect(ui->b_record,&QPushButton::clicked,this,&Recorder::record);
    connect(ui->b_stop,&QPushButton::clicked,this,&Recorder::stop_record);
    connect(ui->b_del,&QPushButton::clicked,this,&Recorder::deleting);
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
    audioRecorder->setOutputLocation(QUrl::fromLocalFile("/D:/test/"));
}

void Recorder::record()
{
    audioRecorder->record();
}

void Recorder::stop_record()
{
    audioRecorder->stop();
}

void Recorder::deleting()
{

}


