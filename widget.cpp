#include "widget.h"
#include "ui_widget.h"
#include "jsonparser.h"
#include "bulb.h"

WidgetServer::WidgetServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
    , bulb_id(new int)
    , bulb_count(new int)
    , bulb_command(new QString)
{
    ui->setupUi(this);
    this->adjustSize();
    server = new QTcpServer(this);
    socket = new QTcpSocket(this);
    *bulb_id=0;
    *bulb_count=0;
    *bulb_command="";

    if(!server-> listen(QHostAddress("192.168.1.101"),8080))//адрес и порт, по которому клиент может соединиться с сервером
    {
        ui->label_isConnected->setText("Нет соединения");
    }
    else
    {
        connect(server, &QTcpServer::newConnection, this, &WidgetServer::OnConnected);//при новом соединении вызываем OnConnected
    }
}

void WidgetServer:: OnConnected()
{
    ui->label_isConnected->setText("Соединение установлено");
    socket = server->nextPendingConnection();//получаем сокет, подключенный к серверу
    connect(socket,&QTcpSocket::readyRead,this,&WidgetServer::ReadData);//подключаем обработчик чтения данных, когда информация пришла на сервер
    connect(socket, &QTcpSocket::disconnected, this, &WidgetServer::OnDisconnected);//вызываем закрытие сокета сервера при отключении
}

void WidgetServer:: ReadData()
{
    auto data_read = ((QTcpSocket *)sender())->readAll();//получаем информацию от клиента
    auto getInfo = std::make_unique<JsonParser>();//функция умного указателя вместо new
    getInfo->ParseJson(data_read);//десериализация в json номер лампочки и комманды от клиента
    *bulb_id = getInfo->getId();//получаем id лампочки
    *bulb_command = getInfo->getCommand();// получаем комманду

//обнуление виджета при получении комманды clear
    if(*bulb_command=="clear")
    {
        ClearBulbs();
    }

//реализуем комманду add добавления лампочки
    else if(*bulb_command=="add")
    {
        AddButton();
    }

//реализуем комманду delete удаления лампочки
    else if(*bulb_command=="delete")
    {
        DeleteButton();
    }

//команда ON изменяет цвет на зеленый
    else if(*bulb_command=="on")
    {
        TurnOn();
    }

//комманда OFF изменяет цвет на красный
    else if(*bulb_command=="off")
    {
        TurnOff();
    }
}

void WidgetServer::OnDisconnected()
{
    socket->close();//закрываем сокет со стороны сервера
}

void WidgetServer::ClearBulbs()
{
    ui->listWidget->clear();
    *bulb_count=0;
}
void WidgetServer::AddButton()
{
    auto newBulb = std::make_unique<Bulb>(*bulb_count+1);//создаем новую лампочку
    ui->listWidget->addItem(newBulb->getFullName());//добавляем лампочку с текстом
    ui->listWidget->item(*bulb_id)->setBackground(Qt::red);//помечаем ее как выключенную устанавливая цвет фона на красный
    ++*bulb_count;//инкрементируем счетчик лампочек для добавления новых в конец списка
}
void WidgetServer::DeleteButton()
{
    ui->listWidget->takeItem(*bulb_id);
}
void WidgetServer::TurnOn()
{
    ui->listWidget->item(*bulb_id)->setBackground(Qt::green);
}
void WidgetServer::TurnOff()
{
    ui->listWidget->item(*bulb_id)->setBackground(Qt::red);
}

WidgetServer::~WidgetServer()
{
    delete ui;
}
