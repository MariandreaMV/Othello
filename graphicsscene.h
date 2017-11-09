#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "juego.h"

class graphicsscene : public QGraphicsScene
{
    Q_OBJECT
private:
    int x;
    int y;
    int opc;
public:
    Juego *juego;
    graphicsscene(QObject *parent = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    void paint();

};

#endif // GRAPHICSSCENE_H
