#ifndef CONTROLSOCKET_H
#define CONTROLSOCKET_H

#include <QObject>
#include <QMap>

class QLocalSocket;

class controlSocket : public QObject
{
    Q_OBJECT

public:
    controlSocket(const QString &socketFileName, QObject *parent = NULL);

signals:
    void Hide();
    void Show();
    void Update(QMap<QString, QString>);

private:
    QLocalSocket* socket;

private slots:
    void processCmd();
};

#endif // CONTROLSOCKET_H
