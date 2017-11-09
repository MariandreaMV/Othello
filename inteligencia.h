#ifndef INTELIGENCIA_H
#define INTELIGENCIA_H
#include "juego.h"
#include <iostream>
using namespace std;

class Inteligencia
{

    Casilla *tablero[TAM][TAM];
    int hayMovimientosPosibles;

public:
    Inteligencia();
    Inteligencia(Juego *ju);
    Casilla* mejorJugada();
};

#endif // INTELIGENCIA_H
