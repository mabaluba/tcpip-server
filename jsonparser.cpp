#include "jsonparser.h"

JsonParser::JsonParser(): id(new int), command(new QString)
{
    *id=0;
    *command="";
}
JsonParser::~JsonParser(){}

void JsonParser::ParseJson(const QByteArray &data_read)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data_read);
    QJsonObject jsonObj = jsonDoc.object();
    *id = jsonObj["id"].toInt();
    *command = jsonObj["command"].toString();
}

int JsonParser::getId() const
{
    return *id;
}

QString JsonParser::getCommand() const
{
    return *command;
}
