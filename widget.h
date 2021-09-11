#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class WidgetServer : public QWidget
{
    Q_OBJECT

public:
    WidgetServer(QWidget *parent = nullptr);
    ~WidgetServer();

private slots:
    void OnConnected();
    void ReadData();
    void OnDisconnected();

private:
    Ui::Server *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    int *bulb_id;
    int *bulb_count;
    QString *bulb_command;
    void AddButton();
    void DeleteButton();
    void TurnOn();
    void TurnOff();
    void ClearBulbs();
};
#endif // WIDGET_H
