#include "server.h"

Server::Server(int port, QObject *parent)
    : QTcpServer{parent}
{
    if(listen(QHostAddress::Any, port)){
        qDebug() << "successfully started";
    }
    else{
        qDebug() << "error";
    }
}

void Server::sendToClient(const QString &message)
{

}

void Server::incomingConection(qintptr socketDescriptor)
{
    auto socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    sockets.push_back(socket);
    qDebug() << "client connected: " << socketDescriptor;
}

void Server::onReadyRead()
{
    auto socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        qDebug() << "read..";
        QString str;
        in >> str;
        qDebug() << str;
    }
    else{
        qDebug() << "data stream error";
    }
}
