#ifndef BUSYWIDGET_H
#define BUSYWIDGET_H

#include <QGraphicsItem>
class QPropertyAnimation;
/**
 * @brief The IconLabel class
 * 繁忙控件
 */
class BusyWidget : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(int angle READ angle WRITE setAngle)
public:

    BusyWidget(QGraphicsItem *parent = nullptr);
    virtual QRectF boundingRect() const override;
    void setSize(const QSize &sz);
    //显示控件
    void showItem();
    //隐藏控件
    void hideItem();
protected:
    void setAngle(int angle);
    int angle() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    int _angle; //
    QColor _color;
    QSize _size;
    QPropertyAnimation *_pAnimation;

};

#endif // BUSYWIDGET_H
