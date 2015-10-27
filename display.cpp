#include <QLabel>
#include <QHBoxLayout>
#include <QMap>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QApplication>
#include <QDesktopWidget>

#include "display.h"

ValuesDisplay::ValuesDisplay(bool test, QWidget *parent) : QWidget(parent)
{
    ignore_updates = true;
    if (test)
    {
        // test keys:
        // "CPU_Temp" "GPU_Temp" "SPIN1" "SPIN2" "flow1" "flow2";
        QFont fnt;
        fnt.setFamily("Droid");
        fnt.setPointSize(40);

        labels["CPU_Temp"] = new Value(fnt, Qt::red, QPoint(50, 50));
        labels["GPU_Temp"] = new Value(fnt, Qt::cyan, QPoint(300, 200));
        labels["SPIN1"] = new Value(fnt, Qt::blue, QPoint(50, 100));
        labels["SPIN2"] = new Value(fnt, Qt::lightGray, QPoint(300, 150));
        labels["flow1"] = new Value(fnt, Qt::yellow, QPoint(500, 700));
        labels["flow2"] = new Value(fnt, "#0AC0FC", QPoint(700, 700));
    }
}

ValuesDisplay::~ValuesDisplay()
{
    for(QMap<QString, Value*>::ConstIterator it = labels.begin();
        it != labels.end(); ++it)
        delete *it;
}

void ValuesDisplay::setBackground(QImage *img)
{
    background =
            QPixmap::fromImage(
                img->scaled(QApplication::desktop()->screenGeometry().size()));
}

void ValuesDisplay::SetValue(const QMap<QString, QString> &vals)
{
    for (QMap<QString, QString>::ConstIterator it = vals.begin();
         it != vals.end(); ++it)
        if (labels.keys().contains(it.key()))
            labels[it.key()]->SetText(it.value());
        else
        {
            Value *v = new Value;
            v->SetColor(Qt::red);
            v->SetPos(QPoint(50, 50));
            v->SetText(it.value());

            QFont fnt;
            fnt.setPointSize(50);
            fnt.setFamily("Droid");
            v->SetFont(fnt);
            labels[it.key()] = v;
        }
    if (!ignore_updates)
        update();
}

void ValuesDisplay::setVisible(bool visible)
{
    ignore_updates = !visible;
    QWidget::setVisible(visible);
}

void ValuesDisplay::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);

    for(QMap<QString, Value*>::ConstIterator it = labels.begin();
        it != labels.end(); ++it)
        (*it)->Draw(&painter);
}

ValuesDisplay::Value::Value(const QFont &fnt, const QColor &color, const QPoint &pos)
{
    SetFont(fnt);
    SetColor(color);
    SetPos(pos);
}

void ValuesDisplay::Value::Draw(QPainter *p) const
{
    p->setFont(font);
    p->setPen(TextColor);
    p->setBrush(TextColor);
    p->drawText(pos, value);
}

void ValuesDisplay::Value::SetText(const QString &text)
{
    value = text;
}

void ValuesDisplay::Value::SetFont(const QFont &fnt)
{
    font = fnt;
}

void ValuesDisplay::Value::SetColor(const QColor &color)
{
    TextColor = color;
}

void ValuesDisplay::Value::SetPos(const QPoint &pos)
{
    this->pos = pos;
}
