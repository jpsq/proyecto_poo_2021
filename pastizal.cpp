#include "pastizal.h"
#include "elemento.h"
#include "QPixmap"
#include <iostream>
#include "ca.h"
#include "cb.h"

void Pastizal::pasar_dia()
{
    if(estaSeco)
    {
        regeneracion++;

        if(this->regeneracion == 5) //cumplio el plazo de crecimiendo
        {
            this->crecer();
        }

    }else{

        this->cantidad_de_dias++;

        if(cantidad_de_dias==10) // se seco
        {
            this->secar();
        }
    }
}

void Pastizal::interacciones()
{
    if(this->cantidadCiervos>1)
    {
        if(this->cantidadCiervos == 2)
        {
            ciervos[0]->interactua(ciervos[1], this);
        }
    }
}

eelemento Pastizal::getStruct()
{
    eelemento aux;
    aux.representacion = this->get_representacion();
    aux.representacionOriginal = this->getRepresentacionOriginal();
    aux.ocupado = this->ocupado;
    aux.cantidadCiervos = this->cantidadCiervos;
    aux.estaSeco = this->estaSeco;
    aux.regeneracion = this->regeneracion;
    aux.cantDias = this->cantidad_de_dias;

    for(int i=0;i<this->cantidadCiervos;i++){

        aux.ciervitos[i] = this->ciervos[i]->getStruct();
    }

    //PARA REPRESENTACION GRAFICA:

    if(this->getRepresentacionGrafica() == this->pix){

        aux.representacionGrafica = 0;

    }else if(this->getRepresentacionGrafica() == this->pix_ca){

        aux.representacionGrafica = 1;

    }else if(this->getRepresentacionGrafica() == this->pix_cb){

        aux.representacionGrafica = 2;

    }else if(this->getRepresentacionGrafica() == this->pix_seco_multiples){

        aux.representacionGrafica = 3;

    }else if(this->getRepresentacionGrafica() == this->pix_seco){

        aux.representacionGrafica = 4;

    }else if(this->getRepresentacionGrafica() == this->pix_seco_ca){

        aux.representacionGrafica = 5;

    }else if(this->getRepresentacionGrafica() == this->pix_seco_cb){

        aux.representacionGrafica = 6;

    }else if(this->getRepresentacionGrafica() == this->pix_seco_multiples){

        aux.representacionGrafica = 7;
    }

    return aux;
}

void Pastizal::crecer(){

    this->regeneracion=0;
    this->estaSeco=false;
    this->cantidad_de_dias=0;

    if(!this->ocupado) //si esta vacio
    {
        this->setRepresentacion(vivo);
        this->setRepresentacionGrafica(pix);

    }else{ //esta ocupado

        //PARA REPRESENTACION GRAFICA:
        if(cantidadCiervos==1) //solo hay 1 ciervo
        {
            if(this->get_representacion() == 'A')
            {
                this->setRepresentacionGrafica(pix_ca);
            }else{
                this->setRepresentacionGrafica(pix_cb);
            }
        }else{ // hay mas de 1 ciervo

            this->setRepresentacionGrafica(pix_multiples);
        }
    }

}

void Pastizal::secar(){

    this->regeneracion=0;
    this->estaSeco=true;
    this->cantidad_de_dias=0;

    if(!this->ocupado)
    {
        this->setRepresentacion(seco);
        this->setRepresentacionGrafica(pix_seco);
    }else{

        //PARA REPRESENTACION GRAFICA:
        if(cantidadCiervos==1) //solo hay 1 ciervo
        {
            if(this->get_representacion() == 'A')
            {
                this->setRepresentacionGrafica(pix_seco_ca);
            }else{
                this->setRepresentacionGrafica(pix_seco_cb);
            }
        }else{ // hay mas de 1 ciervo

            this->setRepresentacionGrafica(pix_seco_multiples);
        }
    }
}

ciervo* Pastizal::getPrimerCiervo()
{
    if(this->ocupado)
    {
        return this->ciervos[0];
    }
}

bool Pastizal::getOcupado() const
{
    return this->ocupado;
}

void Pastizal::setOcupado(bool newOcupado)
{
    ocupado = newOcupado;
}

char Pastizal::getSeco() const
{
    return seco;
}

bool Pastizal::estaSecoEstePastizal(){

    return this->estaSeco;
}

int Pastizal::getCantidadCiervos() const
{
    return cantidadCiervos;
}

Pastizal::Pastizal():Elemento(){

    //INICIALIZO LOS ICONOS:
    this->pix = new QPixmap(":/iconostp3/iconostp3/pastizal.png");
    this->pix_ca = new QPixmap(":/iconostp3/iconostp3/pastizal_ca.png");
    this->pix_cb = new QPixmap(":/iconostp3/iconostp3/pastizal_cb.png");
    this->pix_multiples = new QPixmap(":/iconostp3/iconostp3/pastizal_m.png");
    this->pix_seco_ca = new QPixmap(":/iconostp3/iconostp3/pastizal_seco_ca.png");
    this->pix_seco_cb = new QPixmap(":/iconostp3/iconostp3/pastizal_seco_cb.png");
    this->pix_seco = new QPixmap(":/iconostp3/iconostp3/pastizal_seco.png");
    this->pix_seco_multiples = new QPixmap(":/iconostp3/iconostp3/pastizal_seco_m.png");

    this->setRepresentacion(vivo);
    this->setRepresentacionOriginal('P');
    this->setRepresentacionGrafica(pix);
}

Pastizal::Pastizal(char representacion1, int representacionGrafica1, bool ocupado1, int cantCiervos1, int cantDias1, bool estaSeco1, int regeneracion1, eciervo ciervitos[]):Elemento()
{
    //INICIALIZO LOS ICONOS:
    this->pix = new QPixmap(":/iconostp3/iconostp3/pastizal.png");
    this->pix_ca = new QPixmap(":/iconostp3/iconostp3/pastizal_ca.png");
    this->pix_cb = new QPixmap(":/iconostp3/iconostp3/pastizal_cb.png");
    this->pix_multiples = new QPixmap(":/iconostp3/iconostp3/pastizal_m.png");
    this->pix_seco_ca = new QPixmap(":/iconostp3/iconostp3/pastizal_seco_ca.png");
    this->pix_seco_cb = new QPixmap(":/iconostp3/iconostp3/pastizal_seco_cb.png");
    this->pix_seco = new QPixmap(":/iconostp3/iconostp3/pastizal_seco.png");
    this->pix_seco_multiples = new QPixmap(":/iconostp3/iconostp3/pastizal_seco_m.png");

    this->setRepresentacion(representacion1);
    this->setRepresentacionOriginal('P');

    //PARA REPRESENTACION GRAFICA

    switch (representacionGrafica1) {

        case 0: this->setRepresentacionGrafica(pix);
                break;
        case 1: this->setRepresentacionGrafica(pix_ca);
                break;
        case 2: this->setRepresentacionGrafica(pix_cb);
               break;
        case 3: this->setRepresentacionGrafica(pix_multiples);
                break;
        case 4: this->setRepresentacionGrafica(pix_seco);
                break;
        case 5: this->setRepresentacionGrafica(pix_seco_ca);
                break;
        case 6: this->setRepresentacionGrafica(pix_seco_cb);
                break;
        case 7: this->setRepresentacionGrafica(pix_seco_multiples);
                break;
    }

    this->cantidadCiervos = cantCiervos1;
    this->cantidad_de_dias = cantDias1;
    this->estaSeco = estaSeco1;
    this->regeneracion = regeneracion1;
    this->ocupado = ocupado1;

    for(int i=0;i<this->cantidadCiervos;i++){

        switch (ciervitos[i].representacion) {

            case 'A': ciervos[i] = new CA(ciervitos[i].hambre, ciervitos[i].recienSeteado);
                      break;
            case 'B': ciervos[i] = new CB(ciervitos[i].hambre, ciervitos[i].recienSeteado);
                      break;
        }
    }
}

ciervo* Pastizal::getCiervo(int indice){

    if(indice < cantidadCiervos)
    {
        return this->ciervos[indice];
    }else{
        return nullptr;
    }
}

void Pastizal::quitarCiervo(int indice)
{
    if(this->cantidadCiervos==1)
    {
        this->setOcupado(false);
        this->ciervos[0] = nullptr;
        this->cantidadCiervos=0;

        if(estaSeco)
        {
            this->setRepresentacion(seco);
            this->setRepresentacionGrafica(pix_seco); //inserto imagen de pastizal seco sin ciervos
        }else{
            this->setRepresentacion(vivo);
            this->setRepresentacionGrafica(pix); //inserto imagen de pastizal sin ciervos
        }

    }else{ //mas de 1 ciervo, se quiere borrar el ciervo 0, y acomodar el array

        if(indice == cantidadCiervos-1) //es el ultimo de la lista
        {
            ciervos[indice] = nullptr;
            this->setRepresentacion(this->ciervos[0]->getRepresentacion()); //seteo el icono del ciervo
            this->cantidadCiervos--;
        }else
        {

            for(int i=indice;i<cantidadCiervos-1;i++)
            {
                ciervos[i] = ciervos[i+1];
            }

            this->setRepresentacion(this->ciervos[0]->getRepresentacion()); //seteo el icono del ciervo q estaba dsp del q borre
            this->ciervos[cantidadCiervos-1] = nullptr;                      //esto no es necesario pero bueno lo hago por las dudas
            this->cantidadCiervos--;

            //PARA LA REPRESENTACION GRAFICA:

            if(estaSeco)
            {
                if(cantidadCiervos == 1){//si solo quedaba este ciervo

                    if(this->get_representacion() == 'A')
                    {
                        this->setRepresentacionGrafica(pix_ca);
                    }else{

                        this->setRepresentacionGrafica(pix_cb);
                    }
                }else{
                    this->setRepresentacionGrafica(pix_multiples);
                }

            }else{

                if(cantidadCiervos == 1){//si solo quedaba este ciervo

                    if(this->get_representacion() == 'A')
                    {
                        this->setRepresentacionGrafica(pix_ca);
                    }else{

                        this->setRepresentacionGrafica(pix_cb);
                    }
                }else{
                    this->setRepresentacionGrafica(pix_multiples);
                }

            } //fin de las comprobaciones para la repr. grafica
        }
    }
}

void Pastizal::insertar_poblacion_ciervos(ciervo* poblacion1){

    if(this->ocupado)
    {
        this->ciervos[cantidadCiervos] = poblacion1; //ingreso la poblacion donde correspondas
        this->cantidadCiervos++;                    //aumento el indice
        this->setRepresentacion( poblacion1->getRepresentacion() );
        poblacion1->setRecienSeteado(true);         //para que el pasar de dias de ciervos funcione bien

        if(estaSeco)
        {
            this->setRepresentacionGrafica(pix_seco_multiples);
        }else{
            this->setRepresentacionGrafica(pix_multiples);
        }

    }else //no hay en ningun lado
    {
        this->ocupado = true;
        this->ciervos[0] = poblacion1;              //ingreso la poblacion en el primer espacio
        this->cantidadCiervos++;                    //aumento el indice
        this->setRepresentacion( poblacion1->getRepresentacion() );
        poblacion1->setRecienSeteado(true);         //para que el pasar de dias de ciervos funcione bien

        //PARA REPRESENTACION GRAFICA:

        if(estaSeco)
        {
            if(this->get_representacion() == 'A')
            {
                this->setRepresentacionGrafica(pix_seco_ca);
            }else{
                this->setRepresentacionGrafica(pix_seco_cb);
            }
        }else{

            if(this->get_representacion() == 'A'){

                this->setRepresentacionGrafica(pix_ca);
            }else{
                this->setRepresentacionGrafica(pix_cb);
            }
        }


    }
    poblacion1->alimentarse(this, cantidadCiervos-1);                  //el ciervo intenta alimentarse
}

