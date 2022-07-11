#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QColorDialog>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpSocket *socket;

    QString name;
    QColor curColor = Qt::black;

    void sendToServer(const QString &message);

public slots:
    void onReadyRead();

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_lineEdit_2_returnPressed();
};
#endif // WIDGET_H
