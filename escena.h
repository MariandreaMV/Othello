#ifndef ESCENA_H
#define ESCENA_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QFont>
#include "inteligencia.h"
#include "juego.h"

class Escena : public QGraphicsScene
{
    Q_OBJECT
private:
    int x;
    int y;
    int opc;
    int dificultad;

    QGraphicsTextItem *puntos_texto;
    QGraphicsTextItem *puntos_jugador1;
    QGraphicsTextItem *puntos_jugador2;
    QFont fuente;
public:
    Juego *juego;

    Escena(QObject *parent = 0);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void setOpc(int o) { opc = o; }
    void setDificultad(int o) { dificultad = o; }
    void reiniciar();
    void actualizar();

};

#endif // ESCENA_H
