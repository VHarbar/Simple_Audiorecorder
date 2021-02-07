#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QAudioDeviceInfo>
#include<QAudioRecorder>
#include<QUrl>
#include<QFileDialog>
#include<QDir>
#include <QFileSystemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    audioRecorder = new QAudioRecorder(this);
    QAudioEncoderSettings recordSettings;
    recordSettings.setCodec("audio/pcm");
    recordSettings.setSampleRate(16000);
    recordSettings.setBitRate(32);
    recordSettings.setQuality(QMultimedia::HighQuality);
    recordSettings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
    audioRecorder->setEncodingSettings(recordSettings);
    connect(ui->Chooser,&QPushButton::clicked,this,&MainWindow::Choose_auto);
    connect(ui->b_record,&QPushButton::clicked,this,&MainWindow::start_recording);
    connect(ui->b_stop,&QPushButton::clicked,this,&MainWindow::stop_record);
    connect(ui->b_del,&QPushButton::clicked,this,&MainWindow::deleting);
    add_reccord_list();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Choose_auto()
{
    auto info = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    foreach (auto i, info) qDebug() <<i.deviceName();
    audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());
    audioRecorder->setOutputLocation(QUrl::fromLocalFile("/D:/test/"));
}

void MainWindow::start_recording()
{

    audioRecorder->record();
    ui->b_record->setText("||");
    disconnect (ui->b_record, &QPushButton::clicked, this, &MainWindow::start_recording);
    connect (ui->b_record, &QPushButton::clicked, this, &MainWindow::pause);
}

void MainWindow::stop_record()
{
    if(ui->b_record->text()=="||")
    {
        disconnect (ui->b_record, &QPushButton::clicked, this, &MainWindow::pause);
        connect (ui->b_record, &QPushButton::clicked, this, &MainWindow::start_recording);
        ui->b_record->setText("|>");
    }
    audioRecorder->stop();
    add_reccord_list();
}

void MainWindow::deleting()
{
    QString filePath=("D:\\test\\"+ui->listWidget->currentIndex().data().toString());
    ui->listWidget->takeItem(ui->listWidget->row(ui->listWidget->currentItem()));
    QFile::remove(filePath);
}

void MainWindow::pause()
{
    audioRecorder->pause();
    ui->b_record->setText("|>");
    disconnect (ui->b_record, &QPushButton::clicked, this, &MainWindow::pause);
    connect (ui->b_record, &QPushButton::clicked, this, &MainWindow::start_recording);

}

void MainWindow::add_reccord_list()
{
    ui->listWidget->clear();
    QString path=("D:\\test\\");
    QDir currentDir(path);
    QStringList items = currentDir.entryList(QDir::AllEntries |QDir::NoDotAndDotDot);
    ui->listWidget->addItems(items);
}

