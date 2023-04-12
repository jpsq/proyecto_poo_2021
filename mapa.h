#ifndef MAPA_H
#define MAPA_H
#include <elemento.h>
#include <vector>
#include <fstream>
#include "estructuras.h"

class Mapa
{
private:
    Elemento*** elementos;
    //indican tamanio del mapa:
    int horizontal=0;
    int vertical=0;
    int tiempo_de_retardo=0;
    //estos atributos los usare para el control de la generacion de pastizales
    int cantidadCaminosValidos = 0;
    int cantidadCaminosInvalidos = 0; //montanias
    int diasSimulacion;
public:
    Mapa();
    Mapa(int v,int h);
    Mapa(int v,int h, int t);
    void generar_mapa(int cantPastizales, int cantCiervosA, int cantCiervosB);
    void mapcorrector();
    void imprimir_mapa();
    bool chequear(int pi,int pj);
    int esperar();
    bool generarPastizales(int cantidadPastizales);
    void setElementInicial(int x, int y, Elemento* x1); // este es para setear elemento en un lugar vacio de la matriz
    void setElementSustituto(int x, int y, Elemento* x1); // este es para setear elemento en un lugar ocupado de la matriz
    void setearPastizales(int cantPastizales);
    bool generar_ciervos(int cantidadCiervosA, int cantidadCiervosB); //setea los ciervos en el mapa
    void pasar_dia(); //invoca pasar_dia para todas sus casillas con tal funcionamiento
    void pasar_dia_para_ciervos(); //esta funcion crashea a veces
    bool esMeseta(int x, int y);
    bool esPastizal(int x, int y);
    bool esMontania(int x, int y);
    bool casillaFormaraCaminoValido(int x, int y);
    void cargarMapaDesdeArchivo();
    void guardarMapaEnArchivo(int diasPasadosSimulacion);

    int getCantidadCaminosValidos() const;
    void setCantidadCaminosValidos(int newCantidadCaminosValidos);
    int getCantidadCaminosInvalidos() const;
    void setCantidadCaminosInvalidos(int newCantidadCaminosInvalidos);
    Elemento* getElemento(int x, int y);
    int getHorizontal() const;
    int getVertical() const;


    ~Mapa();
    int getDiasSimulacion() const;
};

#endif // MAPA_H
