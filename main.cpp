#include <QApplication>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QLayout>
#include <iostream>
#include <windows.h>
#include "vista.h"
#include "juego.h"

using namespace std;

void paint(Juego *juego, Escena *scene);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLayout *caja = new QVBoxLayout();
    Vista *view = new Vista();
    caja->setMenuBar(view->barra);
    caja->addWidget(view);
    QWidget *mostrar = new QWidget();
    mostrar->setLayout(caja);
    mostrar->setFixedSize(64*11+25,64*8+45);
    mostrar->show();

    return a.exec();
}
