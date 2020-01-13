#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class PillarItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit PillarItem();
    ~PillarItem();
    qreal x() const;
    bool collide();
    void freeze();
public slots:
    void setX(qreal x);

signals:
    void collideFail();

private:
    QGraphicsPixmapItem * top;
    QGraphicsPixmapItem * bottom;
    QPropertyAnimation * xAnimation;

    qreal m_x;
    int yPos;
};

#endif // PILLARITEM_H
