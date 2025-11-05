#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
   Ui::MainWindow *ui;

   QString mp3Path = "";
   int inputID = -1, outputID = -1;
   bool active = false;

   void startStop();
   void setInputDevice(int id);
   void setOutputDevice(int id);
   void setMP3File();
};
#endif // MAINWINDOW_H
