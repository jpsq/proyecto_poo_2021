#ifndef PASTIZAL_H
#define PASTIZAL_H
#include <elemento.h>
#include "ciervo.h"

class Pastizal:public Elemento
{
private:

    ciervo** ciervos = new ciervo* [150]; //si se quisiese meter mas de 150 ciervos en una casilla el programa explota
    int cantidadCiervos=0;
    bool ocupado = false;
    //propias del pastizal:
    char vivo= '=';
    char seco= '-';
    int cantidad_de_dias=0;
    int regeneracion=0;
    bool estaSeco=false;

    QPixmap* pix;
    QPixmap* pix_ca;
    QPixmap* pix_cb;
    QPixmap* pix_multiples;
    QPixmap* pix_seco;
    QPixmap* pix_seco_ca;
    QPixmap* pix_seco_cb;
    QPixmap* pix_seco_multiples;

public:
    Pastizal();
    Pastizal(char representacion1, int representacionGrafica1, bool ocupado1, int cantCiervos1, int cantDias1, bool estaSeco1, int regeneracion1, eciervo ciervitos[14]);
    void insertar_poblacion_ciervos(ciervo* poblacion1);
    void pasar_dia();
    void quitarCiervo(int indice);
    void secar();
    void crecer();
    void interacciones();
    eelemento getStruct();

    //setters y getters

    ciervo* getPrimerCiervo();
    bool getOcupado() const;
    void setOcupado(bool newOcupado);
    char getSeco() const;
    bool estaSecoEstePastizal();
    ciervo* getCiervo(int indice);


    int getCantidadCiervos() const;
};

#endif // PASTIZAL_H
