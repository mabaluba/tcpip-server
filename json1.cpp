#include "json1.h"
#include<QJsonDocument>
#include<QJsonObject>


json1::json1(QWidget *parent) : QWidget(parent)
{
    auto id = 5;
    auto bulb_command = "add";
    QJsonObject a;
    a["id"]= id;
    a["command"]= bulb_command;
    QJsonDocument doc(a);
    qDebug()<< doc.toJson( QJsonDocument::Indented );
}
