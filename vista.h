#ifndef VISTA_H
#define VISTA_H
#include <QGraphicsView>
#include <QCoreApplication>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
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

    QFont fuente;

    QMenu *pestana_juego;
    QAction *nuevoJuego;
    QAction *pistas;
    QAction *salir;

    QMenu *pestana_opciones;
    QAction *jugador_v_jugador;
    QMenu *subMenuIA;
    QAction *ia_facil;
    QAction *ia_dificil;

    QMenu *pestana_ayuda;
    QAction *acercade;
    QMessageBox infor;

private slots:
    void slotNuevoJuego();
    void slotCerrarJuego();
    void slotJugadorvJugador();
    void slotIaFacil();
    void slotIaDificil();
    void slotPistas();
    void slotAcercade();

};

#endif // VISTA_H
