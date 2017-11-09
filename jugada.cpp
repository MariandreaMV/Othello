#include "jugada.h"

Jugada::Jugada()
{

}

Jugada::Jugada(Casilla *tablero[8][8])
{
    for (int i = 0; i< 8; i++)
        for(int j = 0; j < 8; j++)
            this->tablero[i][j] = tablero[i][j];
}

void Jugada::calcular_f()
{
    int fg = 0;
    int fp = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tablero[i][j]->getEstado() == 1)
                fp++;
            else if (tablero[i][j]->getEstado() == 2)
                fg++;
        }
    }
    this->f = fg - fp;
}
