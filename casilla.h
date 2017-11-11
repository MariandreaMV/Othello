#ifndef CASILLA_H
#define CASILLA_H
#include <iostream>
using namespace std;
class Casilla {
    private:
        int id;            		// ID de la casilla
        bool movimientoPosible; // Si hay un movimiento posible para un jugador
        int estado;        		// 0 = nada, 1 = jugador1, 2 = jugador2
        int fila;           	// Fila de la casila
        int colu;          		// Columna de la casilla
    public:

        Casilla();

        void setID(int x) { id = x; }
        int getID() { return id; }

        void setMovimientoPosible(bool _movimientoPosible) { movimientoPosible = _movimientoPosible; }
        bool isMovimientoPosible() { return movimientoPosible; }

        void setEstado(int x) { estado = x; }
        int getEstado() { return estado; }

        void setPosicion(int _fila, int _colu);
        int getFila() { return fila; }
        int getColu() { return colu; }
};

#endif // CASILLA_H
