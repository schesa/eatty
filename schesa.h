#ifndef SCHESA_H
#define SCHESA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Schesa : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Schesa(QPixmap  pixmap);

    qreal y() const;

    qreal rotation() const;

    void hop();
    void freeze();

public slots:
    void setY(qreal y);

    void setRotation(qreal rotation);

    void useGravitation();

    void rotateTo(const qreal &end, const int &duration, const QEasingCurve& curve);

private:

    void updatePixMap();
    // have the same meaning, unless a transition state like SemiOpened ear is introduced
    bool openEar;
    int direction;
    qreal m_y;
    qreal m_rotation;
    QPropertyAnimation * yAnimation;
    QPropertyAnimation * rotationAnimation;
    qreal groundPosition;
};

#endif // SCHESA_H
