#include "vista.h"

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

}

void Vista::crearAcciones()
{
    nuevoJuego = new QAction(tr("&Nuevo Juego"), this);
    nuevoJuego->setShortcuts(QKeySequence::New);
    nuevoJuego->setStatusTip(tr("Abrir un nuevo juego"));
    connect(nuevoJuego, &QAction::triggered, this, &Vista::slotNuevoJuego);

   /* openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
 //   connect(openAct, &QAction::triggered, this, &MainWindow::open);*/
}

void Vista::crearMenus()
{
    barra = new QMenuBar();

    pestana_juego = barra->addMenu(tr("&Juego"));
    pestana_juego->addAction(nuevoJuego);
    //pestana_juego->addAction(openAct);
    pestana_juego->addSeparator();
    //pestana_juego->addAction(this->close());

    /*editMenu = barra->addMenu(tr("&Edit"));
    editMenu->addSeparator();*/
}

void Vista::slotNuevoJuego()
{
    scene->juego->reiniciar();
    scene->reiniciar();
    scene->actualizar();
}


