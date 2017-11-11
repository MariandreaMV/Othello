#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    caja = new QVBoxLayout();
    view = new Vista();
    mostrar = new QWidget();

    caja->setMenuBar(view->barra);
    caja->addWidget(view);

    mostrar->setLayout(caja);
    mostrar->setFixedSize(64*11+25,64*8+45);
    setWindowIcon(QIcon(":/Imagen/logo.png"));
}

void MainWindow::show()
{
    mostrar->show();
}
