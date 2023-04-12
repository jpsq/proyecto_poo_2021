#include "mapa.h"
#include "ca.h"
#include "cb.h"
#include "mesetas.h"
#include "montania.h"
#include "pastizal.h"
#include "windows.h"
#include "stdlib.h"
#include "iostream"
#include "elemento.h"
#include "ciervo.h"

int Mapa::getDiasSimulacion() const
{
    return diasSimulacion;
}

Mapa::Mapa(){}

int Mapa::getCantidadCaminosValidos() const
{
    return cantidadCaminosValidos;
}

void Mapa::setCantidadCaminosValidos(int newCantidadCaminosValidos)
{
    cantidadCaminosValidos = newCantidadCaminosValidos;
}

int Mapa::getCantidadCaminosInvalidos() const
{
    return cantidadCaminosInvalidos;
}

Elemento* Mapa::getElemento(int x, int y) //devuelve una casilla a partir de sus indices
{
    return this->elementos[x][y];
}

void Mapa::setCantidadCaminosInvalidos(int newCantidadCaminosInvalidos)
{
    cantidadCaminosInvalidos = newCantidadCaminosInvalidos;
}

void Mapa::pasar_dia(){ //esto ejecuta el cambio de dia para las casillas q posean una funcion en tal, ademas activa el pasar dia de los ciervos con sus respectivos controles

    for(int x=0; x<this->vertical;x++) //los pastizales se actualizan
    {
        for(int y=0;y<this->horizontal;y++)
        {

            if(this->elementos[x][y]->getRepresentacionOriginal() == 'P')
            {
                reinterpret_cast< Pastizal * >( this->elementos[x][y] )->pasar_dia(); //los pastizales cambian de dia, se seca, crecen segun corresponda
            }
        }
    }

    for(int x=0; x<this->vertical;x++) //los pastizales se actualizan
    {
        for(int y=0;y<this->horizontal;y++)
        {

            if(this->elementos[x][y]->getRepresentacionOriginal() == 'P') //si es pastizal
            {

                if( reinterpret_cast< Pastizal * >( this->elementos[x][y] )->getCantidadCiervos() > 1 ) //si tiene mas de 1 ciervo
                {
                    reinterpret_cast< Pastizal * >( this->elementos[x][y] )->interacciones(); //los ciervos interactuan
                }
            }else if( this->elementos[x][y]->getRepresentacionOriginal() == '*' ) //es meseta
            {
                if( reinterpret_cast< Mesetas * >( this->elementos[x][y] )->getCantidadCiervos() > 1 ) //si tiene mas de 1 ciervo
                {
                    reinterpret_cast< Mesetas * >( this->elementos[x][y] )->interacciones(); //los ciervos interactuan
                }
            }
        }
    }

    this->pasar_dia_para_ciervos(); //los ciervos se mueven a otras casillas de forma aleatoria
}

int Mapa::getHorizontal() const
{
    return horizontal;
}

int Mapa::getVertical() const
{
    return vertical;
}
Mapa::Mapa(int v,int h)
{
    this->vertical=v;
    this->horizontal=h;
}

Mapa::Mapa(int v,int h,int t)
{
    this->vertical=v;
    this->horizontal=h;
    this->tiempo_de_retardo=t;
}

bool Mapa::esMeseta(int x, int y)
{
    return this->elementos[x][y]->getRepresentacionOriginal() == '*';
}
bool Mapa::esPastizal(int x, int y)
{
    return this->elementos[x][y]->getRepresentacionOriginal() == 'P';
}
bool Mapa::esMontania(int x, int y)
{
    return this->elementos[x][y]->getRepresentacionOriginal() == '#';
}

bool Mapa::casillaFormaraCaminoValido(int x, int y)//checkea si la casilla tiene en alguno de sus 4 extremos un pastizal
{

    if(x-1 >= 0)// existe una casilla arriba
    {
        if( this->getElemento(x-1,y)->getRepresentacionOriginal()=='P' )//si es un pastizal
        {
            return true;
        }
    }

    if(x+1 < vertical)// existe una casilla abajo
    {
        if( this->getElemento(x+1,y)->getRepresentacionOriginal()=='P' )//si es un pastizal
        {
            return true;
        }
    }

    if(y-1 >= 0)// existe una casilla izquierda
    {
        if( this->getElemento(x,y-1)->getRepresentacionOriginal()=='P' )//si es un pastizal
        {
            return true;
        }
    }

    if(y+1 < horizontal)// existe una casilla derecha
    {
        if( this->getElemento(x,y+1)->getRepresentacionOriginal()=='P' )//si es un pastizal
        {
            return true;
        }
    }

    return false;
}

void Mapa::cargarMapaDesdeArchivo()
{
    std::ifstream archivo("mapa.dat", std::ios::binary);
    emapa x;
    archivo.read( (char*) &x, sizeof(emapa));
    archivo.close();

    this->vertical = x.vertical;
    this->horizontal = x.horizontal;
    this->tiempo_de_retardo = x.tiempo; // hasta aca anda
    this->diasSimulacion = x.cantDiasSimulacion;

    //CREO LOS PUNTEROS
    this->elementos = new Elemento** [this->vertical];
    for(int x=0;x<this->vertical;x++)
    {
        this->elementos[x]=new Elemento*[this->horizontal];
    }

    for(int i=0;i<vertical;i++){

        for(int j=0;j<horizontal;j++){

            switch(x.casillas[i][j].representacionOriginal){

                case '#': this->setElementInicial(i,j, new Montania() );
                          break;

                case '*': this->setElementInicial(i,j, new Mesetas(x.casillas[i][j].representacion,
                                                                   x.casillas[i][j].representacionGrafica,
                                                                   x.casillas[i][j].ocupado,
                                                                   x.casillas[i][j].cantidadCiervos,
                                                                   x.casillas[i][j].ciervitos)
                                                  );
                          break;

                case 'P': this->setElementInicial(i,j, new Pastizal(x.casillas[i][j].representacion,
                                                                    x.casillas[i][j].representacionGrafica,
                                                                    x.casillas[i][j].ocupado,
                                                                    x.casillas[i][j].cantidadCiervos,
                                                                    x.casillas[i][j].cantDias,
                                                                    x.casillas[i][j].estaSeco,
                                                                    x.casillas[i][j].regeneracion,
                                                                    x.casillas[i][j].ciervitos)
                                                    );
                          break;
            }

        }
    }

}

void Mapa::guardarMapaEnArchivo(int diasPasadosSimulacion)
{
    emapa aux; //no puede crear eelemtto si estos tiene vectores de ciervos de mas de 14
    aux.vertical = this->vertical;
    aux.horizontal = this->horizontal;
    aux.tiempo = this->tiempo_de_retardo;
    aux.cantDiasSimulacion = diasPasadosSimulacion;

    for(int i=0;i<vertical;i++){

        for(int j=0;j<horizontal;j++){

            aux.casillas[i][j] = this->elementos[i][j]->getStruct();
        }
    }

    std::ofstream archivo("mapa.dat", std::ios::binary);
    archivo.write( (char*) &aux, sizeof(emapa) );
    archivo.close();
}

void Mapa::pasar_dia_para_ciervos() //recorre la matriz, ejecuta mover para cada ciervo y se asegura q ningun ciervo se mueva 2 veces en el mismo dia por error
{                                   //FUNCIONA, pero los ciervos conviertes casillas en otro tipo

    int cantCiervos;
    int indiceCiervos=0;

    for(int x=0;x<this->vertical;x++)
    {
        for(int y=0;y<this->horizontal;y++)
        {
            //IDENTIFICAMOS LA CASILLA:

            if(this->elementos[x][y]->getRepresentacionOriginal() == '*') //si es meseta
            {
                if( reinterpret_cast< Mesetas * >( this->elementos[x][y] )->getOcupado() ) //si la casilla tiene ciervos
                {

                    cantCiervos = reinterpret_cast< Mesetas * >( this->elementos[x][y] )->getCantidadCiervos(); //me guardo en una variable cuantos tiene
                    indiceCiervos=0;

                    for(int i=0;i<cantCiervos;i++)      //bucle de la lista de ciervos de esta casilla
                    {

                        if( !reinterpret_cast< Mesetas * >( this->elementos[x][y] )->getCiervo(indiceCiervos)->getRecienSeteado() ) //si el ciervo fue recien seteado en esta casilla no debe volver a ejecutarse su movimiento
                        {
                            reinterpret_cast< Mesetas * >( this->elementos[x][y] )->getCiervo(indiceCiervos)->moverse(this,x,y,i); //el ciervo se mueve

                        }else{ //estaba recien seteado por ende no se movio

                            indiceCiervos++; //si ciervo actual no se mueve, paso al siguiente puntero, si el ciervo actual se movio, el indice no deberia aumentar porque la lista re recoloca
                        }
                    }
                }

            }else if(this->elementos[x][y]->getRepresentacionOriginal() == 'P') //es pastizal
            {

                if( reinterpret_cast< Pastizal * >( this->elementos[x][y] )->getOcupado() ) //si tiene ciervos
                {
                    cantCiervos = reinterpret_cast< Pastizal * >( this->elementos[x][y] )->getCantidadCiervos(); //me guardo en una variable cuantos tiene
                    indiceCiervos=0;
                    for(int i=0;i<cantCiervos;i++)
                    {

                        if( !reinterpret_cast< Pastizal * >( this->elementos[x][y] )->getCiervo(indiceCiervos)->getRecienSeteado() ) //si el ciervo NO fue recien seteado
                        {
                            reinterpret_cast< Pastizal * >( this->elementos[x][y] )->getCiervo(indiceCiervos)->moverse(this,x,y,i);

                        }else{

                            indiceCiervos++; //si ciervo actual no se mueve, paso al siguiente puntero, si el ciervo actual se movio, el indice no deberia aumentar porque la lista re recoloca
                        }
                    }
                }
            }
        }
    }

    //estos ciclos deben poner a todos los ciervos an no seteados para el proximo dia:
    for(int x=0;x<this->vertical;x++)
    {
        for(int y=0;y<this->horizontal;y++)
        {

            if(this->elementos[x][y]->getRepresentacionOriginal() == '*') //si es meseta
            {
                if( reinterpret_cast< Mesetas * >( this->elementos[x][y] )->getOcupado() )
                {

                    cantCiervos = reinterpret_cast< Mesetas * >( this->elementos[x][y] )->getCantidadCiervos(); //me guardo en una variable cuantos tiene
                    for(int i=0;i<cantCiervos;i++)      //bucle de la lista de ciervos de esta casilla
                    {
                        reinterpret_cast< Mesetas * >( this->elementos[x][y] )->getCiervo(i)->setRecienSeteado(false); //le pongo false a este atributo del ciervo para el proximo dia
                    }

                }



            }else if(this->elementos[x][y]->getRepresentacionOriginal() == 'P')
            {
                if( reinterpret_cast< Pastizal * >( this->elementos[x][y] )->getOcupado() )
                {

                    cantCiervos = reinterpret_cast< Pastizal * >( this->elementos[x][y] )->getCantidadCiervos(); //me guardo en una variable cuantos tiene
                    for(int i=0;i<cantCiervos;i++)      //bucle de la lista de ciervos de esta casilla
                    {
                        reinterpret_cast< Pastizal * >( this->elementos[x][y] )->getCiervo(i)->setRecienSeteado(false); //le pongo false a este atributo del ciervo para el proximo dia
                    }
                }
            }
        }
    }

}

bool Mapa::generar_ciervos(int cantidadCiervosA, int cantidadCiervosB) //version original q funciona
{

    int cant_ca_colocados=0, cant_cb_colocados=0, z;
    bool esPastizal;

    //si se quiere ingresar mas o igual cantidad de ciervos que caminos validos para ellos, simplemento coloco en todos los caminos validos ciervos,
   if(cantidadCiervosA+cantidadCiervosB >= this->cantidadCaminosValidos)
   {
       //BUCLES QUE RECORREN EL MAPA:
        for(int x=0;x<this->vertical;x++)
        {
            for(int y=0;y<this->horizontal;y++)
            {

                if(this->elementos[x][y]->getRepresentacionOriginal() == 'P' || this->elementos[x][y]->getRepresentacionOriginal() == '*') //si la casilla es un camino valido
                {

                    if(this->elementos[x][y]->getRepresentacionOriginal() == 'P'){ //si es pastizal, esto lo uso para definir la bandera y dsp saber si es la casilla es pastizal o es meseta para hacer correctamente el reinterpreter cas

                        esPastizal = true;
                    }else{
                        esPastizal = false;
                    }

                    if( cant_ca_colocados < cantidadCiervosA && cant_cb_colocados < cantidadCiervosB ) //quedan colocar ciervos a y b
                    {

                        z=rand()%2; //asigno un random para saber cual tipo de ciervo setear

                        if(esPastizal){ //pregunto para saber que casteo usar

                            switch(z)
                            {
                                case 0: reinterpret_cast< Pastizal * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                                        cant_ca_colocados++;
                                        break;
                                case 1: reinterpret_cast< Pastizal * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                                        cant_cb_colocados++;
                                        break;
                            }

                        }else{

                            switch(z)
                            {
                                case 0: reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                                        cant_ca_colocados++;
                                        break;
                                case 1: reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                                        cant_cb_colocados++;
                                        break;
                            }
                        }


                    }else if( cant_ca_colocados < cantidadCiervosA && cant_cb_colocados >= cantidadCiervosB ) //solo quedan colocar ciervos a
                    {

                        if(esPastizal)
                        {
                            reinterpret_cast< Pastizal * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                            cant_ca_colocados++;

                        }else
                        {
                            reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                            cant_ca_colocados++;
                        }


                    }else if( cant_ca_colocados >= cantidadCiervosA && cant_cb_colocados < cantidadCiervosB ) //solo quedan colocar ciervos b
                    {
                        if(esPastizal)
                        {
                            reinterpret_cast< Pastizal * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                            cant_cb_colocados++;
                        }else
                        {
                            reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                            cant_cb_colocados++;
                        }

                    }else if(cant_ca_colocados+cant_cb_colocados == cantidadCiervosA+cantidadCiervosB) //no quedan colocar ciervos, solo entra si la cantidad de ciervos
                    {                                                                                  // era igual a la cantidad de camnos validos, porque lo que los bucles alcanzan justo
                        return true;
                    }
                }
            }
        }
        //Luego de estos bucles, todos los caminos validos tiene ciervos

        if(cantidadCiervosA+cantidadCiervosB >= vertical*horizontal) //si la cantidad de ciervos es mayor o igual a la cantidad de casillas, seteo ciervos en todo el mapa restante, sacrificando montanias
        {

            std::cout << "ADVERTENCIA: LA CANTIDAD DE CIERVOS ES MAYOR (O IGUAL) A LAS CASILLAS DEL MAPA, LOS CIERVOS SOBRANTES NO PODRAN GENERARSE:" << std::endl;
            //BUCLES QUE RECORREN EL MAPA:
             for(int x=0;x<this->vertical;x++)
             {
                 for(int y=0;y<this->horizontal;y++)
                 {

                     if(this->elementos[x][y]->getRepresentacionOriginal() == '#') //si la casilla es una montania
                     {

                         if( cant_ca_colocados < cantidadCiervosA && cant_cb_colocados < cantidadCiervosB ) //quedan colocar ciervos a y b
                         {

                             z=rand()%2; //asigno un random para saber cual tipo de ciervo setear

                             switch(z)
                             {
                                case 0: this->setElementSustituto(x,y, new Mesetas); //transformo la casilla
                                        reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() ); //seteo ciervo
                                        cant_ca_colocados++;
                                        break;
                                case 1: this->setElementSustituto(x,y, new Mesetas);
                                        reinterpret_cast< Pastizal * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                                        cant_cb_colocados++;
                                        break;
                             }


                         }else if( cant_ca_colocados < cantidadCiervosA && cant_cb_colocados >= cantidadCiervosB ) //solo quedan colocar ciervos a
                         {

                            this->setElementSustituto(x,y, new Mesetas);
                            reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                            cant_ca_colocados++;

                         }else if( cant_ca_colocados >= cantidadCiervosA && cant_cb_colocados < cantidadCiervosB ) //solo quedan colocar ciervos b
                         {
                             this->setElementSustituto(x,y, new Mesetas);
                             reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                             cant_cb_colocados++;

                         }else if(cant_ca_colocados+cant_cb_colocados == vertical*horizontal) //siempre deberia tocar aqui al final de los bucles,el mapa se lleno de ciervos, los ciervos q no se quedan no se colocaran
                         {
                             return true;
                         }
                     }
                 }
             }

        }else{ //hay mas casillas que ciervos pero quedan colocar ya que hay mas ciervos que caminos validos, osea quedan colocar ciervos sacrificando algunas montanias


            while( (cant_ca_colocados<cantidadCiervosA) || (cant_cb_colocados<cantidadCiervosB) )
            {
                //tengo las coordenadas aleatorias
                int x = rand()%this->vertical;
                int y = rand()%this->horizontal;

                if(this->elementos[x][y]->getRepresentacionOriginal() == '#') //si la casilla es una montania
                {
                    if( (cant_ca_colocados<cantidadCiervosA) && (cant_cb_colocados<cantidadCiervosB) ) //si quedan colocar ciervos a y b
                    {
                        z=rand()%2;

                        switch(z)
                        {
                            case 0: this->setElementSustituto(x,y, new Mesetas() );
                                    reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                                    cant_ca_colocados++;
                                    break;
                            case 1: this->setElementSustituto(x,y, new Mesetas() );
                                    reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                                    cant_cb_colocados++;
                                    break;
                         }


                     }else if( (cant_ca_colocados<cantidadCiervosA) && (cant_cb_colocados>=cantidadCiervosB) ) //solo quedan colocar ciervos a por coloar
                     {
                         this->setElementSustituto(x,y, new Mesetas() );
                         reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                         cant_ca_colocados++;

                     }else if( (cant_ca_colocados>=cantidadCiervosA) && (cant_cb_colocados<cantidadCiervosB) ) //solo quedan colocar ciervos b
                     {
                        this->setElementSustituto(x,y, new Mesetas() );
                        reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                        cant_cb_colocados++;

                     }else{ //no quedan colocar ciervos

                        return true;
                     }
                }
            }
       }

   }else{ //caso hay mas caminos validos que ciervos

       int x, y;
       bool noOcupado;

       while( (cant_ca_colocados<cantidadCiervosA) || (cant_cb_colocados<cantidadCiervosB) ){

           //tengo las coordenadas aleatorias
           x = rand()%this->vertical;
           y = rand()%this->horizontal;

           if( (this->elementos[x][y]->get_representacion() == '=') || this->elementos[x][y]->get_representacion() == '-' || (this->elementos[x][y]->get_representacion() == '*') ) //si la casilla es un camino valido
           {
               if(this->elementos[x][y]->get_representacion() == 'P'){ //si es pastizal, esto lo uso para definir la bandera y
                                                                       //dsp saber si es la casilla es pastizal o es meseta para hacer
                    esPastizal = true;                                 //correctamente el reinterpreter cast y saber si esta ocupada la casilla

               }else{

                   esPastizal = false; //es meseta
               }

               if(esPastizal){ //es pastizal

                   if( reinterpret_cast< Pastizal * >( this->elementos[x][y] )->getOcupado() ) //si esta ocupado
                   {
                       noOcupado = false;
                   }else{//esta libre
                       noOcupado = true;
                   }

               }else{// era una meseta

                   if( reinterpret_cast< Mesetas * >( this->elementos[x][y] )->getOcupado() ) //si esta ocupado
                   {
                       noOcupado = false;
                   }else{//esta libre
                       noOcupado = true;
                   }
               }

               if(noOcupado) //SI NO ESTA OCUPADO
               {

                   if( (cant_ca_colocados<cantidadCiervosA) && (cant_cb_colocados<cantidadCiervosB) ) //si quedan colocar ciervos a y b
                   {

                       z=rand()%2;

                       if(esPastizal){ //uso el reinterpreter de pastizal

                           switch(z)
                           {
                               case 0: reinterpret_cast< Pastizal * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                                       cant_ca_colocados++;
                                       break;
                               case 1: reinterpret_cast< Pastizal * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                                       cant_cb_colocados++;
                                       break;
                           }

                       }else{ //uso el reinterpreter de meseta

                           switch(z)
                           {
                               case 0: reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                                       cant_ca_colocados++;
                                       break;
                               case 1: reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                                       cant_cb_colocados++;
                                       break;
                           }
                       }

                   }else if( (cant_ca_colocados<cantidadCiervosA) && (cant_cb_colocados>=cantidadCiervosB) ) //solo quedan colocar ciervos a por coloar
                   {

                       if(esPastizal)
                       {
                           reinterpret_cast< Pastizal * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                           cant_ca_colocados++;
                       }else
                       {
                           reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CA() );
                           cant_ca_colocados++;
                       }


                   }else if( (cant_ca_colocados>=cantidadCiervosA) && (cant_cb_colocados<cantidadCiervosB) ) //solo quedan colocar ciervos b
                   {
                       if(esPastizal)
                       {
                           reinterpret_cast< Pastizal * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                           cant_cb_colocados++;
                       }else
                       {
                           reinterpret_cast< Mesetas * >( this->elementos[x][y] )->insertar_poblacion_ciervos( new CB() );
                           cant_cb_colocados++;
                       }

                   }else //no quedan colocar ciervos
                   {
                       return true;
                   }
               }
           }
       }

   }
}

bool Mapa::generarPastizales(int cantPastizales){

    //recordemos q a luego de generar mapa y mapcorrecortor el mapa solo posee mesetas y montanias

    if(cantPastizales == this->cantidadCaminosValidos){ //pregunto si todas las mesetas seran reemplazadas por pastizales


        //en este caso usariamos un barrido convencional para no usar los aleatorios, ya q todas las mesetas se borraran

        for(int x=0;x<this->vertical;x++)
        {
            for(int y=0;y<this->horizontal;y++)
            {
                if(this->elementos[x][y]->get_representacion() == '*') //es una meseta

                    this->setElementSustituto(x,y, new Pastizal() ); //seteamos el pastizal
            }
        }

        return true;

    }else if(cantPastizales < this->cantidadCaminosValidos){ //algunas mesetas seran reemplazadas por pastizales

        int aleatorio_x=0,aleatorio_y=0,x=0;
        while(x<cantPastizales)
        {
            aleatorio_x=rand()%this->vertical;
            aleatorio_y=rand()%this->horizontal;
            if(this->elementos[aleatorio_x][aleatorio_y]->get_representacion() == '*')
            {
                this->setElementSustituto(aleatorio_x,aleatorio_y, new Pastizal() );
                x++;
            }
        }

        return true;

    }else if(cantPastizales >= (this->vertical*this->horizontal) ){ //si la cantidad de pastizales es mayor o igual a la cantidad de casillas del mapo

        for(int x=0;x<this->vertical;x++)
        {
            for(int y=0;y<this->horizontal;y++)
            {
                this->setElementSustituto(x,y, new Pastizal() ); //seteamos el pastizal
            }
        }

        return true;


    }else{ //la cantidad de pastizales es mayor a la cantidad de mesetas pero menor a la cantidad de casillas, por ende deben reemplazarse montanias tambien

        //en este caso usariamos un barrido convencional para no usar los aleatorios, ya q todas las mesetas se borraran

        int pastizales_colocados = 0;

        for(int x=0;x<this->vertical;x++)
        {
            for(int y=0;y<this->horizontal;y++)
            {
                if(this->elementos[x][y]->getRepresentacionOriginal() == '*'){ //es una meseta

                    this->setElementSustituto(x,y, new Pastizal() ); //seteamos el pastizal
                    pastizales_colocados++;
                }
            }
        }//en este punto borre todas las mesetas


        while(pastizales_colocados < cantPastizales ){ //los pastizales q quedan reemplazarian alguna montanias

            int aleator_x=rand()%this->vertical;
            int aleator_y=rand()%this->horizontal;

            if(this->elementos[aleator_x][aleator_y]->get_representacion() == '#')//si es montania
            {

                if( casillaFormaraCaminoValido(aleator_x, aleator_y) )//la montania tiene q estar unida al camino valido si o si, por ende debe tener un pastizal al lado para verificar formara parte del camino al modificarse
                {
                    this->setElementSustituto(aleator_x,aleator_y, new Pastizal() ); //reemplazo pastizal por montania
                    pastizales_colocados++;
                }
            }
        }
    }
}

void Mapa::imprimir_mapa()
{
    for(int x=0;x<this->vertical;x++)
    {
        std::cout<<"   ";
        for(int y=0;y<this->horizontal;y++)
        {

            std::cout<<this->elementos[x][y]->get_representacion()<<" ";
        }
        std::cout<<std::endl;
    }
}

void Mapa::setElementInicial(int x, int y, Elemento* x1){ //funciona bien

    this->elementos[x][y] = x1;

    if(x1->get_representacion() == '#'){

        this->cantidadCaminosInvalidos++;

    }else if(x1->get_representacion() == '?'){

        //no debe hacer nada
    }else{

        this->cantidadCaminosValidos++; //se supone siempre es meseta
    }
}

void Mapa::setElementSustituto(int x, int y, Elemento *x1){ //funciona bien

    //pregunto que voy a reemplazar

    if(this->elementos[x][y]->get_representacion()=='#'){

        this->cantidadCaminosInvalidos--;

    }else if(this->elementos[x][y]->get_representacion()=='?'){

        //no debe hacer nada
    }else{ //se interpreta q va a sacar una meseta, ya q nunca se intenta reemplazar un pastizal

        this->cantidadCaminosValidos--;
    }

    this->elementos[x][y] = x1; //reemplazo

    //pregunto q es lo que seteee:

    if(x1->get_representacion() == '#'){

        this->cantidadCaminosInvalidos++;

    }else if(x1->get_representacion() == '?'){

        //no debe hacer nada
    }else{

        this->cantidadCaminosValidos++;
    }
}

void Mapa::generar_mapa(int cantidadPastizales, int cantCiervosA, int cantCiervosB) //jirho version
{
    this->cantidadCaminosInvalidos=0;
    this->cantidadCaminosValidos=0;

    int aleatorio=0;

    this->elementos = new Elemento** [this->vertical];
    for(int x=0;x<this->vertical;x++)
    {
        this->elementos[x]=new Elemento*[this->horizontal];

        for(int y=0;y<this->horizontal;y++)
        {

            aleatorio=rand()%2;

            switch(aleatorio)
            {

                case 0: this->setElementInicial(x,y, new Montania() );
                        break;

                case 1: this->setElementInicial(x,y, new Mesetas() );
                        break;
            }
        }
    }
    this->mapcorrector(); //corrijo el mapa
    this->generarPastizales(cantidadPastizales);
    std::cout << std::endl;
    this->imprimir_mapa();
    std::cout << std::endl;
    this->generar_ciervos(cantCiervosA, cantCiervosB);
}

void Mapa::mapcorrector(){ //arregla el mapa generado usando chequear para cada posicion del mapa

    for(int x=0;x<this->vertical;x++)
    {
        for(int y=0;y<this->horizontal;y++)
        {
            this->chequear(x,y);
        }
    }
}

bool Mapa::chequear(int pi,int pj) //jirho version
{
    if( this->elementos[pi][pj]->get_representacion() == '*') //si es mesetas, osea es camino valido
    {

        if(pj+1<this->horizontal)//pregunto si existe un elemento a la derecha
        {
            if(this->elementos[pi][pj+1]->get_representacion() != '*')//pregunto si el de la derecha NO es un camino valido
            {
                if (pi+1<this->vertical)//pregunto si el de abajo existe
                {
                    if(this->elementos[pi+1][pj]->get_representacion() != '*') //pregunto si el de abajo NO es un camino valido
                    {
                        this->setElementSustituto(pi,pj+1, new Mesetas() ); // si no es convierto el de la derecha en un camino valido
                        return true;
                    }
                    return true;
                }
                this->setElementSustituto(pi,pj+1, new Mesetas() ); //si el de abajo no existe convierto el de la derecha en un camino valido
                return true;
            }
            else return true;

        }else if (pi+1<this->vertical) //pregunta si existe uno arriba
        {
            if(this->elementos[pi+1][pj]->get_representacion() != '*') //pregunto si el de arriba no es un camino valido
            {
                this->setElementSustituto(pi+1,pj, new Mesetas() ); //convierto el de arriba en un camino valido
            }
        }
    }
    return true;
}

int Mapa::esperar()
{
    std::cout << std::endl;
    for(int i=0;i<this->tiempo_de_retardo;i++)
    {
        Sleep(1000);
        std::cout << ".";
    }
    std::cout << std::endl;
}

Mapa::~Mapa(){

    delete this;
}
