#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <mapa.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getCasillas_verticales() const;
    void setCasillas_verticales(int newCasillas_verticales);

    int getCasillas_horizontales() const;
    void setCasillas_horizontales(int newCasillas_horizontales);
    int getCantidad_de_ciervos_A() const;
    void setCantidad_de_ciervos_A(int newCantidad_de_ciervos_A);
    int getCantidad_de_ciervos_B() const;
    void setCantidad_de_ciervos_B(int newCantidad_de_ciervos_B);
    int getCantidad_de_pastizales() const;
    void setCantidad_de_pastizales(int newCantidad_de_pastizales);
    int getCantidad_de_tiempo() const;
    void setCantidad_de_tiempo(int newCantidad_de_tiempo);

private slots:


    void borrar_grid();

    void contar();

    void inicializar();

    void pasar_dias();

    void on_generar_mapa_clicked();

    void on_boton_abrir_clicked();

    void on_boton_pausa_clicked();

    void on_boton_reanudar_clicked();

    void on_boton_guardar_clicked();

    void on_actionOpciones_de_simulacion_triggered();

    void on_actionAbrir_triggered();

    void on_actionGuardar_triggered();

    void on_actionVer_integrantes_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *** labels;
    QTimer* tiempo;
    Mapa* un_mapa;

    int casillas_verticales=30;
    int casillas_horizontales=30;
    int cantidad_de_ciervos_A=0;
    int cantidad_de_ciervos_B=0;
    int cantidad_de_pastizales=0;
    int cantidad_de_tiempo=10;
    int contador=0;
    int dias_pasados=0;
};
#endif // MAINWINDOW_H
