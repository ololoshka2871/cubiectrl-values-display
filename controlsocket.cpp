#include <QLocalSocket>
#include <QDebug>
#include <QApplication>

#include "controlsocket.h"

#define SPLIT_CHAR  "="

controlSocket::controlSocket(const QString &socketFileName, QObject *parent) :
    QObject(parent)
{
    socket = new QLocalSocket(this);
    socket->connectToServer(socketFileName);

    connect(socket, SIGNAL(readyRead()), this, SLOT(processCmd()));
}

void controlSocket::processCmd()
{
    if (socket->canReadLine()) {
        QString cmd = QString(socket->readAll());
        qDebug() << cmd;

        if (cmd.contains(trUtf8("hide"))) {
            emit Hide();
            return;
        }
        if (cmd.contains(trUtf8("show"))) {
            emit Show();
            return;
        }
        if (cmd.contains(trUtf8("quit"))) {
            QApplication::quit();
            return;
        }

        QStringList keyVal = cmd.split(SPLIT_CHAR);
        if (keyVal.size() == 2) {
            QMap<QString, QString> res;
            res[keyVal.at(0)] = keyVal.at(1);
            emit Update(res);
        }
    }
}

