#include "graphicsscene.h"
#include <QDebug>
#include <iostream>
#include "inteligencia.h"
#include <time.h>
using namespace std;

graphicsscene::graphicsscene(QObject *parent) :
    QGraphicsScene(parent)
{
    juego = new Juego();
    this->opc=1;
    this->setBackgroundBrush(Qt::gray);
}

void graphicsscene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
}

void graphicsscene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    if (mouseEvent->scenePos().x() <= 64*8 && mouseEvent->scenePos().x()>=0) {
        if (mouseEvent->scenePos().y() <= 64*8 && mouseEvent->scenePos().y()>=0) {
            cout<<"tablero antes de jugar maquina y humano:"<<endl;
            for(int i = 0; i < 8; i++) {
                    for(int j = 0; j < 8; j++) {
                        int d =(juego->getTablero(i,j))->getEstado();
                    cout << d<< " ";
                }
                cout << endl;
             }
            cout<<"puntaje jugador 1: "<<juego->getJugador1Puntos()<<" puntaje jugador 2: "<<juego->getJugador2Puntos()<<endl;
            qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
            qDebug() << "Fila: " << (int)mouseEvent->scenePos().y()/64;
            qDebug() << "Colu: " << (int)mouseEvent->scenePos().x()/64;
            x = mouseEvent->scenePos().x()/64;
            y = mouseEvent->scenePos().y()/64;
            juego->turno(y, x);\
            juego->cambiarTurnos();

            cout<<"jugo el juegador: "<<juego->getJugadorActual()<<endl;
            //opcion de jugar vs maquina
            paint();
            QGraphicsScene::mouseReleaseEvent(mouseEvent);
            if(opc==1){
//                if(true){
//                int seg=2;
//                time_t t1,t2;
//                  time(&t1);
//                do
//                      time(&t2);
//                while ((int)t2-t1 < seg);
//                }
                Inteligencia *minMax = new Inteligencia(juego);
                Casilla* ideal = minMax->mejorJugada();
                if(ideal!=NULL){
                    x = ideal->getColu(); y =ideal->getFila();
                    juego->turno(y,x);
                    juego->cambiarTurnos();

                    cout<<"jugo el juegador: "<<juego->getJugadorActual()<<endl;
                    cout<<"tablero despues de jugar maquina y humano:"<<endl;
                    for(int i = 0; i < 8; i++) {
                            for(int j = 0; j < 8; j++) {
                                int d =(juego->getTablero(i,j))->getEstado();
                            cout << d<< " ";
                        }
                        cout << endl;
                     }
                      paint();
                      QGraphicsScene::mouseReleaseEvent(mouseEvent);
                }else cout<<"FIN DEL JUEGO"<<endl;


            }

        }
    }

}

void graphicsscene::paint() {

    int x = 0, y = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
                this->addRect(x,y,64,64,QPen(Qt::gray),QBrush(Qt::cyan,Qt::Dense1Pattern));

            if (juego->tablero[i][j]->isMovimientoPosible())
                this->addEllipse(x+64/2-4,y+64/2-4,8,8,QPen(Qt::black), QBrush(Qt::black, Qt::Dense1Pattern));
            if (juego->tablero[i][j]->getEstado() == 1)
                this->addEllipse(x,y,64,64,QPen(Qt::white), QBrush(Qt::white, Qt::Dense2Pattern));
            if (juego->tablero[i][j]->getEstado() == 2)
                this->addEllipse(x,y,64,64,QPen(Qt::black), QBrush(Qt::black, Qt::Dense2Pattern));
                x+=64;

        }
        x=0;
        y+=64;
    }
}
