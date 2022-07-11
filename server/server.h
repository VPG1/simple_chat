#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <set>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(int port = 2323, QObject *parent = nullptr);
    
private:
    std::set<QTcpSocket *> sockets;
    
    void sendToClient(const QByteArray &message);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

public slots:
    void onReadyRead();
    void onDisconect();
};

#endif // SERVER_H
