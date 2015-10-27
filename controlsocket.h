#ifndef CONTROLSOCKET_H
#define CONTROLSOCKET_H

#include <QObject>
#include <QMap>
#include <QVector>

class QLocalSocket;

class controlSocket : public QObject
{
    Q_OBJECT

public:
    controlSocket(const QString &socketFileName, QObject *parent = NULL);
    bool istest() const;

signals:
    void Hide();
    void Show();
    void Update(QMap<QString, QString>);

private:
    QLocalSocket* socket;
    QVector<QString> keys;
    bool testFirstSignal;

protected:
    virtual void timerEvent(QTimerEvent *e);

private slots:
    void processCmd();
};

#endif // CONTROLSOCKET_H
