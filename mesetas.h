#ifndef MESETAS_H
#define MESETAS_H
#include "elemento.h"
#include "ciervo.h"
#include <QPixmap>


class Mesetas:public Elemento
{
private:
    ciervo** ciervos = new ciervo* [150]; //si se quisiese meter mas de 150 ciervos en una casilla el programa explota
    int cantidadCiervos=0;
    bool ocupado = false;
    QPixmap* pix;
    QPixmap* pix_ca;
    QPixmap* pix_cb;
    QPixmap* pix_multiples;
public:
    Mesetas();
    Mesetas(char representacion1, int representacionGrafica1, bool ocupado1, int cantCiervos1, eciervo ciervitos[14]);
    void insertar_poblacion_ciervos(ciervo* poblacion1);
    void quitarCiervo(int indice);
    void interacciones();
    eelemento getStruct();

    ciervo* getPrimerCiervo();
    int getCantidadCiervos() const;
    void setCantidadCiervos(int newCantidadCiervos);
    bool getOcupado() const;
    void setOcupado(bool x);
    ciervo* getCiervo(int indice);
};

#endif // MESETAS_H

