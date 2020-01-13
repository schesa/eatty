#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    setUpPillarTimer();
}

void Scene::addSchesa()
{
    schesa = new Schesa(QPixmap(":/images/s_schesaUP.png"));
    addItem(schesa);
}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer, &QTimer::timeout, [=](){
        PillarItem * pillar = new PillarItem();
        connect(pillar, &PillarItem::collideFail, [=](){
            pillarTimer->stop();
            freeze();
        });

        addItem(pillar);
    });

    pillarTimer->start(1000);
}

void Scene::freeze()
{
    schesa->freeze();

    QList<QGraphicsItem*> i = items();
    foreach(QGraphicsItem *item, i){
        PillarItem * pillar = dynamic_cast<PillarItem*>(item);
        if(pillar){
            pillar->freeze();
        }
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        schesa->hop();
    }
    QGraphicsScene::mousePressEvent(event);
}
