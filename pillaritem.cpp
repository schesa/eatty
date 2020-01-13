#include "pillaritem.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>
#include "schesa.h"

PillarItem::PillarItem() :
    top(new QGraphicsPixmapItem(QPixmap(":/images/top_knife.png"))),
    bottom(new QGraphicsPixmapItem(QPixmap(":/images/bottom_knife.png")))
{

    int distance = 96;
    top->setPos(QPointF(0,0) + QPointF(-top->boundingRect().width()/2, -top->boundingRect().height()-distance));
    bottom->setPos(QPointF(0,0) + QPointF(-bottom->boundingRect().width()/2,distance));

    addToGroup(top);
    addToGroup(bottom);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this, "x",this);
    xAnimation->setStartValue(260 + xRandomizer);
    xAnimation->setEndValue(-260);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(2000);
    connect(xAnimation, &QPropertyAnimation::finished,[=](){
        qDebug() << "Animation finished";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();

//    bottom->setX(bottom->x()+bottom->pixmap().rect().height());
//    bottom->setY(bottom->y()+80);

}

PillarItem::~PillarItem()
{
    qDebug() << "  Pillar deleted ";
}

qreal PillarItem::x() const
{
    return m_x;
}

bool PillarItem::collide()
{
    QList<QGraphicsItem*> items = top->collidingItems();
    items.append(bottom->collidingItems());
    foreach(QGraphicsItem* item, items){
        Schesa *schesa = dynamic_cast<Schesa*>(item);
        if(schesa){
            return true;
        }
    }
    return false;
}

void PillarItem::freeze()
{
    xAnimation->stop();
}

void PillarItem::setX(qreal x)
{
//    qDebug() << "Pillar position: " << x;
    m_x = x;
    if(collide()){
        emit collideFail();
    }

    setPos(QPointF(0,0) + QPointF(x, yPos));
}
