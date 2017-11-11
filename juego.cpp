#include "juego.h"

Juego::Juego() {

    jugadorActual = 1;
    movimientosPosibles = 0;
    pistas = true;

    iniciarTablero();
    setMovimientosPosibles();

}


//------------------heuristica--------------------------

Juego::Juego(Casilla *tabC[TAM][TAM],int i,int j)
{
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tablero[i][j] = new Casilla();
            tablero[i][j]->setEstado(tabC[i][j]->getEstado());
            tablero[i][j]->setMovimientoPosible(tabC[i][j]->isMovimientoPosible());
            tablero[i][j]->setPosicion(tabC[i][j]->getFila(),tabC[i][j]->getColu());
            tablero[i][j]->setID(tabC[i][j]->getID());
        }
    }
    jugadorActual=2;
    turno(i,j);
    cambiarTurnos();
}

int Juego::getMejorJugada()
{
    MyLinkedList<int> puntajes3;
    Casilla *tabC[TAM][TAM];

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabC[i][j] = new Casilla();
            tabC[i][j]->setEstado(tablero[i][j]->getEstado());
            tabC[i][j]->setMovimientoPosible(tablero[i][j]->isMovimientoPosible());
            tabC[i][j]->setPosicion(tablero[i][j]->getFila(),tabC[i][j]->getColu());
            tabC[i][j]->setID(tablero[i][j]->getID());
        }
    }

    for(int i = 0; i < 8; i++) {
       for(int j = 0; j < 8; j++) {
           if(tablero[i][j]->isMovimientoPosible()){

             for (int i = 0; i < TAM; i++) {
                 for (int j = 0; j < TAM; j++) {
                     tablero[i][j] = new Casilla();
                     tablero[i][j]->setEstado(tabC[i][j]->getEstado());
                     tablero[i][j]->setMovimientoPosible(tabC[i][j]->isMovimientoPosible());
                     tablero[i][j]->setPosicion(tabC[i][j]->getFila(),tabC[i][j]->getColu());
                     tablero[i][j]->setID(tabC[i][j]->getID());
                 }
             }

             turno(i,j);
             puntajes3.agregar(getJugador2Puntos()-getJugador1Puntos());//resto las respectivas cantidades de piezas para determinar cual es la mejor opcion luego.

           }
        }
    }
    //puntajes3.imprimir();

    int cont=0, posicion=0;
    int mayor=-9999,elemento;
    while(!puntajes3.isEmpty()){
        puntajes3.eliminar(elemento);
        if(elemento>mayor){
            mayor=elemento;
           posicion=cont;
        }
       cont++;
    }

    return mayor;//solo me impora el numero mayor de negras que yo pueda tener en las n jugadas de esta opcion

}

//---------------------------fin heuristica--------------

void Juego::iniciarTablero () {
    int numCasilla = 0;

    // Iniciar el tablero
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tablero[i][j] = new Casilla();

            tablero[i][j]->setID(numCasilla);
            tablero[i][j]->setEstado(0);
            tablero[i][j]->setMovimientoPosible(false);
            tablero[i][j]->setPosicion(i, j);

            numCasilla++;
        }
    }
    // piezas iniciales
    tablero[3][3]->setEstado(1);
    tablero[4][4]->setEstado(1);
    tablero[3][4]->setEstado(2);
    tablero[4][3]->setEstado(2);
}

void Juego::setMovimientosPosibles() {
    bool enemigoEncontrado = false; // Si la piea enemiga es detectada
    movimientosPosibles = 0; 		// Cuantos movimientos posibles pueden ser hechos?

    //Pone el numero del enemigo
    int enemigo;
    if (jugadorActual == 1) {
        enemigo = 2;
    } else {
        enemigo = 1;
    }
    int estadoCasillaActual;

    // Limpia los estados anteriores.
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tablero[i][j]->setMovimientoPosible(false);
        }
    }

    // Se verifica cada casilla para ver si hay movimiento posible
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            enemigoEncontrado = false;


            /* Encuentra la siguiente casilla vacia
                - Verifica lls columnas en la fila hasta que encuentre una columna vacia
                - si todas las columnas en la fila se verificaron y no hay casillas vacias
                  saltará a la siguiente fila con el break
                - la siguiente fila es verificada de la misma manera anterior
                - si no hay casillas disponibles el juego termina
            */
            estadoCasillaActual = tablero[i][j]->getEstado();
            while (estadoCasillaActual != 0) {
                j++;
                if (j < TAM) {
                    estadoCasillaActual = tablero[i][j]->getEstado();
                } else {
                    j = 0;
                    i++;
                    if (i >= TAM)
                        return;
                    else
                        estadoCasillaActual = tablero[i][j]->getEstado();
                }
            }


            //ahora esa casilla vacia encontrada se verifica en todas direcciones para un movimiento valido

            // CASILLAS DE LA IZQUIERDA
            for (int k = j - 1; k >= 0; k--) {
                if (tablero[i][k]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero[i][k]->getEstado() == jugadorActual) {
                        tablero[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
            }
            enemigoEncontrado = false;


            // CASILLAS DE LA DERECHA
            for (int k = j + 1; k < TAM; k++) {
                if (tablero[i][k]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero[i][k]->getEstado() == jugadorActual) {
                        tablero[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
            }
            enemigoEncontrado = false;


            // CASILLAS DE ARRIBA
            for (int k = i - 1; k >= 0; k--) {
                if (tablero[k][j]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero[k][j]->getEstado() == jugadorActual) {
                        tablero[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
            }
            enemigoEncontrado = false;

            // CASILLAS DE ABAJO
            for (int k = i + 1; k < TAM; k++) {
                if (tablero[k][j]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero[k][j]->getEstado() == jugadorActual) {
                        tablero[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
            }
            enemigoEncontrado = false;


            int r, c;


            // DIAGONAL SUPERIOR IZQUIERDA
            r = i - 1;
            c = j - 1;
            while (r >= 0 && c >= 0) {
                if (tablero[r][c]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero[r][c]->getEstado() == jugadorActual) {
                        tablero[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
                r--;
                c--;
            }
            enemigoEncontrado = false;


            // DIAGONAL SUPERIOR DERECHA
            r = i - 1;
            c = j + 1;
            while (r >= 0 && c < TAM) {
                if (tablero[r][c]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero[r][c]->getEstado() == jugadorActual) {
                        tablero[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
                r--;
                c++;
            }
            enemigoEncontrado = false;


            // DIAGONAL INFERIOR IZQUIERDA
            r = i + 1;
            c = j - 1;
            while (r < TAM && c >= 0) {
                if (tablero[r][c]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero[r][c]->getEstado() == jugadorActual)
                    {
                        tablero[i][j]->setMovimientoPosible(true);
                        movimientosPosibles++;
                    }
                    enemigoEncontrado = false;
                    break;
                }
                r++;
                c--;
            }
            enemigoEncontrado = false;


            // DIAGONAL INFERIOR DERECHA
            r = i + 1;
            c = j + 1;
            while (r < TAM && c < TAM)
            {
                if (tablero[r][c]->getEstado() == enemigo)
                    enemigoEncontrado = true;
                else {
                    if (enemigoEncontrado && tablero[r][c]->getEstado() == jugadorActual) {
                        tablero[i][j]->setMovimientoPosible(true);
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

void Juego::actualizarTablero() {
    jugador1Puntos = jugador2Puntos = 0;

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {

            //implementar colores en la clase juego
            //y actualizar segun sean

            // Permitir que los posbles movimientos sean visibles o clickeables.. implementar
            if(tablero[i][j]->isMovimientoPosible()) {

                // Mostrar pistas..
                if (pistas) {

                } else {

                }
            }
        }
    }
}

void Juego::reiniciar() {

    // regresar a las casillas a sus valores por defecto
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tablero[i][j]->setMovimientoPosible(false);
            tablero[i][j]->setEstado(0);
            tablero[i][j]->setPosicion(i, j);
        }
    }

    // Reiniciar variables
    jugador1Puntos = jugador2Puntos = 0;
    jugadorActual = 1;
    movimientosPosibles = 0;

    // Reiniciar las 4 casilals centrales
    tablero[3][3]->setEstado(1);
    tablero[4][4]->setEstado(1);
    tablero[3][4]->setEstado(2);
    tablero[4][3]->setEstado(2);

    // Actualizar tablero..
    setMovimientosPosibles();
    actualizarTablero();
}

void Juego::cambiarTurnos() {
    if (jugadorActual == 1) {
        jugadorActual = 2;
    } else {
        jugadorActual = 1;
    }
    setMovimientosPosibles();
}

void Juego::turno(int fila, int colu) {
    bool enemigoEncontrado = false;
    int enemigo;
    if (jugadorActual == 1)
        enemigo = 2;
    else
        enemigo = 1;

    enemigoEncontrado = false;

    for (int k = colu - 1; k >= 0; k--) {
        if (tablero[fila][k]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero[fila][k]->getEstado() == jugadorActual) {
                while (k + 1 <= colu) {
                    k++;
                    tablero[fila][k]->setEstado(jugadorActual);
                }
            }
            break;
        }
    }
    enemigoEncontrado = false;

    for (int k = colu + 1; k < TAM; k++) {
        if (tablero[fila][k]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero[fila][k]->getEstado() == jugadorActual) {
                while (k - 1 >= colu) {
                    k--;
                    tablero[fila][k]->setEstado(jugadorActual);
                }
            }
            break;
        }
    }
    enemigoEncontrado = false;

    for (int k = fila - 1; k >= 0; k--) {
        if (tablero[k][colu]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero[k][colu]->getEstado() == jugadorActual) {
                while (k + 1 <= fila) {
                    k++;
                    tablero[k][colu]->setEstado(jugadorActual);
                }
            }
            break;
        }
    }
    enemigoEncontrado = false;

    for (int k = fila + 1; k < TAM; k++) {
        if (tablero[k][colu]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero[k][colu]->getEstado() == jugadorActual) {
                while (k - 1 >= fila) {
                    k--;
                    tablero[k][colu]->setEstado(jugadorActual);
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
        if (tablero[r][c]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero[r][c]->getEstado() == jugadorActual) {
                while ((r + 1) <= fila && (c + 1) <= colu) {
                    r++;
                    c++;
                    tablero[r][c]->setEstado(jugadorActual);
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
        if (tablero[r][c]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero[r][c]->getEstado() == jugadorActual) {
                while ((r + 1) <= fila && (c - 1) >= colu) {
                    r++;
                    c--;
                    tablero[r][c]->setEstado(jugadorActual);
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
        if (tablero[r][c]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero[r][c]->getEstado() == jugadorActual) {
                while ((r - 1) >= fila && (c + 1) <= colu) {
                    r--;
                    c++;
                    tablero[r][c]->setEstado(jugadorActual);
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
        if (tablero[r][c]->getEstado() == enemigo)
            enemigoEncontrado = true;
        else {
            if (enemigoEncontrado && tablero[r][c]->getEstado() == jugadorActual) {
                while ((r - 1) >= fila && (c - 1) >= colu) {
                    r--;
                    c--;
                    tablero[r][c]->setEstado(jugadorActual);
                }
            }
            break;
        }
        r++;
        c++;
    }

}

int Juego::getJugador1Puntos()
{   jugador1Puntos=0;
    jugador2Puntos=0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
                if(tablero[i][j]->getEstado()==1){
                   jugador1Puntos++;
                }
                if(tablero[i][j]->getEstado()==2){
                   jugador2Puntos++;
                }
        }
     }
    return jugador1Puntos;
}

int Juego::getJugador2Puntos()
{
    getJugador1Puntos();
    return jugador2Puntos;
}


