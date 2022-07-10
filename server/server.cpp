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
    QByteArray data;
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << message;

    for(auto &socket : sockets){
        socket->write(data);
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    auto socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::onDisconect);

    sockets.insert(socket);
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
        sendToClient(str);
    }
    else{
        qDebug() << "data stream error";
    }
}

void Server::onDisconect()
{
    auto socket = (QTcpSocket*)sender();
    sockets.erase(socket);
    socket->deleteLater();
}
