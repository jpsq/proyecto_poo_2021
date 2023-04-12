#ifndef CIERVO_H
#define CIERVO_H
#include "elemento.h"
#include "mapa.h"
#include "estructuras.h"

class ciervo
{
private:
    char representacion;
    int hambre=0;
    bool recienSeteado=false;
public:
    ciervo();
    ciervo(int hambre, bool recienSeteado);
    void movimiento();
    bool moverse(Mapa* m, int x, int y, int indice);
    void reproduccion();
    void alimentarse(Elemento* casilla, int indice); //se invoca al caer a una casilla, si tiene comida come, gana hambre y muere
    void unir_poblacion();
    bool intentarMoverseAbajo(Mapa *mapa, int x, int y, int indice);
    bool intentarMoverseArriba(Mapa *mapa, int x, int y, int indice);
    bool intentarMoverseDerecha(Mapa *mapa, int x, int y, int indice);
    bool intentarMoverseIzquierda(Mapa *mapa, int x, int y, int indice);
    char getRepresentacion() const;
    void setRepresentacion(char newRepresentacion);
    virtual void interactua(ciervo* ciervo, Elemento* casilla) = 0;
    eciervo getStruct();


    bool getRecienSeteado() const;
    void setRecienSeteado(bool newRecienSeteado);
};

#endif // CIERVO_H
