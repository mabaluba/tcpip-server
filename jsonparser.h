#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

class JsonParser
{
public:
    explicit JsonParser();
    ~JsonParser();
    int getId() const;
    QString getCommand() const;
    void ParseJson(const QByteArray&);

private:
    int *id;
    QString *command;
};

#endif // JSONPARSER_H
