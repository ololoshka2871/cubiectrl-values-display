#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QMap>

class QLabel;
class QImage;

class ValuesDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit ValuesDisplay(bool test = false, QWidget *parent = 0);
    ~ValuesDisplay();
    void setBackground(QImage* img);

    class Value
    {
    public:
        Value(const QFont& fnt = QFont(),
              const QColor& color = QColor(),
              const QPoint& pos = QPoint());
        void Draw(QPainter* p) const;
        void SetText(const QString& text);
        void SetFont(const QFont& fnt);
        void SetColor(const QColor& color);
        void SetPos(const QPoint& pos);

    private:
        QPoint pos;
        QColor TextColor;
        QFont font;
        QString value;
    };

private:
    QLabel *l;
    QPixmap background;
    QMap<QString, Value*> labels;
    bool ignore_updates;

public slots:
    void SetValue(const QMap<QString, QString>& vals);
    virtual void setVisible(bool visible);

protected:
    virtual void paintEvent(QPaintEvent *e);
};

#endif // DISPLAY_H
