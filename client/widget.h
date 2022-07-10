#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>

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

    void sendToServer(const QString &message);

public slots:
    void onReadyRead();

private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
 };
#endif // WIDGET_H
