#include <QLocalSocket>
#include <QDebug>
#include <QApplication>
#include <QStringList>

#include "controlsocket.h"

#define SPLIT_CHAR  "="

controlSocket::controlSocket(const QString &socketFileName, QObject *parent) :
    QObject(parent)
{
    if (socketFileName == "test")
    {
        keys << "CPU_Temp" << "GPU_Temp" << "SPIN1" << "SPIN2" << "flow1" << "flow2";
        testFirstSignal = true;
        startTimer(100);
    }
    else
    {
        socket = new QLocalSocket(this);
        socket->connectToServer(socketFileName);

        connect(socket, SIGNAL(readyRead()), this, SLOT(processCmd()));
    }
}

bool controlSocket::istest() const
{
    return !keys.isEmpty();
}

static int rnd(int Low, int High)
{
    return qrand() % ((High + 1) - Low) + Low;
}

void controlSocket::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    if (testFirstSignal)
    {
        testFirstSignal = false;
        emit Show();
    }

    int index = rnd(0, keys.size() -1);
    QMap<QString, QString> res;
    res[keys.at(index)] = QString::number(rnd(10, 1000));
    emit Update(res);
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

