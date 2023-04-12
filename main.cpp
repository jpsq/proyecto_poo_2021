#include "mainwindow.h"
#include "QMessageBox"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QMessageBox ms;
    ms.setText(QString::fromStdString(
                   "Bienvenido al Simulador de Especies.\n "
                   "Primeramente debera definir las caracteristicas de la simulacion en el menu superior.\n "
                   "Advertencia: al generar una simulacion con un mapa de dimensiones menores a las del mapa\n"
                   "de la simulacion previa, la simulacion nueva no se visualizara correctamente.\n"
                   "Recomendamos reiniciar el programa previo a cargar una simulacion guardada." ));
    ms.exec();
    return a.exec();
}
