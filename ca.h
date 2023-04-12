#ifndef CA_H
#define CA_H
#include "ciervo.h"

class CA:public ciervo
{
private:
    char representacion;
public:
    CA();
    CA(int hambre, bool recienSeteado);
    void interactua(ciervo* ciervo, Elemento* casilla);
};

#endif // CA_H
