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


    QPixmap pixmap(10, 10);
    pixmap.fill(curColor);
    ui->label_2->setPixmap(pixmap);

}

Widget::~Widget()
{
    delete ui;
}

void Widget:: sendToServer(const QString &message)
{
    QJsonObject jsonObj;
    jsonObj.insert("name", QJsonValue::fromVariant(name));
    jsonObj.insert("color", QJsonValue::fromVariant(curColor));
    jsonObj.insert("message", QJsonValue::fromVariant(message));


    QByteArray data;
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << QJsonDocument(jsonObj).toJson();

    socket->write(data);
}

void Widget::onReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);

    if(in.status() == QDataStream::Ok){
        QByteArray message;
//        message.clear();
        in >> message;
        auto doc = QJsonDocument::fromJson(message);

        QString senderName = doc.object().value("name").toString();
        QColor senderColor = doc.object().value("color").toVariant().value<QColor>();
        QString messageText = doc.object().value("message").toString();

       qDebug() << senderColor.name();

        ui->textBrowser->append(QString("<font color=\"%1\">%2</font>: ").arg(senderColor.name()).arg(senderName) + messageText);
    }
    else{
        QMessageBox::critical(this, "Error", "read error");
    }
}


void Widget:: on_pushButton_clicked()
{
    sendToServer(ui->lineEdit->text());
    ui->lineEdit->clear();
}


void Widget::on_lineEdit_returnPressed()
{
    sendToServer(ui->lineEdit->text());
    ui->lineEdit->clear();
}


void Widget::on_pushButton_2_clicked()
{
    curColor = QColorDialog::getColor(Qt::black);
    QPixmap pixmap(10, 10);
    pixmap.fill(curColor);
    ui->label_2->setPixmap(pixmap);
}


void Widget::on_pushButton_3_clicked()
{
    socket->connectToHost("127.0.0.1", 2323);
    ui->stackedWidget->setCurrentIndex(0);
    name = ui->lineEdit_2->text();
    setGeometry(300, 300, 500, 500);
}

void Widget::on_lineEdit_2_returnPressed()
{
    socket->connectToHost("127.0.0.1", 2323);
    ui->stackedWidget->setCurrentIndex(0);
    name = ui->lineEdit_2->text();
    setGeometry(300, 300, 500, 500);
}

