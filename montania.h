#ifndef MONTANIA_H
#define MONTANIA_H
#include <elemento.h>

class Montania:public Elemento
{
private:
    QPixmap* pix;

public:
    Montania();
    eelemento getStruct();
    ~Montania();
};

#endif // MONTANIA_H
