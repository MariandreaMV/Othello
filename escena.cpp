#include "escena.h"

using namespace std;

Escena::Escena(QObject *parent) :
    QGraphicsScene(parent)
{
    juego = new Juego();
    opc = 1;
    dificultad = 2;

    fuente.setPixelSize(35);
    fuente.setBold(true);
    fuente.setFamily("Fixedsys");
    fuente2.setPixelSize(25);
    fuente2.setBold(true);
    fuente2.setFamily("Fixedsys");

    puntos_texto = new QGraphicsTextItem;
    puntos_texto->setFont(fuente);
    puntos_texto->setPos(520,20);
    puntos_texto->setPlainText("Puntos: ");
    puntos_texto->setDefaultTextColor(Qt::green);

    puntos_jugador1 = new QGraphicsTextItem;
    puntos_jugador1->setFont(fuente);
    puntos_jugador1->setPos(520, 80);
    puntos_jugador1->setPlainText("J1: " + QString::number(juego->getJugador1Puntos()));
    puntos_jugador1->setDefaultTextColor(Qt::black);

    puntos_jugador2 = new QGraphicsTextItem;
    puntos_jugador2->setFont(fuente);
    puntos_jugador2->setPos(520, 130);
    if(opc==1)
        puntos_jugador2->setPlainText("PC: " + QString::number(juego->getJugador2Puntos()));
    else
        puntos_jugador2->setPlainText("J2: " + QString::number(juego->getJugador2Puntos()));
    puntos_jugador2->setDefaultTextColor(Qt::white);

    turno_jugador = new QGraphicsTextItem;
    turno_jugador->setFont(fuente2);
    turno_jugador->setPos(520,215);
    turno_jugador->setPlainText("Turno: ");

    jugadas_mostrar = new QGraphicsTextItem;
    jugadas_mostrar->setFont(fuente2);
    jugadas_mostrar->setPos(520, 300);
    jugadas_mostrar->setDefaultTextColor(Qt::red);

    if (juego->getJugadorActual() == 1) {
        turno_jugador->setDefaultTextColor(Qt::black);
        this->addEllipse(630,220,32,32,QPen(Qt::black), QBrush(Qt::black));
    } else {
        turno_jugador->setDefaultTextColor(Qt::white);
        this->addEllipse(630,220,32,32,QPen(Qt::white), QBrush(Qt::white));
    }


    this->addItem(puntos_texto);
    this->addItem(puntos_jugador1);
    this->addItem(puntos_jugador2);
    this->addItem(turno_jugador);
    this->addItem(jugadas_mostrar);

    this->setBackgroundBrush(Qt::gray);
}

void Escena::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    jugadas_mostrar->setPlainText("");

    if (mouseEvent->scenePos().x() <= 64*8 && mouseEvent->scenePos().x()>=0) {
        if (mouseEvent->scenePos().y() <= 64*8 && mouseEvent->scenePos().y()>=0) {
            x = mouseEvent->scenePos().x()/64;
            y = mouseEvent->scenePos().y()/64;
            //----------------- si donde jugo es posible el movimiento-----------//
            if(juego->getTablero(y,x)->isMovimientoPosible()){
                juego->turno(y, x);
                juego->cambiarTurnos();
                //opcion de jugar vs maquina
                actualizar();
                QGraphicsScene::mouseReleaseEvent(mouseEvent);
                if (opc == 1){
                    if (dificultad == 2) {
                        Inteligencia *minMax = new Inteligencia(juego);
                        Casilla* ideal = minMax->mejorJugada();
                        if(ideal!=NULL){
                            x = ideal->getColu(); y =ideal->getFila();
                            juego->turno(y,x);
                            juego->cambiarTurnos();
                            actualizar();
                            QGraphicsScene::mouseReleaseEvent(mouseEvent);
                        }
                    } //implementar facil. o dificil como sea...
                }
            } else {
                //---------mostrar en pantalla que es bruto y jugo donde no puede---------//
                jugadas_mostrar->setPlainText("JUGADA \nINVALIDA");
            }
            //-------------compruebo que tenga uno de los dos donde jugar, si no se ahogo el juego--------------//
                bool JuegoAhogado=false;
                if (juego->getMovimientosPosibles()==0){
                    juego->cambiarTurnos();
                    if (juego->getMovimientosPosibles()==0){
                        JuegoAhogado = true;
                        juego->cambiarTurnos();
                    } else {
                        juego->cambiarTurnos();
                        jugadas_mostrar->setPlainText("Jugador \npasa turno");
                        juego->cambiarTurnos();
                        if (opc == 1 && juego->getJugadorActual() == 2) {//si esta jugando con la maquina entonces ella juega otra vez.
                            if (dificultad == 2) {
                                Inteligencia *minMax = new Inteligencia(juego);
                                Casilla* ideal = minMax->mejorJugada();
                                if(ideal!=NULL){
                                    x = ideal->getColu(); y =ideal->getFila();
                                    juego->turno(y,x);
                                    juego->cambiarTurnos();
                                    actualizar();
                                    QGraphicsScene::mouseReleaseEvent(mouseEvent);
                                }
                            } // implementar la facil o la dificil :v
                        }
                    }
                }
                if(JuegoAhogado){
                    //--------------------mostrar que se tranco el juego---------------------//
                    if (juego->getJugador1Puntos() > juego->getJugador2Puntos())
                        jugadas_mostrar->setPlainText("GANA J1");
                    else if (juego->getJugador1Puntos() == juego->getJugador2Puntos())
                        jugadas_mostrar->setPlainText("EMPATE");
                    else {
                        if (opc == 1)
                            jugadas_mostrar->setPlainText("GANA PC");
                        else
                            jugadas_mostrar->setPlainText("GANA J2");
                    }
                }
        }
    }
    puntos_jugador1->setPlainText("J1: " + QString::number(juego->getJugador1Puntos()));
    if(opc==1)
        puntos_jugador2->setPlainText("PC: " + QString::number(juego->getJugador2Puntos()));
    else
        puntos_jugador2->setPlainText("J2: " + QString::number(juego->getJugador2Puntos()));
}

void Escena::reiniciar()
{
    actualizar();
    puntos_jugador1->setPlainText("J1: " + QString::number(juego->getJugador1Puntos()));
    if(opc==1)
        puntos_jugador2->setPlainText("PC: " + QString::number(juego->getJugador2Puntos()));
    else
        puntos_jugador2->setPlainText("J2: " + QString::number(juego->getJugador2Puntos()));

    jugadas_mostrar->setPlainText("");
}

void Escena::actualizar()
{

    int x = 0, y = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
                this->addRect(x,y,64,64,QPen(Qt::gray),QBrush(Qt::green));

            if (juego->tablero[i][j]->isMovimientoPosible() && juego->getMostrarPistas()){
                if(juego->getJugadorActual()==1)
                    this->addEllipse(x+64/2-4,y+64/2-4,8,8,QPen(Qt::black), QBrush(Qt::black));
                else
                    this->addEllipse(x+64/2-4,y+64/2-4,8,8,QPen(Qt::white), QBrush(Qt::white));
            } else
                this->addRect(x,y,64,64,QPen(Qt::gray),QBrush(Qt::green));
            if (juego->tablero[i][j]->getEstado() == 1)
                this->addEllipse(x,y,64,64,QPen(Qt::black), QBrush(Qt::black));
            if (juego->tablero[i][j]->getEstado() == 2)
                this->addEllipse(x,y,64,64,QPen(Qt::white), QBrush(Qt::white));
                x+=64;

        }
        x=0;
        y+=64;
    }
    if (juego->getJugadorActual() == 1) {
        turno_jugador->setDefaultTextColor(Qt::black);
        this->addEllipse(630,220,32,32,QPen(Qt::black), QBrush(Qt::black));
    } else {
        turno_jugador->setDefaultTextColor(Qt::white);
        this->addEllipse(630,220,32,32,QPen(Qt::white), QBrush(Qt::white));
    }

}
