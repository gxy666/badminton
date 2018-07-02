#include "logdialog.h"
#include "ui_logdialog.h"

LogDialog::LogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogDialog)
{
    ui->setupUi(this);
}

LogDialog::~LogDialog()
{
    delete ui;
}

void LogDialog::on_pushButton_clicked()
{
    id = this->ui->textEdit_2->toPlainText();
    name = this->ui->textEdit->toPlainText();
    ip = this->ui->ip->toPlainText();
    if(id.compare("")==0||name.compare("")==0)
    {
        QMessageBox::critical(NULL,"warning","你需要输入名字和房间id");
    }
    else
    {
        if(ip.compare("")==0)
        {
            QMessageBox::critical(NULL,"warning","你需要输入服务器IP");
        }
        else
        {
            ok = 1;
            this->close();
        }

    }
}
QString LogDialog::getid()
{
    return id;
}
QString LogDialog::getname()
{
    return name;
}
QString LogDialog::getip()
{
    return ip;
}
