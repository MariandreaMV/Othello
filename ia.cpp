#include "ia.h"
#include "QDebug"

IA::IA()
{

}

Jugada IA::min_max(Casilla *tablero[8][8], int jug)
{
    //cambiarTurnos();
    //Casilla *tablero_actual[TAM][TAM];
    for (int i = 0; i< 8; i++)
        for(int j = 0; j < 8; j++)
            tablero_actual[i][j] = tablero[i][j];
    //setMovimientosPosibles(tablero_actual);

    jugadorActual = jug;

    ListaEnlazada<Jugada> *listaJugadas_max;
    ListaEnlazada<Jugada> *listaJugadas_min;

    for (int j = 0; j < TAM; j++) {
        for (int k = 0; k < TAM; k++) {
            for (int h = 0; h< TAM; h++)
                for(int n = 0; n < TAM; n++)
                    tablero_actual[h][n] = tablero[h][n];
            if (tablero_actual[j][k]->isMovimientoPosible()) {

                Jugada act = turno(k, j, tablero_actual);
                /*act.set_x(j);
                act.set_y(k);
                act.calcular_f();*/
                for (int i = 0; i < 8; i++)
                    qDebug() <<"["<< k << "," << j << "]"<< act.tablero[i][0]->getEstado() << " " << act.tablero[i][1]->getEstado() << " " << act.tablero[i][2]->getEstado() << " " << act.tablero[i][3]->getEstado() << " " << act.tablero[i][4]->getEstado() << " " << act.tablero[i][5]->getEstado() << " " << act.tablero[i][6]->getEstado() << " " << act.tablero[i][7]->getEstado();
                qDebug() << " ";
//                    qDebug() << tablero_actual[4][2]->getEstado() << " " << tablero[4][2]->getEstado();
//                for (int l = 0; l < TAM; l++) {
//                    for (int m = 0; m < TAM; m++) {
//                        if (act.tablero[l][m]->isMovimientoPosible()) {
//                            Jugada act2 = turno(l, m, act.tablero);
//                            act2.set_x(l);
//                            act2.set_y(m);
//                            act2.calcular_f();

//                            listaJugadas_min->Anadir(act2);
//                        }

//                    }
//                }
//                Nodo<Jugada> *valor = listaJugadas_min.get_inicio();
//                listaJugadas_max.Anadir(valor->getValor());
//                qDebug() << valor->getValor().get_f();
            }

        }
    }


}

void IA::setMovimientosPosibles(Casilla *tablero_actual[TAM][TAM]) {

    bool enemigoEncontrado = false;
    int movimientosPosibles = 0;

    int enemigo;
    if (jugadorActual == 1) {
        enemigo = 2;
    } else {
        enemigo = 1;
    }
    int estadoCasillaActual;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tablero_actual[i][j]->setMovimientoPosible(false);
        }
    }

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            enemigoEncontrado = false;

            estadoCasillaActual = tablero_actual[i][j]->getEstado();
            while (estadoCasillaActual != 0) {
                j++;
                if (j < TAM) {
                    estadoCasillaActual = tablero_actual[i][j]->getEstado();
                } else {
                    j = 0;
                    i++;
                    if (i >= TAM)
                        return;
                    else
                        estadoCasillaActual = tablero_actual[i][j]->getEstado();
                }
            }

            for (int k = j - 1; k >= 0; k--) {
                if (tablero_actual[i][k]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero_actual[i][k]->getEstado() == jugadorActual) {
                        tablero_actual[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
            }
            enemigoEncontrado = false;

            for (int k = j + 1; k < TAM; k++) {
                if (tablero_actual[i][k]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero_actual[i][k]->getEstado() == jugadorActual) {
                        tablero_actual[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
            }
            enemigoEncontrado = false;

            for (int k = i - 1; k >= 0; k--) {
                if (tablero_actual[k][j]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero_actual[k][j]->getEstado() == jugadorActual) {
                        tablero_actual[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
            }
            enemigoEncontrado = false;

            for (int k = i + 1; k < TAM; k++) {
                if (tablero_actual[k][j]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero_actual[k][j]->getEstado() == jugadorActual) {
                        tablero_actual[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
            }
            enemigoEncontrado = false;


            int r, c;
            r = i - 1;
            c = j - 1;
            while (r >= 0 && c >= 0) {
                if (tablero_actual[r][c]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero_actual[r][c]->getEstado() == jugadorActual) {
                        tablero_actual[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
                r--;
                c--;
            }
            enemigoEncontrado = false;

            r = i - 1;
            c = j + 1;
            while (r >= 0 && c < TAM) {
                if (tablero_actual[r][c]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero_actual[r][c]->getEstado() == jugadorActual) {
                        tablero_actual[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
                r--;
                c++;
            }
            enemigoEncontrado = false;

            r = i + 1;
            c = j - 1;
            while (r < TAM && c >= 0) {
                if (tablero_actual[r][c]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero_actual[r][c]->getEstado() == jugadorActual)
                    {
                        tablero_actual[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
                r++;
                c--;
            }
            enemigoEncontrado = false;

            r = i + 1;
            c = j + 1;
            while (r < TAM && c < TAM)
            {
                if (tablero_actual[r][c]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero_actual[r][c]->getEstado() == jugadorActual) {
                        tablero_actual[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
                r++;
                c++;
            }
        }
    }
}

void IA::cambiarTurnos() {
    if (jugadorActual == 1) {
        jugadorActual = 2;
    } else {
        jugadorActual = 1;
    }
}

Jugada IA::turno(int fila, int colu, Casilla *tablero[TAM][TAM]) {

    Casilla *tablero_actual[TAM][TAM];
    for (int i = 0; i< 8; i++)
        for(int j = 0; j < 8; j++)
            tablero_actual[i][j] = tablero[i][j];

    bool enemigoEncontrado = false;

    int enemigo;
    if (jugadorActual == 1)
        enemigo = 2;
    else
        enemigo = 1;

    enemigoEncontrado = false;

    for (int k = colu - 1; k >= 0; k--) {
        if (tablero_actual[fila][k]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero_actual[fila][k]->getEstado() == jugadorActual) {
                while (k + 1 <= colu) {
                    k++;
                    tablero_actual[fila][k]->setEstado(jugadorActual);
                }
            }
            break;
        }
    }
    enemigoEncontrado = false;

    for (int k = colu + 1; k < TAM; k++) {
        if (tablero_actual[fila][k]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero_actual[fila][k]->getEstado() == jugadorActual) {
                while (k - 1 >= colu) {
                    k--;
                    tablero_actual[fila][k]->setEstado(jugadorActual);
                }
            }
            break;
        }
    }
    enemigoEncontrado = false;

    for (int k = fila - 1; k >= 0; k--) {
        if (tablero_actual[k][colu]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero_actual[k][colu]->getEstado() == jugadorActual) {
                while (k + 1 <= fila) {
                    k++;
                    tablero_actual[k][colu]->setEstado(jugadorActual);
                }
            }
            break;
        }
    }
    enemigoEncontrado = false;

    for (int k = fila + 1; k < TAM; k++) {
        if (tablero_actual[k][colu]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero_actual[k][colu]->getEstado() == jugadorActual) {
                while (k - 1 >= fila) {
                    k--;
                    tablero_actual[k][colu]->setEstado(jugadorActual);
                }
            }
            break;
        }
    }
    enemigoEncontrado = false;

    int r, c;

    r = fila - 1;
    c = colu - 1;
    while (r >= 0 && c >= 0) {
        if (tablero_actual[r][c]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero_actual[r][c]->getEstado() == jugadorActual) {
                while ((r + 1) <= fila && (c + 1) <= colu) {
                    r++;
                    c++;
                    tablero_actual[r][c]->setEstado(jugadorActual);
                }
            }
            break;
        }
        r--;
        c--;
    }
    enemigoEncontrado = false;

    r = fila - 1;
    c = colu + 1;

    while (r >= 0 && c < TAM) {
        if (tablero_actual[r][c]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero_actual[r][c]->getEstado() == jugadorActual) {
                while ((r + 1) <= fila && (c - 1) >= colu) {
                    r++;
                    c--;
                    tablero_actual[r][c]->setEstado(jugadorActual);
                }
            }
            break;
        }
        r--;
        c++;
    }
    enemigoEncontrado = false;

    r = fila + 1;
    c = colu - 1;
    while (r < TAM && c >= 0) {
        if (tablero_actual[r][c]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero_actual[r][c]->getEstado() == jugadorActual) {
                while ((r - 1) >= fila && (c + 1) <= colu) {
                    r--;
                    c++;
                    tablero_actual[r][c]->setEstado(jugadorActual);
                }
            }
            break;
        }
        r++;
        c--;
    }

    r = fila + 1;
    c = colu + 1;

    while (r < TAM && c < TAM) {
        if (tablero_actual[r][c]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero_actual[r][c]->getEstado() == jugadorActual) {
                while ((r - 1) >= fila && (c - 1) >= colu) {
                    r--;
                    c--;
                    tablero_actual[r][c]->setEstado(jugadorActual);
                }
            }
            break;
        }
        r++;
        c++;
    }

    setMovimientosPosibles(tablero_actual);
    //cambiarTurnos();

    Jugada act(tablero_actual);

    return act;
}
