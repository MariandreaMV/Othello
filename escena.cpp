#include "escena.h"

using namespace std;

Escena::Escena(QObject *parent) :
    QGraphicsScene(parent)
{
    juego = new Juego();
    this->opc=1;

    fuente.setPixelSize(35);
    fuente.setBold(true);
    fuente.setFamily("Terminal");

    puntos_texto = new QGraphicsTextItem;
    puntos_jugador1 = new QGraphicsTextItem;
    puntos_jugador2 = new QGraphicsTextItem;
    puntos_texto->setFont(fuente);
    puntos_jugador1->setFont(fuente);
    puntos_jugador2->setFont(fuente);
    puntos_texto->setPos(520,70);
    puntos_jugador1->setPos(520, 150);
    puntos_jugador2->setPos(520, 250);
    puntos_texto->setPlainText("Puntos: ");
    puntos_jugador1->setPlainText("J1: " + QString::number(juego->getJugador1Puntos()));
    if(opc==1)
        puntos_jugador2->setPlainText("PC: " + QString::number(juego->getJugador2Puntos()));
    else
        puntos_jugador2->setPlainText("J2: " + QString::number(juego->getJugador2Puntos()));
    this->addItem(puntos_texto);
    this->addItem(puntos_jugador1);
    this->addItem(puntos_jugador2);

    this->setBackgroundBrush(Qt::gray);
}

void Escena::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    if (mouseEvent->scenePos().x() <= 64*8 && mouseEvent->scenePos().x()>=0) {
        if (mouseEvent->scenePos().y() <= 64*8 && mouseEvent->scenePos().y()>=0) {
            //qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
            x = mouseEvent->scenePos().x()/64;
            y = mouseEvent->scenePos().y()/64;

            //----------------- si donde jugo es posible el movimiento-----------//
            if(juego->getTablero(y,x)->isMovimientoPosible()){
                juego->turno(y, x);
                juego->cambiarTurnos();
                //opcion de jugar vs maquina
                actualizar();
                QGraphicsScene::mouseReleaseEvent(mouseEvent);
                if(opc==1){
                    Inteligencia *minMax = new Inteligencia(juego);
                    Casilla* ideal = minMax->mejorJugada();
                    if(ideal!=NULL){
                        x = ideal->getColu(); y =ideal->getFila();
                        juego->turno(y,x);
                        juego->cambiarTurnos();
                        actualizar();
                        QGraphicsScene::mouseReleaseEvent(mouseEvent);
                    }
                }
            }else{
                //---------mostrar en pantalla que es bruto y jugo donde no puede---------//
                cout<<"jugada invalida"<<endl;
            }
            //-------------compruebo que tenga uno de los dos donde jugar, si no se ahogo el juego--------------//
                bool JuegoAhogado=false;
                if(juego->getMovimientosPosibles()==0){
                    juego->cambiarTurnos();
                    if(juego->getMovimientosPosibles()==0){
                        JuegoAhogado = true;
                        juego->cambiarTurnos();
                    }else{
                        juego->cambiarTurnos();
                        cout<<"el jugador: "<<juego->getJugadorActual()<<"no tiene donde jugar, entonces cede puesto al siguiente"<<endl;
                        juego->cambiarTurnos();
                        if(opc==1 && juego->getJugadorActual() == 2) {//si esta jugando con la maquina entonces ella juega otra vez.
                            Inteligencia *minMax = new Inteligencia(juego);
                            Casilla* ideal = minMax->mejorJugada();
                            if(ideal!=NULL){
                                x = ideal->getColu(); y =ideal->getFila();
                                juego->turno(y,x);
                                juego->cambiarTurnos();
                                actualizar();
                                QGraphicsScene::mouseReleaseEvent(mouseEvent);
                            }
                        }

                    }
                }
                if(JuegoAhogado){
                    //--------------------mostrar que se tranco el juego---------------------//
                    cout<<"JUEGO AHOGADO"<<endl;
                }
                /*
                //----------------compruebo que el tablero no este lleno--------------------//
                bool tableroLLeno=false;
                for(int i = 0; i < 8; i++) {
                        for(int j = 0; j < 8; j++) {
                            if(juego->getTablero(i,j)->getEstado()==0){
                                tableroLLeno=false;break;
                            }else tableroLLeno = true;
                    }
                 }

                if(tableroLLeno){
                    //---------------------mostrar que la partida termino------------------//
                    cout<<"fin partida"<<endl;
                    int negras=juego->getJugador2Puntos();
                    int blancas= juego->getJugador1Puntos();
                    cout<<"negras: "<<negras<<" blancas: "<<blancas<<endl;
                    int contador=0;
                    //-------------para luego imprimir la proporcion de cada jugador en el tablero-----------//
                    for(int i = 0; i < 8; i++) {
                            for(int j = 0; j < 8; j++) {
                                if(contador<=blancas){
                                    juego->tablero[i][j]->setEstado(1);
                                }else juego->tablero[i][j]->setEstado(2);
                                contador++;
                        }
                     }
                    paint();
                }*/

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
    puntos_jugador1->setPlainText("J1: " + QString::number(juego->getJugador1Puntos()));
    if(opc==1)
        puntos_jugador2->setPlainText("PC: " + QString::number(juego->getJugador2Puntos()));
    else
        puntos_jugador2->setPlainText("J2: " + QString::number(juego->getJugador2Puntos()));
}

void Escena::actualizar() {

    int x = 0, y = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
                this->addRect(x,y,64,64,QPen(Qt::gray),QBrush(Qt::green));

            if (juego->tablero[i][j]->isMovimientoPosible()){
                if(juego->getJugadorActual()==1)
                    this->addEllipse(x+64/2-4,y+64/2-4,8,8,QPen(Qt::black), QBrush(Qt::black));
                else
                    this->addEllipse(x+64/2-4,y+64/2-4,8,8,QPen(Qt::white), QBrush(Qt::white));
            }
            if (juego->tablero[i][j]->getEstado() == 1)
                this->addEllipse(x,y,64,64,QPen(Qt::black), QBrush(Qt::black));
            if (juego->tablero[i][j]->getEstado() == 2)
                this->addEllipse(x,y,64,64,QPen(Qt::white), QBrush(Qt::white));
                x+=64;

        }
        x=0;
        y+=64;
    }

}
