#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioRecorder>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void Choose_auto();
    void start_recording();
    void stop_record();
    void deleting();
    void pause();


private:
    Ui::MainWindow *ui;
    QAudioRecorder *audioRecorder;
    void add_reccord_list();
};
#endif // MAINWINDOW_H
