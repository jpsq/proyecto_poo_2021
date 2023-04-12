#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "string.h"
#include "elemento.h"
#include <stdlib.h>
#include <time.h>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>
#include "configuracion.h"
#include "fstream"
#include "QPixmap"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->tiempo=new QTimer(this);
    this->ui->linea_de_tiempo->setValue(0);
/*    this->casillas_verticales=this->ui->spinBox_vertical->value();
    this->casillas_horizontales=this->ui->spinBox_horizontal->value(); *///setea los valores por defecto en el constructor
    this->ui->linea_de_tiempo->setRange(0,this->cantidad_de_tiempo);
    this->ui->boton_reanudar->setEnabled(false);
}


MainWindow::~MainWindow() //destructor
{
    delete ui;
}

void MainWindow::on_generar_mapa_clicked() //accion del boton generar mapa
{
    connect(tiempo,SIGNAL(timeout()),this,SLOT(contar()));
    this->tiempo->start(1000);
    this->ui->textBrowser->setText(QString("DIAS:"));           //inicializa el contador y llama al constructor del mapa
    this->inicializar();
}

void MainWindow::borrar_grid() //limpia la matriz visual
{
    for (int i = 0; i < this->casillas_verticales; i++)
    {
        for (int j = 0; j < this->casillas_horizontales; j++)   //limpia la matriz de la pantalla
        {
                this->labels[i][j]->clear();
        }
    }
}

void MainWindow::contar() //funcion invocada por el qtimer
{
    this->contador++;
    this->ui->linea_de_tiempo->setValue(this->contador);
    if(this->contador > this->cantidad_de_tiempo)
    {
        this->contador=0;
        this->ui->linea_de_tiempo->setValue(this->contador);   //por cada segundo que pasa se va ejecutando a funcion
        this->borrar_grid();                                   //al cumplirse la condicion se borra el mapa e pantalla
        this->un_mapa->pasar_dia();
        this->pasar_dias();
    }
}

void MainWindow::inicializar() //funcion que genera el mapa
{
    this->dias_pasados=0; //para reiniciar el contador de dias
    un_mapa = new Mapa(casillas_verticales, casillas_horizontales);
    un_mapa->generar_mapa(cantidad_de_pastizales,cantidad_de_ciervos_A,cantidad_de_ciervos_B);
    this->labels = new QLabel**[this->casillas_verticales];

    for (int i = 0; i < this->casillas_verticales; i++)
    {
        this->labels[i] = new QLabel*[this->casillas_horizontales];
            for (int j = 0; j < this->casillas_horizontales; j++)
            {
                    this->labels[i][j] = new QLabel();
                    this->labels[i][j]->setPixmap(*un_mapa->getElemento(i,j)->getRepresentacionGrafica());
                    this->ui->gridLayout->addWidget(labels[i][j] ,i,j);
            }
     }
    this->ui->contador_dias->display(this->dias_pasados);

    //para q los botones de pausa y reanudar esten bien habilitado:
    this->ui->boton_pausa->setEnabled(true);
    this->ui->boton_reanudar->setEnabled(false);
}

void MainWindow::pasar_dias()
{
    for (int i = 0; i < this->casillas_verticales; i++)
    {
            for (int j = 0; j < this->casillas_horizontales; j++)
            {
                    this->labels[i][j]->setPixmap(*un_mapa->getElemento(i,j)->getRepresentacionGrafica() );
                    this->ui->gridLayout->addWidget(labels[i][j] ,i,j);
            }
        }
    this->dias_pasados++;
    this->ui->contador_dias->display(this->dias_pasados);
}

void MainWindow::on_boton_guardar_clicked()
{
    //mostrar mensaje
}

void MainWindow::on_boton_pausa_clicked(){
    this->tiempo->stop();
    this->ui->boton_pausa->setEnabled(false);
    this->ui->boton_reanudar->setEnabled(true);
}

void MainWindow::on_boton_abrir_clicked(){


}

void MainWindow::on_boton_reanudar_clicked(){
    this->tiempo->start();
    this->ui->boton_reanudar->setEnabled(false);
    this->ui->boton_pausa->setEnabled(true);
}


void MainWindow::on_actionOpciones_de_simulacion_triggered() //invocas a la ventana de las configuraciones
{
    configuracion *ventana = new configuracion;
    ventana->setVentanaAsociada(this);
    ventana->show();
    ventana->cargarLabels(casillas_verticales, casillas_horizontales, cantidad_de_pastizales, cantidad_de_ciervos_A, cantidad_de_ciervos_B, cantidad_de_tiempo);
}

int MainWindow::getCasillas_horizontales() const
{
    return casillas_horizontales;
}

void MainWindow::setCasillas_horizontales(int newCasillas_horizontales)
{
    casillas_horizontales = newCasillas_horizontales;
}

int MainWindow::getCantidad_de_ciervos_A() const
{
    return cantidad_de_ciervos_A;
}

void MainWindow::setCantidad_de_ciervos_A(int newCantidad_de_ciervos_A)
{
    cantidad_de_ciervos_A = newCantidad_de_ciervos_A;
}

int MainWindow::getCantidad_de_ciervos_B() const
{
    return cantidad_de_ciervos_B;
}

void MainWindow::setCantidad_de_ciervos_B(int newCantidad_de_ciervos_B)
{
    cantidad_de_ciervos_B = newCantidad_de_ciervos_B;
}

int MainWindow::getCantidad_de_pastizales() const
{
    return cantidad_de_pastizales;
}

void MainWindow::setCantidad_de_pastizales(int newCantidad_de_pastizales)
{
    cantidad_de_pastizales = newCantidad_de_pastizales;
}

int MainWindow::getCantidad_de_tiempo() const
{
    return cantidad_de_tiempo;
}

void MainWindow::setCantidad_de_tiempo(int newCantidad_de_tiempo)
{
    cantidad_de_tiempo = newCantidad_de_tiempo;
}

int MainWindow::getCasillas_verticales() const
{
    return casillas_verticales;
}

void MainWindow::setCasillas_verticales(int newCasillas_verticales)
{
    casillas_verticales = newCasillas_verticales;
}



void MainWindow::on_actionAbrir_triggered()
{
    std::ifstream archivo_de_lectura("archivo.txt");
    std::string contenido;
    int contador_de_linea=0;

    if(archivo_de_lectura.is_open())
    {
            while(!archivo_de_lectura.eof())
            {
                std::getline(archivo_de_lectura,contenido);
                contador_de_linea++;

                switch(contador_de_linea)
                {
                    case 1: this->casillas_verticales=std::stoi(contenido);break;
                    case 2: this->casillas_horizontales=std::stoi(contenido);break;
                    case 3: this->cantidad_de_tiempo=std::stoi(contenido);break;
                    case 4: this->cantidad_de_pastizales=std::stoi(contenido);break;
                    case 5: this->cantidad_de_ciervos_A=std::stoi(contenido);break;
                    case 6: this->cantidad_de_ciervos_B=std::stoi(contenido);break;
                    case 7: this->cantidad_de_tiempo=std::stoi(contenido);this->ui->linea_de_tiempo->setRange(0,this->cantidad_de_tiempo);break;
                    case 8: this->dias_pasados=std::stoi(contenido);break;
                }
            }
    }
    archivo_de_lectura.close();

    //MENSAJE:
    QMessageBox ms;
    ms.setText(QString::fromStdString("Configuracion cargada."));
    ms.exec();
}


void MainWindow::on_actionGuardar_triggered()
{
    std::ofstream archivo("archivo.txt");
    archivo<<this->casillas_verticales<<std::endl;
    archivo<<this->casillas_horizontales<<std::endl;
    archivo<<this->cantidad_de_tiempo<<std::endl;
    archivo<<this->cantidad_de_pastizales<<std::endl;
    archivo<<this->cantidad_de_ciervos_A<<std::endl;
    archivo<<this->cantidad_de_ciervos_B<<std::endl;
    archivo<<this->contador<<std::endl;
    archivo<<this->dias_pasados<<std::endl;
    archivo.close();

    //MENSAJE:
    QMessageBox ms;
    ms.setText(QString::fromStdString("Configuracion guardada."));
    ms.exec();
}


void MainWindow::on_actionVer_integrantes_triggered()
{
    QMessageBox m;
    m.setText(QString::fromStdString("Heili F. - Saluzzo J.P. - Soñez V. "));
    m.exec();
}


void MainWindow::on_pushButton_clicked()
{
    this->un_mapa->guardarMapaEnArchivo(this->dias_pasados);

    QMessageBox m;
    m.setText(QString::fromStdString("Mapa guardado en archivo binario."));
    m.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->un_mapa = new Mapa();
    this->un_mapa->cargarMapaDesdeArchivo();
    this->casillas_horizontales = this->un_mapa->getHorizontal();
    this->casillas_verticales = this->un_mapa->getVertical();

    this->dias_pasados = this->un_mapa->getDiasSimulacion(); //para reiniciar el contador de dias correctamente

    connect(tiempo,SIGNAL(timeout()),this,SLOT(contar()));
    this->tiempo->start(1000);
    this->ui->textBrowser->setText(QString("DIAS:"));

    this->labels = new QLabel**[this->casillas_verticales];

    for (int i = 0; i < this->casillas_verticales; i++)
    {
        this->labels[i] = new QLabel*[this->casillas_horizontales];
            for (int j = 0; j < this->casillas_horizontales; j++)
            {
                    this->labels[i][j] = new QLabel();
                    this->labels[i][j]->setPixmap(*un_mapa->getElemento(i,j)->getRepresentacionGrafica());
                    this->ui->gridLayout->addWidget(labels[i][j] ,i,j);
            }
     }
    this->ui->contador_dias->display(this->dias_pasados);

    //para q los botones de pausa y reanudar esten bien habilitado:
    this->ui->boton_pausa->setEnabled(true);
    this->ui->boton_reanudar->setEnabled(false);
}

