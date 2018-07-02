#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class LogDialog;
}

class LogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogDialog(QWidget *parent = 0);
    ~LogDialog();
    QString getid();
    QString getname();
    QString getip();
    int ok = 0;
private slots:
    void on_pushButton_clicked();

private:
    Ui::LogDialog *ui;
    QString name;
    QString id;
    QString ip;
};

#endif // LOGDIALOG_H
