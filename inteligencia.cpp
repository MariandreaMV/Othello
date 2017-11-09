#include "inteligencia.h"

Inteligencia::Inteligencia()
{

}

Inteligencia::Inteligencia(Juego *juego)
{


    /*
            int id;            		// ID de la casilla
            bool movimientoPosible; // Si hay un movimiento posible para un jugador
            int estado;        		// 0 = nada, 1 = jugador1, 2 = jugador2
            int fila;           	// Fila de la casila
            int colu;
    */
    hayMovimientosPosibles=juego->getMovimientosPosibles();
    for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                tablero[i][j] = new Casilla();
                tablero[i][j]->setEstado(juego->getTablero(i,j)->getEstado());
                tablero[i][j]->setMovimientoPosible(juego->getTablero(i,j)->isMovimientoPosible());
                tablero[i][j]->setPosicion(juego->getTablero(i,j)->getFila(),juego->getTablero(i,j)->getColu());
                tablero[i][j]->setID(juego->getTablero(i,j)->getID());
            }
     }
    cout<<"tablero despues de la jugada del humano"<<endl;
    for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
            cout << tablero[i][j]->getEstado() << " ";
        }
        cout << endl;
     }

}

Casilla *Inteligencia::mejorJugada()
{
    Casilla *mejor_casilla= new Casilla();
    MyLinkedList<int> max;
    if(hayMovimientosPosibles!=0){
        for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    if(tablero[i][j]->isMovimientoPosible()){
                        cout<<"posible jugada "<<tablero[i][j]->getFila()<<" "<<tablero[i][j]->getColu()<<endl;

                        Juego *evaluacion = new Juego(tablero,i,j);
                       // mejor_casilla= tablero[i][j];
                        max.agregar(evaluacion->getMejorJugada());
                    }
            }
         }

        int cont=0, posicion=0;
        int mayor=-9999,elemento;
        while(!max.isEmpty()){
            max.eliminar(elemento);
            if(elemento>mayor){
                mayor=elemento;
               posicion=cont;
            }
             cont++;
        }

        int cont2=0;
        for(int i = 0; i < 8; i++) {
          for(int j = 0; j < 8; j++) {
            if(tablero[i][j]->isMovimientoPosible()){
               if(cont2==posicion){
                mejor_casilla=tablero[i][j];
                //cout<<"la mejor jugada de este ciclo es: "<<mejorCasilla->getColu()<<","<<mejorCasilla->getFila()<<endl;
                return mejor_casilla;
               }
               cont2++;
             }
          }
        }
    }else
        mejor_casilla=NULL;

    return mejor_casilla;
}
