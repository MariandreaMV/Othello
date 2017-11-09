#ifndef IA_H
#define IA_H
#include "casilla.h"
#include "jugada.h"

#define TAM 8

class IA
{
    int jugadorActual;
    Casilla *tablero_actual[TAM][TAM];
public:
    IA();
    Jugada min_max(Casilla *tablero[TAM][TAM], int jug);
    void setMovimientosPosibles(Casilla *tablero_actual[TAM][TAM]);
    Jugada turno(int fila, int colu, Casilla *tablero[TAM][TAM]);
    void cambiarTurnos();
};

#endif // IA_H
