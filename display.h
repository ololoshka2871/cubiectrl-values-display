#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>

class QLabel;

class Display : public QWidget
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = 0);

private:
    QLabel *l;

public slots:
    void SetValue(const QMap<QString, QString>& vals);
};

#endif // DISPLAY_H
