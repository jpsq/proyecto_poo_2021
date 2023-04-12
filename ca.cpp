#include "ca.h"
#include "mesetas.h"
#include "pastizal.h"
#include <iostream>

CA::CA():ciervo() //llama a constructor de padre y asigna el caracter a para esta clase
{
    this->setRepresentacion('A');
}

CA::CA(int hambre, bool recienSeteado):ciervo(hambre, recienSeteado)
{
    this->representacion = 'A';
}

void CA::interactua(ciervo* ciervo, Elemento* casilla)
{

    if(ciervo->getRepresentacion() == 'A') //si es de tipo a se cruzan y generan una nueva poblacion
    {

        CA* poblacionCria = new CA();

        if(casilla->getRepresentacionOriginal() == '*')
        {
            reinterpret_cast< Mesetas * >( casilla )->insertar_poblacion_ciervos(poblacionCria);
            poblacionCria->setRecienSeteado(false); //para q pueda moverse dsp

        }else if(casilla->getRepresentacionOriginal() == 'P')
        {
            reinterpret_cast< Pastizal * >( casilla )->insertar_poblacion_ciervos(poblacionCria);
            poblacionCria->setRecienSeteado(false); //para q pueda moverse dsp
        }
    }
}

