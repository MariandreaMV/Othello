#ifndef VISTA_H
#define VISTA_H
#include <QGraphicsView>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QMenuBar>
#include "escena.h"

class Vista : public QGraphicsView
{
    Escena *scene;
public:
    Vista();
    QMenuBar *barra;

private:
    void crearAcciones();
    void crearMenus();

    QMenu *pestana_juego;
    QMenu *pestana_opciones;
    QAction *nuevoJuego;
    QAction *pc;

private slots:
    void slotNuevoJuego();

};

#endif // VISTA_H
