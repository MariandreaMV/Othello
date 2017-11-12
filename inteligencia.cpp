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
                delete tablero;
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



Casilla *Inteligencia::mejorJugadaRandom()
{
    int num, c=0;
    srand(time(NULL));
    num = 0 + rand() % (hayMovimientosPosibles);
    Casilla *mejor_casilla= new Casilla();
    cout<<"posibles jugadas: "<<hayMovimientosPosibles<<" random: "<<num<<endl;
    if(hayMovimientosPosibles!=0){
        for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    if(tablero[i][j]->isMovimientoPosible()){
                       cout<<c<<endl;
                        if(c==num){
                          mejor_casilla=tablero[i][j];
                          cout<<"encontrada"<<endl;
                          return mejor_casilla;
                        }
                       c++;
                    }
                }
         }
    }
    mejor_casilla= NULL;//si no hay jugadas

    return mejor_casilla;
}
