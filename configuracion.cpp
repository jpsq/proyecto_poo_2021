#include "configuracion.h"
#include "ui_configuracion.h"

configuracion::configuracion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configuracion)
{
    ui->setupUi(this);
}

configuracion::~configuracion()
{
    delete ui;
}

void configuracion::setVentanaAsociada(MainWindow *m)
{
    this->mwasociada = m;
}

void configuracion::on_cambiar_vertical_clicked()
{
    mwasociada->setCasillas_verticales( this->ui->spinvertical->value() );
    this->ui->spinvertical->setValue(0);
    QString aux = QString::number( mwasociada->getCasillas_verticales() );//parseo
    this->ui->labelvertical->setText( aux  ); //seteo en el label
}


void configuracion::on_cambiar_horizontal_clicked()
{
    mwasociada->setCasillas_horizontales( this->ui->spinhorizontal->value() );
    this->ui->spinhorizontal->setValue(0);
    QString aux = QString::number( mwasociada->getCasillas_horizontales() );//parseo
    this->ui->labelhorizontal->setText( aux ); //seteo en el label
}


void configuracion::on_cambiar_pastizales_clicked()
{
    mwasociada->setCantidad_de_pastizales( this->ui->spinpastizales->value() );
    this->ui->spinpastizales->setValue(0);
    QString aux = QString::number( mwasociada->getCantidad_de_pastizales() );//parseo
    this->ui->labelpastizales->setText( aux  ); //seteo en el label
}


void configuracion::on_cambiar_ca_clicked()
{
    mwasociada->setCantidad_de_ciervos_A( this->ui->spinca->value() );
    this->ui->spinca->setValue(0);
    QString aux = QString::number( mwasociada->getCantidad_de_ciervos_A() );//parseo
    this->ui->labelca->setText( aux ); //seteo en el label
}


void configuracion::on_cambiar_cb_clicked()
{
    mwasociada->setCantidad_de_ciervos_B( this->ui->spincb->value() );
    this->ui->spincb->setValue(0);
    QString aux = QString::number( mwasociada->getCantidad_de_ciervos_B() );//parseo
    this->ui->labelcb->setText( aux ); //seteo en el label
}


void configuracion::on_cabiar_tiempo_clicked()
{
    mwasociada->setCantidad_de_tiempo( this->ui->spintiempo->value() );
    this->ui->spintiempo->setValue(0);
    QString aux = QString::number( mwasociada->getCantidad_de_tiempo() );//parseo
    this->ui->labeltiempo->setText( aux ); //seteo en el label
}

void configuracion::cargarLabels(int vertical, int horizontal, int pastizales, int ca, int cb, int tiempo)
{
    //setea los valores de la configuracion actual de la main windows es los labels de esta ventana:

    QString aux = QString::number(vertical);
    this->ui->labelvertical->setText(aux);

    aux = QString::number(horizontal);
    this->ui->labelhorizontal->setText(aux);

    aux = QString::number(pastizales);
    this->ui->labelpastizales->setText(aux);

    aux = QString::number(ca);
    this->ui->labelca->setText(aux);

    aux = QString::number(cb);
    this->ui->labelcb->setText(aux);

    aux = QString::number(tiempo);
    this->ui->labeltiempo->setText(aux);
}



