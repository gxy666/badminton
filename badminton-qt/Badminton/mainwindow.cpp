#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/new/prefix1/resource/tb.ico"));
    ui->p1pushButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resource/an1.png);}\
                                        QPushButton:hover:!pressed {border-image: url(:/new/prefix1/resource/an1_hover.png);}");
    ui->p2pushButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/resource/an2.png);}\
                                        QPushButton:hover:!pressed {border-image: url(:/new/prefix1/resource/an2_hover.png);}");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_p1pushButton_clicked()
{
    ui->p1pushButton->close();
    ui->p2pushButton->close();
    this->setStyleSheet("border-image: url(:/new/prefix1/resource/loading);");
    this->sleep(3000);
    this->close();
    OnePlayerWindow *a = new OnePlayerWindow();
    a->show();
}
void MainWindow::on_p2pushButton_clicked()
{
    LogDialog *log = new LogDialog();
    log->show();
    log->exec();
    Doubleplayerwindow *a;
    if (log->ok==1)
    {
        a = new Doubleplayerwindow();
        a->setNAMEID(log->getname(),log->getid());
        a->setip(log->getip());
        a->sendlogmessage();
    }
    if(a->diesignal)
    {
        QMessageBox::critical(NULL, "Badminton", "网络无连接");
    }
    else
    {
        ui->p1pushButton->close();
        ui->p2pushButton->close();
        this->setStyleSheet("border-image: url(:/new/prefix1/resource/loading);");
        this->sleep(3000);
        a->show();
        this->close();
    }
}
void MainWindow::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
