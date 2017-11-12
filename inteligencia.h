#ifndef INTELIGENCIA_H
#define INTELIGENCIA_H
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "juego.h"
using namespace std;

class Inteligencia
{

    Casilla *tablero[TAM][TAM];
    int hayMovimientosPosibles;

public:
    Inteligencia();
    Inteligencia(Juego *ju);
    Casilla* mejorJugada();
    Casilla* jugadaRandom();
};

#endif // INTELIGENCIA_H
