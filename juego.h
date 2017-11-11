#ifndef JUEGO_H
#define JUEGO_H
#include "Casilla.h"
#include "MyLinkedList.h"

#define TAM 8

class Juego {
    private:
        int jugador1Puntos; 		// Puntos del jugador 1
        int jugador2Puntos; 		// Puntos del jugador 2
        int jugadorActual; 			// De quien es el turno
        int movimientosPosibles; 	// Cuantos movimientos posibles hay para el jugador actual?
        bool pistas;

        void iniciarTablero();
    public:
        Casilla *tablero[8][8];
        Casilla *tabCopia[TAM][TAM];

        Juego();
        Juego(Casilla * tabC[8][8],int i,int j);
        void setMovimientosPosibles();
        void reiniciar();
        void cambiarTurnos();
        void turno(int fila, int colu);

        int getJugador1Puntos ();
        int getJugador2Puntos ();

        int getJugadorActual () { return jugadorActual; }
        int getMovimientosPosibles () { return movimientosPosibles; }

        void setMostrarPistas (bool mostrar) { pistas = mostrar; }
        bool getMostrarPistas () { return pistas; }
        Casilla *getTablero(int f,int c){ return tablero[f][c];}
        int getMejorJugada();
};

#endif // JUEGO_H
