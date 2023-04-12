#ifndef CB_H
#define CB_H
#include <ciervo.h>

class CB:public ciervo
{
private:
    char representacion;
public:
    CB();
    CB(int hambre, bool recienSeteado);
    void interactua(ciervo* ciervo, Elemento* casilla);
};

#endif // CB_H
