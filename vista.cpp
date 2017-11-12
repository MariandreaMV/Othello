#include "vista.h"

#include <QFontDatabase>

Vista::Vista()
{
    crearAcciones();
    crearMenus();

    scene = new Escena();
    scene->actualizar();
    scene->setSceneRect(0,0,64*10+64,64*8);
    this->setScene(scene);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ia_dificil->setEnabled(false);

    fuente.setPixelSize(12);
    fuente.setBold(true);
    fuente.setFamily("Arial");

    infor.setFont(fuente);
    infor.setText(tr("Hecho por:\n\nMariandrea Maldonado \tCI: 24693522\t\n"
                     "Pedro Labrador \t\tCI: 25587776\n\n"
                     "Proyecto Estructura de datos 2017"));
}

void Vista::crearAcciones()
{
    nuevoJuego = new QAction(tr("&Nuevo Juego"), this);
    nuevoJuego->setShortcuts(QKeySequence::New);
    nuevoJuego->setStatusTip(tr("Abrir un nuevo juego"));
    connect(nuevoJuego, &QAction::triggered, this, &Vista::slotNuevoJuego);

    pistas = new QAction(tr("Desactivar pistas"),this);
    pistas->setShortcuts(QKeySequence::Print);
    pistas->setStatusTip("Habilitar pistas?");
    connect(pistas, &QAction::triggered, this, &Vista::slotPistas);

    salir = new QAction(tr("S&alir"), this);
    salir->setShortcuts(QKeySequence::Quit);
    salir->setStatusTip(tr("Salir del juego"));
    connect(salir, &QAction::triggered, this, &Vista::slotCerrarJuego);



    jugador_v_jugador = new QAction(tr("Jugador vs &Jugador"), this);
    jugador_v_jugador->setStatusTip("Juega contra otra persona");
    connect(jugador_v_jugador, &QAction::triggered, this, &Vista::slotJugadorvJugador);

    ia_facil = new QAction(tr("&Facil"), this);
    ia_facil->setStatusTip("Juega contra una inteligencia artificial facil");
    connect(ia_facil, &QAction::triggered, this, &Vista::slotIaFacil);

    ia_dificil = new QAction(tr("&Dificil"), this);
    ia_dificil->setStatusTip("Juega contra una inteligencia artificial dificil");
    connect(ia_dificil, &QAction::triggered, this, &Vista::slotIaDificil);



    acercade = new QAction(tr("&Acerca de.. "), this);
    acercade->setShortcuts(QKeySequence::HelpContents);
    acercade->setStatusTip("Acerca..");
    connect(acercade, &QAction::triggered, this, &Vista::slotAcercade);
}

void Vista::crearMenus()
{
    barra = new QMenuBar();

    pestana_juego = barra->addMenu(tr("&Juego"));
    pestana_juego->addAction(nuevoJuego);
    pestana_juego->addAction(pistas);
    pestana_juego->addSeparator();
    pestana_juego->addAction(salir);

    pestana_opciones = barra->addMenu(tr("&Opciones"));
    pestana_opciones->addAction(jugador_v_jugador);
    subMenuIA = pestana_opciones->addMenu("Jugador vs IA");
    subMenuIA->addAction(ia_facil);
    subMenuIA->addAction(ia_dificil);

    pestana_ayuda = barra->addMenu(tr("&Ayuda"));
    pestana_ayuda->addAction(acercade);

}


//-----------SLOTS--------------
void Vista::slotNuevoJuego()
{
    scene->juego->reiniciar();
    scene->reiniciar();
}

void Vista::slotCerrarJuego()
{
    QCoreApplication::quit();
}

void Vista::slotJugadorvJugador()
{
    jugador_v_jugador->setEnabled(false);
    subMenuIA->setEnabled(true);
    ia_facil->setEnabled(true);
    ia_dificil->setEnabled(true);
    scene->setOpc(0);
    scene->juego->reiniciar();
    scene->reiniciar();
}

void Vista::slotIaFacil()
{
    jugador_v_jugador->setEnabled(true);
    ia_facil->setEnabled(false);
    ia_dificil->setEnabled(true);
    scene->setOpc(1);
    scene->setDificultad(1);
    scene->juego->reiniciar();
    scene->reiniciar();
}

void Vista::slotIaDificil()
{
    jugador_v_jugador->setEnabled(true);
    ia_dificil->setEnabled(false);
    ia_facil->setEnabled(true);
    scene->setOpc(1);
    scene->setDificultad(2);
    scene->juego->reiniciar();
    scene->reiniciar();
}

void Vista::slotPistas()
{
    if (scene->juego->getMostrarPistas()) {
        pistas->setText("Activar pistas");
        scene->juego->setMostrarPistas(false);
    } else {
        pistas->setText("Desactivar pistas");
        scene->juego->setMostrarPistas(true);
    }
    scene->reiniciar();
}

void Vista::slotAcercade()
{
    infor.show();
//QMessageBox::about(this, tr("Acerca de Othello"), tr("Hecho por:\n\nPedro Labrador \t\tCI: 25587776\nMariandrea Maldonado \tCI: 24693522\n\nProyecto Estructura de datos 2017"));

}
