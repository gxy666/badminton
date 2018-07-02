#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
#include <QThread>
#include "dealhouse.h"
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = 0);
    ~Server();
private:
    QVector<DealHouse *>  HouseHold;
    QTcpSocket *a;
    void incomingConnection(qintptr d);
    bool ifaccept = false;
private slots:
    void acceptdata();

};

#endif // SERVER_H
