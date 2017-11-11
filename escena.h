#ifndef ESCENA_H
#define ESCENA_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QFont>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "inteligencia.h"
#include "juego.h"

class Escena : public QGraphicsScene
{
    Q_OBJECT
private:
    int x;
    int y;
    int opc;
    QGraphicsTextItem *puntos_texto;
    QGraphicsTextItem *puntos_jugador1;
    QGraphicsTextItem *puntos_jugador2;
    QFont fuente;
public:
    Juego *juego;

    Escena(QObject *parent = 0);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void reiniciar();
    void actualizar();

};

#endif // ESCENA_H
