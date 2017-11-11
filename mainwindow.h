#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include "vista.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLayout *caja;
    Vista *view;
    QWidget *mostrar;
public:
    MainWindow(QWidget *parent = 0);
    void show();
};
#endif // MAINWINDOW_H
