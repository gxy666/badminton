#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QMessageBox>
#include "doubleplayerwindow.h"
#include "oneplayerwindow.h"
#include "logdialog.h"
#include <QWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_p1pushButton_clicked();
    void on_p2pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void sleep(unsigned int msec);
};

#endif // MAINWINDOW_H
