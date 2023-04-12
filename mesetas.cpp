#include "mesetas.h"
#include "QPixmap"
#include <iostream>
#include "ca.h"
#include "cb.h"

int Mesetas::getCantidadCiervos() const
{
    return cantidadCiervos;
}

void Mesetas::setCantidadCiervos(int newCantidadCiervos)
{
    cantidadCiervos = newCantidadCiervos;
}

Mesetas::Mesetas():Elemento(){

    //INICIALIZO LOS ICONOS:
    this->pix = new QPixmap(":/iconostp3/iconostp3/mesetas.png");
    this->pix_ca = new QPixmap(":/iconostp3/iconostp3/mesetas_ca.png");
    this->pix_cb = new QPixmap(":/iconostp3/iconostp3/mesetas_cb.png");
    this->pix_multiples = new QPixmap(":/iconostp3/iconostp3/mesetas_m.png");

    this->setRepresentacionOriginal('*');
    this->setRepresentacion('*');
    this->setRepresentacionGrafica(pix);
}

Mesetas::Mesetas(char representacion1, int representacionGrafica1, bool ocupado1, int cantCiervos1, eciervo ciervitos[]):Elemento()
{
    //INICIALIZO LOS ICONOS:
    this->pix = new QPixmap(":/iconostp3/iconostp3/mesetas.png");
    this->pix_ca = new QPixmap(":/iconostp3/iconostp3/mesetas_ca.png");
    this->pix_cb = new QPixmap(":/iconostp3/iconostp3/mesetas_cb.png");
    this->pix_multiples = new QPixmap(":/iconostp3/iconostp3/mesetas_m.png");

    this->setRepresentacionOriginal('*');
    this->setRepresentacion(representacion1);

    //PARA REPRESENTACION GRAFICA
    switch(representacionGrafica1){

        case 0: this->setRepresentacionGrafica(pix);
                break;
        case 1: this->setRepresentacionGrafica(pix_ca);
                break;
        case 2: this->setRepresentacionGrafica(pix_cb);
                break;
        case 3: this->setRepresentacionGrafica(pix_multiples);
    }

    this->ocupado = ocupado1;
    this->cantidadCiervos = cantCiervos1;

    for(int i=0;i<cantidadCiervos;i++){

        switch (ciervitos[i].representacion) {

            case 'A': ciervos[i] = new CA(ciervitos[i].hambre, ciervitos[i].recienSeteado);
                      break;
            case 'B': ciervos[i] = new CB(ciervitos[i].hambre, ciervitos[i].recienSeteado);
                      break;
        }
    }
}

void Mesetas::interacciones()
{
    if(this->cantidadCiervos>1)
    {

        ciervos[0]->interactua(ciervos[1], this);
        /* Hicimos q solo interactuen las 2 primeras poblaciones de ciervos, si hay mas de 2 las otras no generaran un evento.
          Esto debido a que para que las demas tuvieran efecto se deberia controlar paridad de cantidad de ciervos por casilla,
          decidir que que poblacion interactua con que otra, que hacer con la poblacion impar si se da el caso, pero principalmente
          debido a que la lista de ciervos se acomoda automaticamente al al quitar o agregar ciervos, seria compliado gestionar el indice
          correcto para utilizar los demas interacciones de la lista. Ya que este caso seria muy raro en probabilidad, dejamos solo un evento con los primero 2 de la lista y ya.
        */
    }
}

eelemento Mesetas::getStruct()
{
    eelemento aux;
    aux.representacion = this->get_representacion();
    aux.representacionOriginal = this->getRepresentacionOriginal();
    aux.ocupado = this->ocupado;
    aux.cantidadCiervos = this->cantidadCiervos;

    for(int i=0;i<this->cantidadCiervos;i++){

        aux.ciervitos[i] = this->ciervos[i]->getStruct();
    }

    //PARA REPRESENTACION GRAFICA:
    if(!this->ocupado){ //si no esta ocupado

        aux.representacionGrafica = 0;

    }else if(this->cantidadCiervos > 1){ //tienen varios ciervos

        aux.representacionGrafica = 3;

    }else if(this->get_representacion() == 'A'){ //tiene un ciervo a

        aux.representacionGrafica = 1;

    }else{ //tiene un ciervo b

        aux.representacionGrafica = 2;
    }

    return aux;
}

ciervo* Mesetas::getPrimerCiervo()
{
    if(this->ocupado)
    {
        return this->ciervos[0];
    }
}

void Mesetas::quitarCiervo(int indice)
{

    if(this->cantidadCiervos==1) //queda vacio
    {
        this->setOcupado(false);
        this->ciervos[0] = nullptr;
        this->cantidadCiervos=0;

        this->setRepresentacion('*');
        this->setRepresentacionGrafica(pix);

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


        }
    }
}

void Mesetas::setOcupado(bool x)
{
    this->ocupado=x;
}

ciervo* Mesetas::getCiervo(int indice){

    return this->ciervos[indice];
}

void Mesetas::insertar_poblacion_ciervos(ciervo* poblacion1){

    if(this->ocupado)
    {
        this->ciervos[cantidadCiervos] = poblacion1; //ingreso la poblacion donde correspondas
        this->cantidadCiervos++;                    //aumento el indice
        this->setRepresentacion( poblacion1->getRepresentacion() );
        poblacion1->setRecienSeteado(true);         //para que el pasar de dias de ciervos funcione bien
        this->setRepresentacionGrafica(pix_multiples);

    }else //no hay en ningun lado
    {

        this->ocupado = true;
        this->ciervos[0] = poblacion1;              //ingreso la poblacion en el primer espacio
        this->cantidadCiervos++;                    //aumento el indice
        this->setRepresentacion( poblacion1->getRepresentacion() );
        poblacion1->setRecienSeteado(true);         //para que el pasar de dias de ciervos funcione bien

        if(this->get_representacion() == 'A')
        {
            this->setRepresentacionGrafica(pix_ca);
        }else{

            this->setRepresentacionGrafica(pix_cb);
        }
    }

    poblacion1->alimentarse(this, cantidadCiervos-1);                  //el ciervo intenta alimentarse
}

bool Mesetas::getOcupado() const
{
    return this->ocupado;
}
