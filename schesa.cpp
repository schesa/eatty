#include "schesa.h"

#include <QTimer>
#include <QTransform>
#include <QGraphicsScene>
#include <QDebug>

Schesa::Schesa(QPixmap pixmap)
    : openEar(true), direction(1){
    setPixmap(pixmap);

    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout,[=](){
        updatePixMap();
    });
    timer->start(100);

    groundPosition = scenePos().y() + 160;

    yAnimation = new QPropertyAnimation(this, "y",this);
    yAnimation->setStartValue(scenePos().y());
    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);
    yAnimation->start();

    rotationAnimation = new QPropertyAnimation(this,"rotation",this);
    rotateTo(90,1200,QEasingCurve::InQuad);
}

qreal Schesa::y() const
{
    return m_y;
}

qreal Schesa::rotation() const
{
    return m_rotation;
}

void Schesa::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);
    rotationAnimation->start();
}

void Schesa::hop()
{
    qDebug() << "enter hop";
//    rotationAnimation->stop();
//    yAnimation = new QPropertyAnimation(this, "y",this);
//    rotationAnimation = new QPropertyAnimation(this,"rotation",this);
    delete yAnimation;
    yAnimation = new QPropertyAnimation(this, "y",this);
    qDebug() << "stop all animations";
    qreal yPos = y();
    yAnimation->setStartValue(yPos);
    yAnimation->setEndValue(yPos - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);
    yAnimation->setDuration(285);
    yAnimation->start();
    qDebug() << "start animation";
    connect(yAnimation, &QPropertyAnimation::finished,[=](){
        useGravitation();
    });

    rotateTo(-20,200,QEasingCurve::OutCubic);
}

void Schesa::setY(qreal y)
{
    moveBy(0,y-m_y);
    m_y = y;
}

void Schesa::setRotation(qreal rotation)
{
    m_rotation = rotation;

    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(rotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

void Schesa::useGravitation()
{
    if(y() < groundPosition){
        qDebug()<<"Gravity rotation";
        rotationAnimation->stop();
        qDebug()<<"Gravity y";
        yAnimation->setStartValue(y());
        yAnimation->setEndValue(groundPosition);
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setDuration(1200);
        yAnimation->start();

        rotateTo(90,1100,QEasingCurve::InCubic);
    };
}

void Schesa::updatePixMap()
{
    if(direction == 1){
        setPixmap(QPixmap(":/images/s_schesaUP.png"));
        openEar=true;
        direction=0;
    }else{
        setPixmap(QPixmap(":/images/s_schesaDOWN.png"));
        openEar=false;
        direction=1;
    }
}

void Schesa::freeze()
{
    yAnimation->stop();
    rotationAnimation->stop();
}
