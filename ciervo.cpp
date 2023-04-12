#include "ciervo.h"
#include "mesetas.h"
#include "pastizal.h"
#include "montania.h"
#include <iostream>

char ciervo::getRepresentacion() const
{
    return representacion;
}

void ciervo::setRepresentacion(char newRepresentacion)
{
    this->representacion = newRepresentacion;
}

eciervo ciervo::getStruct()
{
    eciervo aux;
    aux.hambre = this->hambre;
    aux.recienSeteado = this->recienSeteado;
    aux.representacion = this->representacion;

    return aux;
}

void ciervo::movimiento()
{
    this->recienSeteado=true;
}

bool ciervo::getRecienSeteado() const
{
    return this->recienSeteado;
}

void ciervo::setRecienSeteado(bool newRecienSeteado)
{
    recienSeteado = newRecienSeteado;
}

void ciervo::alimentarse(Elemento* casilla, int indice) //se invoca al caer a una casilla, si tiene comida come, gana hambre y muere, funciona pero las casillas del mapa cambian a veces su icono sin razon
{
    if(casilla->getRepresentacionOriginal() == '*') //si es meseta el ciervo gana hambre
    {
        this->hambre++;
        if(hambre==4){ //el ciervo muere

            reinterpret_cast< Mesetas * >( casilla )->quitarCiervo(indice); //me borro de la posicion anterior
            //delete this; //el ciervo muere
        }

    }else{// es un pastizal

        if(reinterpret_cast< Pastizal * >( casilla )->estaSecoEstePastizal() ) //si el pastizal esta seco el ciervo no se alimenta
        {
            this->hambre++;
            if(hambre==4){ //el ciervo muere, agrego 1 porque el primer seteo no cuenta
                reinterpret_cast< Pastizal * >( casilla )->quitarCiervo(indice);
                //delete this; //el ciervo muere
            }

        }else{ //el ciervo come

            this->hambre=0;
            reinterpret_cast< Pastizal * >( casilla )->secar(); //el pastizal es comido
        }
    }

}

bool ciervo::intentarMoverseDerecha(Mapa* mapa, int x, int y, int indice)
{

    if( y+1 < mapa->getHorizontal() )
    {

        if(mapa->getElemento(x,y+1)->getRepresentacionOriginal() != '#') //si la derecha es una casilla valida
        {

            //ME BORRO DE LA POSICION ANTERIOR
            if( mapa->getElemento(x,y)->getRepresentacionOriginal() == '*' ) //debo saber q tipo de casilla era donde estaba antes el ciervo para usar correctamente el quitar ciervo
            {
                reinterpret_cast< Mesetas * >( mapa->getElemento(x,y) )->quitarCiervo(indice); //me borro de la posicion anterior
            }else{
                reinterpret_cast< Pastizal * >( mapa->getElemento(x,y) )->quitarCiervo(indice); //me borro de la posicion anterior
            }

            // ME MUEVO O INSERTO EN LA CASILLA DESEADA
            if( mapa->getElemento(x,y+1)->getRepresentacionOriginal() == '*' ) //debo saber q tipo de casilla es donde voy a setear el ciervo para usar correctamente el insertar
            {
                reinterpret_cast< Mesetas * >( mapa->getElemento(x,y+1) )->insertar_poblacion_ciervos(this); //me muevo
            }else{
                reinterpret_cast< Pastizal * >( mapa->getElemento(x,y+1) )->insertar_poblacion_ciervos(this); //me muevo
            }

            return true;
        }
    }

    return false;
}

bool ciervo::intentarMoverseIzquierda(Mapa *mapa, int x, int y, int indice)
{

    if( y-1 >= 0 ) //si la izquierda existe
    {

        if(mapa->getElemento(x,y-1)->getRepresentacionOriginal() != '#') //si la derecha es una casilla valida
        {

            //ME BORRO DE LA POSICION ANTERIOR
            if( mapa->getElemento(x,y)->getRepresentacionOriginal() == '*' ) //debo saber q tipo de casilla era donde estaba antes el ciervo para usar correctamente el quitar ciervo
            {
                reinterpret_cast< Mesetas * >( mapa->getElemento(x,y) )->quitarCiervo(indice); //me borro de la posicion anterior
            }else{
                reinterpret_cast< Pastizal * >( mapa->getElemento(x,y) )->quitarCiervo(indice); //me borro de la posicion anterior
            }

            // ME MUEVO O INSERTO EN LA CASILLA DESEADA
            if( mapa->getElemento(x,y-1)->getRepresentacionOriginal() == '*' ) //debo saber q tipo de casilla es donde voy a setear el ciervo para usar correctamente el insertar
            {
                reinterpret_cast< Mesetas * >( mapa->getElemento(x,y-1) )->insertar_poblacion_ciervos(this); //me muevo
            }else{
                reinterpret_cast< Pastizal * >( mapa->getElemento(x,y-1) )->insertar_poblacion_ciervos(this); //me muevo
            }

            return true;
        }
    }

    return false;
}

bool ciervo::intentarMoverseArriba(Mapa *mapa, int x, int y, int indice)
{
    if( x-1 >= 0 ) //si la superior existe
    {
        if(mapa->getElemento(x-1,y)->getRepresentacionOriginal() != '#') //si la derecha es una casilla valida
        {

            //ME BORRO DE LA POSICION ANTERIOR
            if( mapa->getElemento(x,y)->getRepresentacionOriginal() == '*' ) //debo saber q tipo de casilla era donde estaba antes el ciervo para usar correctamente el quitar ciervo
            {
                reinterpret_cast< Mesetas * >( mapa->getElemento(x,y) )->quitarCiervo(indice); //me borro de la posicion anterior
            }else{
                reinterpret_cast< Pastizal * >( mapa->getElemento(x,y) )->quitarCiervo(indice); //me borro de la posicion anterior
            }

            // ME MUEVO O INSERTO EN LA CASILLA DESEADA
            if( mapa->getElemento(x-1,y)->getRepresentacionOriginal() == '*' ) //debo saber q tipo de casilla es donde voy a setear el ciervo para usar correctamente el insertar
            {
                reinterpret_cast< Mesetas * >( mapa->getElemento(x-1,y) )->insertar_poblacion_ciervos(this); //me muevo
            }else{
                reinterpret_cast< Pastizal * >( mapa->getElemento(x-1,y) )->insertar_poblacion_ciervos(this); //me muevo
            }

            return true;
        }

    }

    return false;
}

bool ciervo::intentarMoverseAbajo(Mapa *mapa, int x, int y, int indice)
{
    if( x+1 < mapa->getVertical() ) //si la de abajo existe
    {
        if(mapa->getElemento(x+1,y)->getRepresentacionOriginal() != '#') //si la derecha es una casilla valida
        {

            //ME BORRO DE LA POSICION ANTERIOR
            if( mapa->getElemento(x,y)->getRepresentacionOriginal() == '*' ) //debo saber q tipo de casilla era donde estaba antes el ciervo para usar correctamente el quitar ciervo
            {
                reinterpret_cast< Mesetas * >( mapa->getElemento(x,y) )->quitarCiervo(indice); //me borro de la posicion anterior
            }else{
                reinterpret_cast< Pastizal * >( mapa->getElemento(x,y) )->quitarCiervo(indice); //me borro de la posicion anterior
            }

            // ME MUEVO O INSERTO EN LA CASILLA DESEADA
            if( mapa->getElemento(x+1,y)->getRepresentacionOriginal() == '*' ) //debo saber q tipo de casilla es donde voy a setear el ciervo para usar correctamente el insertar
            {
                reinterpret_cast< Mesetas * >( mapa->getElemento(x+1,y) )->insertar_poblacion_ciervos(this); //me muevo
            }else{
                reinterpret_cast< Pastizal * >( mapa->getElemento(x+1,y) )->insertar_poblacion_ciervos(this); //me muevo
            }

            return true;
        }

    }

    return false;
}

bool ciervo::moverse(Mapa* mapa, int x, int y, int indice)
{
    int aleatorio;
    bool bandera = false;

    while(!bandera)
    {
        aleatorio = rand()%4;

        switch(aleatorio){

            case 0: bandera = intentarMoverseDerecha(mapa, x, y, indice);
                    break;
            case 1: bandera = intentarMoverseIzquierda(mapa, x, y, indice);
                    break;
            case 2: bandera = intentarMoverseAbajo(mapa, x, y, indice);
                    break;
            case 3: bandera = intentarMoverseArriba(mapa, x, y, indice);
                    break;
        }
    }

    return true;

    //deberia funcionar si el mapa esta bien generado
}

ciervo::ciervo(){}

ciervo::ciervo(int hambre, bool recienSeteado)
{
    this->hambre = hambre;
    this->recienSeteado = recienSeteado;
}
