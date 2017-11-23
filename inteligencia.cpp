#include "inteligencia.h"

Inteligencia::Inteligencia()
{

}

Inteligencia::Inteligencia(Juego *juego)
{

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

}

Casilla *Inteligencia::mejorJugada()
{
    Casilla *mejor_casilla= new Casilla();
    MyLinkedList<int> *max=new MyLinkedList<int>;
    if(hayMovimientosPosibles!=0){
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(tablero[i][j]->isMovimientoPosible()){
                     Juego *evaluacion = new Juego(tablero,i,j);
                     max->agregar(evaluacion->getMejorJugada());
                     delete evaluacion;
                }
            }
        }

        int cont=0, posicion=0;
        int mayor=-9999,elemento;
        while(!max->isEmpty()){
            max->eliminar(elemento);
            if(elemento>mayor){
                mayor=elemento;
               posicion=cont;
            }
             cont++;
        }

        delete max;

        int cont2=0;
        for(int i = 0; i < 8; i++) {
          for(int j = 0; j < 8; j++) {
            if(tablero[i][j]->isMovimientoPosible()){
               if(cont2==posicion){
                mejor_casilla=tablero[i][j];
               }else delete tablero[i][j];
               cont2++;
             }else delete tablero[i][j];
          }
        }

    }else mejor_casilla=NULL;//si no hay jugadas

    return mejor_casilla;
}

Casilla *Inteligencia::jugadaRandom()
{
    Casilla *mejor_casilla= new Casilla();
    int num;
    srand(time(NULL));
    int cont=0;

    for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if(tablero[i][j]->isMovimientoPosible()) cont++;

            }
     }

    hayMovimientosPosibles=cont;

    num = 0 + rand() % (hayMovimientosPosibles);
    cout<<"mov posibles: "<<hayMovimientosPosibles<<" random: "<<num<<endl;
    if(hayMovimientosPosibles!=0){
        for(int i = 0; i < 8; i++) {
          for(int j = 0; j < 8; j++) {
            if(tablero[i][j]->isMovimientoPosible()){
                cout<<"jugada podible: "<<tablero[i][j]->getFila()<<tablero[i][j]->getColu()<<endl;
               }
             }
          }

        int cont2=0;
        for(int i = 0; i < 8; i++) {
          for(int j = 0; j < 8; j++) {
            if(tablero[i][j]->isMovimientoPosible()){
                cout<<cont2<<endl;
               if(cont2==num){
                cout<<"existe"<<endl;
                mejor_casilla=tablero[i][j];
                return mejor_casilla;
               }
               cont2++;
             }
          }
        }
    }else
        mejor_casilla=NULL;//si no hay jugadas

    return mejor_casilla;
}
