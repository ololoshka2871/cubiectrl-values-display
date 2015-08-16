#include <QApplication>
#include <QDebug>

#include "display.h"
#include "controlsocket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (argc != 2) {
        qDebug() << "Usage: " << argv[0] << " <ctrl socket>\n";
        return 1;
    }

    Display w;
    controlSocket s(QObject::trUtf8(argv[1]));

    QObject::connect(&s, SIGNAL(Hide()), &w, SLOT(hide()));
    QObject::connect(&s, SIGNAL(Show()), &w, SLOT(showFullScreen()));
    QObject::connect(&s, SIGNAL(Update(QMap<QString, QString>)), &w,
                     SLOT(SetValue(QMap<QString,QString>)));

    return a.exec();
}
