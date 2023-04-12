#ifndef ELEMENTO_H
#define ELEMENTO_H
#include <QPixmap>
#include "estructuras.h"

class Elemento
{
private:
    char representacion = '?';
    char representacionOriginal = '?';
    QPixmap* representacionGrafica;
public:
    Elemento();
    char get_representacion(); //getRepresentacion()
    void setRepresentacion(char newRepresentacion);
    ~Elemento(); //no funciona
    char getRepresentacionOriginal() const;
    void setRepresentacionOriginal(char newRepresentacionOriginal);
    QPixmap* getRepresentacionGrafica();
    void setRepresentacionGrafica(QPixmap *newRepresentacionGrafica);
    virtual eelemento getStruct() = 0;
};

#endif // ELEMENTO_H
