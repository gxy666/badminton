#include "Server.h"

Server::Server(QObject *parent):QTcpServer(parent)
{
    this->listen(QHostAddress::Any,8081);
    this->setMaxPendingConnections(30000);
    std::cout<<"waiting....."<<std::endl;
}
Server::~Server()
{

}
void Server::incomingConnection(qintptr d)
{
    QTcpSocket *tempsocket = new QTcpSocket;
    tempsocket->setSocketDescriptor(d);
    a = tempsocket;
    ifaccept = true;
    qDebug()<<"newer";
    connect(a,SIGNAL(readyRead()),this,SLOT(acceptdata()));
}
void Server::acceptdata()
{
    if(ifaccept)
    {
        QString tempinstruct = (QString)a->readAll();
        qDebug()<<"new connection:"<<tempinstruct;
        QStringList instruction = tempinstruct.split("@@@@");
        QString houseid = (QString)instruction.at(1);
        QString name = (QString)instruction.at(0);
        int flag = 0;
        int i;
        for(i = 0;i<HouseHold.length();++i)
        {
           if(HouseHold.at(i)!=NULL)
           {
                if(houseid.compare(HouseHold.at(i)->id)==0)
                {
                    flag++;
                    if(HouseHold.at(i)->lock)
                    {
                        a->write("full");
                        a->flush();
                        qDebug()<<"new player:"<<name<<" is denied to "<<houseid;
                    }
                    else
                    {
                        HouseHold.at(i)->setsocket2(a,name);
                        HouseHold.at(i)->lock = true;
                        qDebug()<<"new player:"<<name<<" enter "<<houseid;
                        HouseHold.at(i)->start();
                    }
                }
           }
        }
        if(flag==0)
        {
            DealHouse *house = new DealHouse(houseid,a,name,this);
            HouseHold.push_back(house);
            qDebug()<<"new house:"<<houseid;
            qDebug()<<"new player:"<<name<<" enter "<<houseid;
        }
        ifaccept = false;
    }
}

