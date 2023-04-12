#include "cb.h"
#include "mesetas.h"
#include "pastizal.h"

CB::CB():ciervo() //llama a constructor de padre y asigna el caracter a para esta clase
{
    this->setRepresentacion('B');
}

CB::CB(int hambre, bool recienSeteado):ciervo(hambre, recienSeteado)
{
    this->representacion = 'B';
}

void CB::interactua(ciervo* ciervo, Elemento* casilla)
{

    if(ciervo->getRepresentacion() == 'B') //si es de tipo b se unen las poblaciones
    {

        if(casilla->getRepresentacionOriginal() == '*')
        {
            reinterpret_cast< Mesetas * >( casilla )->quitarCiervo(1); //lo borro y dejo el de indice 0, asumiendo q se unen digamos

        }else if(casilla->getRepresentacionOriginal() == 'P')
        {
            reinterpret_cast< Pastizal * >( casilla )->quitarCiervo(1);
        }
    }
}
