#include "montania.h"
#include "QPixmap"

Montania::Montania():Elemento()
{
    this->pix = new QPixmap(":/iconostp3/iconostp3/montanias.png");

    this->setRepresentacion('#');
    this->setRepresentacionOriginal('#');
    this->setRepresentacionGrafica(pix);
}

eelemento Montania::getStruct()
{
    eelemento aux;
    aux.representacion = this->get_representacion();
    aux.representacionOriginal = this->getRepresentacionOriginal();
    aux.representacionGrafica = 0;

    return aux;
}
