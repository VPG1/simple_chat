#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <vector>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(int port = 2323, QObject *parent = nullptr);
    
private:
    std::vector<QTcpSocket *> sockets;  
    
    void sendToClient(const QString &message);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

public slots:
    void onReadyRead();
};

#endif // SERVER_H
