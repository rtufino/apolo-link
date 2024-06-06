#include "agregarcontacto.h"
#include "ui_agregarcontacto.h"

AgregarContacto::AgregarContacto(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AgregarContacto)
{
    ui->setupUi(this);
    // Desahibilitar botones
    ui->buttonBox->setEnabled(false);
    // Iniciando combos
    on_cmbSede_currentIndexChanged(ui->cmbSede->currentIndex());
}

AgregarContacto::~AgregarContacto()
{
    delete ui;
}

void AgregarContacto::puedeCerrar()
{
    QString nombre = ui->inNombre->text();
    int extencion = ui->inExtencion->value();

    if (!nombre.isEmpty() && extencion != 0){
       ui->buttonBox->setEnabled(true);
    }
}

Contacto *AgregarContacto::contacto() const
{
    return m_contacto;
}

void AgregarContacto::on_inNombre_editingFinished()
{
    puedeCerrar();
}


void AgregarContacto::on_inExtencion_valueChanged(int arg1)
{
    puedeCerrar();
}


void AgregarContacto::on_cmbSede_currentIndexChanged(int index)
{
    ui->cmbCampus->clear();
    switch (index) {
    case 0:
        ui->cmbCampus->addItems(CAMPUS_CUENCA);
        break;
    case 1:
        ui->cmbCampus->addItems(CAMPUS_GUAYAQUIL);
        break;
    case 2:
        ui->cmbCampus->addItems(CAMPUS_QUITO);
        break;
    default:
        break;
    }
}


void AgregarContacto::on_buttonBox_accepted()
{
    QString nombre = ui->inNombre->text();
    int extencion = ui->inExtencion->value();
    QString sede = ui->cmbSede->currentText();
    QString campus = ui->cmbCampus->currentText();
    QString cargo = ui->inCargo->text();
    QString unidad = ui->inUnidad->text();
    QString celular = ui->inCelular->text();
    QString correo = ui->inCorreo->text();

    m_contacto = new Contacto(nombre,sede,campus,cargo,unidad,extencion,celular,correo);
}

