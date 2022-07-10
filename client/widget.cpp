#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , socket(new QTcpSocket)
{
    ui->setupUi(this);
    connect(socket, &QTcpSocket::readyRead, this, &Widget::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    socket->connectToHost("127.0.0.1", 2323);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendToServer(const QString &message)
{
    QByteArray data;
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << message;

    socket->write(data);
}

void Widget::onReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);

    if(in.status() == QDataStream::Ok){
        QString message;
        in >> message;
        ui->textBrowser->append(message);
    }
    else{
        QMessageBox::critical(this, "Error", "read error");
    }
}


void Widget::on_pushButton_clicked()
{
    sendToServer(ui->lineEdit->text());
    ui->lineEdit->clear();
}


void Widget::on_lineEdit_returnPressed()
{
    sendToServer(ui->lineEdit->text());
    ui->lineEdit->clear();
}

