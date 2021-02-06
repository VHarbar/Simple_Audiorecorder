#ifndef RECORDER_H
#define RECORDER_H

#include <QMainWindow>
#include<QAudioRecorder>


QT_BEGIN_NAMESPACE
namespace Ui { class Recorder; }
QT_END_NAMESPACE

class Recorder : public QMainWindow
{
    Q_OBJECT

public:
    Recorder(QWidget *parent = nullptr);
    ~Recorder();
public slots:
    void b_autoChoose();
    void record();
    void stop_record();
    void deleting();

private:
    Ui::Recorder *ui;
    QAudioRecorder *audioRecorder;

};
#endif // RECORDER_H
