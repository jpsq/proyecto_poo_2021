#ifndef CONFIGURACION_H
#define CONFIGURACION_H
#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class configuracion;
}

class configuracion : public QDialog
{
    Q_OBJECT

public:
    explicit configuracion(QWidget *parent = nullptr);
    ~configuracion();
    void setVentanaAsociada(MainWindow* m);

    void cargarLabels(int vertical, int horizontal, int pastizales, int ca, int cb, int tiempo);

private slots:

    void on_cambiar_vertical_clicked();

    void on_cambiar_horizontal_clicked();

    void on_cambiar_pastizales_clicked();

    void on_cambiar_ca_clicked();

    void on_cambiar_cb_clicked();

    void on_cabiar_tiempo_clicked();

private:
    Ui::configuracion *ui;
    MainWindow *mwasociada;

};

#endif // CONFIGURACION_H
