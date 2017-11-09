#ifndef JUGADA_H
#define JUGADA_H
#include "ListaEnlazada.h"
#include "casilla.h"
#define TAM 8

class Jugada
{
    int x, y;
    int f;
public:
    Jugada();
    Jugada(Casilla *tablero[TAM][TAM]);
    Casilla *tablero[TAM][TAM];
    void calcular_f();
    int get_x() { return x; }
    int get_y() { return y; }
    int get_f() { return f; }
    void set_x(int x) { this->x = x; }
    void set_y(int y) { this->y = y; }
    void set_f(int f) { this->f = f; }
    bool operator<( Jugada &x ) { return this->f<x.f; }
};

#endif // JUGADA_H
