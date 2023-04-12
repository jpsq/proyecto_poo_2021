#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

struct eciervo{

    char representacion;
    int hambre;
    bool recienSeteado;
};

struct eelemento{

    char representacion;
    char representacionOriginal;
    int representacionGrafica;
    bool ocupado;
    int cantidadCiervos;
    eciervo ciervitos[14]; //nose xq no puedo mas, solo se podrian guardar hasta 14 ciervos
    bool estaSeco;
    int regeneracion;
    int cantDias;
};

struct emapa{

    int vertical;
    int horizontal;
    int tiempo;
    eelemento casillas[100][100]; //como maximo se podria guardar un mapa de 100x100
    int cantDiasSimulacion;
};

#endif // ESTRUCTURAS_H
