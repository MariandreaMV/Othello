#ifndef ESCENA_H
#define ESCENA_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsDropShadowEffect>
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
    QGraphicsTextItem *puntos_texto2;
    QGraphicsTextItem *puntos_jugador1;
    QGraphicsTextItem *puntos_jugador2;
    QGraphicsTextItem *turno_jugador;
    QGraphicsTextItem *turno_jugador2;
    QGraphicsTextItem *jugadas_mostrar;
    QFont fuente;
    QFont fuente2;
    QFont aux;
    QGraphicsDropShadowEffect *effect;
public:
    Casilla *tableroAnterior[TAM][TAM];
    Juego *juego;

    Escena(QObject *parent = 0);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void setOpc(int o) { opc = o; }
    int getOpc() { return opc; }
    void setDificultad(int o) { dificultad = o; }
    void reiniciar();
    void actualizar();

};

#endif // ESCENA_H
