#include <QLabel>
#include <QHBoxLayout>
#include <QMap>

#include "display.h"

Display::Display(QWidget *parent) : QWidget(parent)
{
    l = new QLabel();
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(l);
    setLayout(layout);
}

void Display::SetValue(const QMap<QString, QString> &vals)
{
    QString k = vals.keys().at(0);
    l->setText(QString("%1=%2").arg(k).arg(vals[k]));
}
