#include "busywidget.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>

BusyWidget::BusyWidget(QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , _angle(0)
{
    //创建动画
    _pAnimation = new QPropertyAnimation(this, "angle");
    //设置动画持续时间
    _pAnimation->setDuration(1000);
    //设置动画循环次数
    //永远运行，直到stop
    _pAnimation->setLoopCount(-1);
    for(int i = 0; i < 12; ++i)
    {
        //使用插值的方法，设置动画值
        //因为angle 属性是int， i自增，key对应的value正好可以全部覆盖所有值，可以看成离散动画
        //NOTE:如果设置 _pAnimation->setKeyValueAt(i/11.0, i * 30);
        //     此时key对应的value不能完全覆盖，比如key = 1 时， value可以是 0 ~ 30中任意的值
        _pAnimation->setKeyValueAt(i/11.0, i);
    }
    connect(_pAnimation, &QVariantAnimation::valueChanged,[](){
    });
    showItem();
}

QRectF BusyWidget::boundingRect() const
{
    return  QRect(0, 0, _size.width(), _size.height()).adjusted(-2, -2, 2, 2);
}

void BusyWidget::setSize(const QSize &sz)
{
    _size = sz;
}

void BusyWidget::showItem()
{
    _pAnimation->start();
    this->show();
}

void BusyWidget::hideItem()
{
    _pAnimation->stop();
    this->hide();
}

void BusyWidget::setAngle(int angle)
{
    //优化，如果更行的值为当前值，不刷新界面
    if(angle == _angle){
        return;
    }
    _angle = angle;
    update();
}

int BusyWidget::angle() const
{
    return _angle;
}

void BusyWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     int width = qMin(_size.width(), _size.height());


     painter->setRenderHint(QPainter::Antialiasing);

     int outerRadius = (width-1)*0.5;
     int innerRadius = (width-1)*0.5*0.38;

     int capsuleHeight = outerRadius - innerRadius;
     int capsuleWidth  = (width > 32 ) ? capsuleHeight *.23 : capsuleHeight *.35;
     int capsuleRadius = capsuleWidth/2;

     for (int i=0; i < 12; i++)
     {
         QColor color = _color;
         color.setAlphaF(1.0f - (i/12.0f));
         painter->setPen(Qt::NoPen);
         painter->setBrush(color);

         painter->save();
         painter->translate(boundingRect().center());
         painter->rotate(_angle * 30.0f - i*30.0f);
         painter->drawRoundedRect(-capsuleWidth*0.5, -(innerRadius+capsuleHeight), capsuleWidth,
                                  capsuleHeight, capsuleRadius, capsuleRadius);
         painter->restore();
     }
}
