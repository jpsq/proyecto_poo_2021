#include "elemento.h"
#include "montania.h"

char Elemento::getRepresentacionOriginal() const
{
    return representacionOriginal;
}

void Elemento::setRepresentacionOriginal(char newRepresentacionOriginal)
{
    representacionOriginal = newRepresentacionOriginal;
}

QPixmap* Elemento::getRepresentacionGrafica()
{
    return representacionGrafica;
}

void Elemento::setRepresentacionGrafica(QPixmap *newRepresentacionGrafica)
{
    representacionGrafica = newRepresentacionGrafica;
}

Elemento::Elemento(){}

void Elemento::setRepresentacion(char newRepresentacion)
{
    representacion = newRepresentacion;
}

char Elemento::get_representacion()
{
    return this->representacion;
}

Elemento::~Elemento(){

    delete this;
}
