#include <QApplication>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <iostream>
#include <windows.h>
#include "graphicsscene.h"
#include "juego.h"

using namespace std;

void paint(Juego *juego, graphicsscene *scene);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    graphicsscene *scene = new graphicsscene();
    QGraphicsView *view = new QGraphicsView();
    scene->paint();

    /*scene->juego->setMovimientosPosibles();
    juego->actualizarTablero();
    if(scene->is_clicked()) {
        paint(juego,scene);
        juego->turno(scene->get_last_y(), scene->get_last_x());
        juego->cambiarTurnos();
    }*/

//    Tile *ficha1 = new Tile(0,600,600,64,64);
  //  scene->addRect();
    QPushButton *boton = new QPushButton();

    boton->setText("Presioname");

   // boton->setGeometry(QRect(520, 64, 40, 20));
   // scene->addWidget(boton);
//    QGraphicsProxyWidget *proxy = scene->addWidget(boton);

    //scene->setSceneRect(0,0,64*8+64,64*8);
    view->setFixedSize(64*10,64*8);
    view->setScene(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();





    return a.exec();
}
