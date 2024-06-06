#include "apollolink.h"
#include "ui_apollolink.h"

ApolloLink::ApolloLink(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ApolloLink)
{
    ui->setupUi(this);

    // setWindowIcon(QIcon("://app.png"));
    // Iniciando combos
    on_cmbSede_currentIndexChanged(ui->cmbSede->currentIndex());
    mEstado = Estado::CARGANDO;
    // Configurar la tabla
    QStringList titulo;
    titulo << "Nombre" << "Extención" << "Cargo" << "Unidad" << "Sede" << "Campus" << "E-mail" << "Celular";
    ui->tblContactos->setColumnCount(titulo.size());
    ui->tblContactos->setHorizontalHeaderLabels(titulo);
    // cargar datos
    this->cargarContactos();
    mEstado = Estado::OK;
    this->mSinGuardar = false;
}

ApolloLink::~ApolloLink()
{
    delete ui;
}


void ApolloLink::on_cmbSede_currentIndexChanged(int index)
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

void ApolloLink::cargarContactos()
{
    // Verificar si el archivo existe
    QFile archivo(ARCHIVO);
    if (!archivo.exists())
        return;

    // cargar datos
    if (archivo.open(QFile::ReadOnly)) {
        QTextStream entrada(&archivo);
        while(!entrada.atEnd()){
            Contacto *c = new Contacto(entrada.readLine());
            agregarATabla(c);
        }
        archivo.close();
    }
}

void ApolloLink::agregarATabla(Contacto *c)
{
    // "Nombre" << "Extención" << "Celular" << "E-mail" << "Cargo"
    int fila = ui->tblContactos->rowCount();
    ui->tblContactos->insertRow(fila);
    ui->tblContactos->setItem(fila, NOMBRE, new QTableWidgetItem(c->nombre()));
    ui->tblContactos->setItem(fila, EXTENCION, new QTableWidgetItem(QString::number(c->extencion())));
    ui->tblContactos->setItem(fila, CELULAR, new QTableWidgetItem(c->celular()));
    ui->tblContactos->setItem(fila, EMAIL, new QTableWidgetItem(c->correo()));
    ui->tblContactos->setItem(fila, CARGO, new QTableWidgetItem(c->cargo()));
    ui->tblContactos->setItem(fila, UNIDAD, new QTableWidgetItem(c->unidad()));
    ui->tblContactos->setItem(fila, SEDE, new QTableWidgetItem(c->sede()));
    ui->tblContactos->setItem(fila, CAMPUS, new QTableWidgetItem(c->campus()));

    this->m_contactos.append(c);

    this->limpiar();
}

void ApolloLink::limpiar()
{
    ui->inNombre->clear();
    ui->cmbSede->setCurrentIndex(0);
    ui->inExtencion->setValue(0);
    ui->inCargo->clear();
    ui->inUnidad->clear();
    ui->inCelular->clear();
    ui->inCorreo->clear();

    ui->inNombre->setFocus();

}

bool ApolloLink::guardarContactos()
{
    // Abrir el archivo y guardar
    QFile archivo(ARCHIVO);
    if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream salida(&archivo);
        foreach (Contacto *c, m_contactos) {
            salida << c->toCSV() + "\n";
        }
        archivo.close();
        this->mSinGuardar = false;
        return true;
    }
    return false;


}

int ApolloLink::estaRepetida(int ext)
{
    int i = 0;
    foreach (Contacto *c, m_contactos) {
        if (c->extencion() == ext)
            return i;
        i++;
    }
    return -1;
}

void ApolloLink::on_btnAgregar_released()
{
    QString nombre = ui->inNombre->text();
    int extencion = ui->inExtencion->value();

    if (nombre.isEmpty() || extencion == 0){
        QMessageBox::warning(this,"Agregar contacto", "El nombre o extención no pueden estar vacíos");
        if (nombre.isEmpty())
            ui->inNombre->setFocus();
        else
            ui->inExtencion->setFocus();
        return;
    }

    int existe = estaRepetida(extencion);
    if (existe >= 0){
        QMessageBox::warning(this,"Agregar contacto", "La extención ya está registrado a otro contacto");
        ui->tblContactos->selectRow(existe);
        limpiar();
        return;
    }

    QString sede = ui->cmbSede->currentText();
    QString campus = ui->cmbCampus->currentText();
    QString cargo = ui->inCargo->text();
    QString unidad = ui->inUnidad->text();
    QString celular = ui->inCelular->text();
    QString correo = ui->inCorreo->text();

    Contacto *c = new Contacto(nombre,sede,campus,cargo,unidad,extencion,celular,correo);
    mEstado = Estado::AGREGANDO;
    agregarATabla(c);
    mEstado = Estado::OK;
    this->mSinGuardar = true;
}


void ApolloLink::on_btnGuardar_released()
{

    // Verificar que exista datos para guardar;
    if (this->m_contactos.size() == 0){
        QMessageBox::warning(this,"Guardar contactos","Agenda sin datos para guardar");
        return;
    }

    if (guardarContactos()){
        QMessageBox::information(this,"Guardar contactos","Contactos guardados con éxito");
    }else{
        QMessageBox::critical(this,"Guardar contactos", "No se puede escribir sobre " + ARCHIVO);
    }
}

void ApolloLink::on_tblContactos_itemChanged(QTableWidgetItem *item)
{
    if (mEstado == Estado::OK){
        Contacto *c = m_contactos.at(item->row());
        switch (item->column()) {
        case NOMBRE:
            c->setNombre(item->text());
            break;
        case EXTENCION:
            c->setExtencion(item->text().toInt());
            break;
        case CARGO:
            c->setCargo(item->text());
            break;
        case UNIDAD:
            c->setUnidad(item->text());
            break;
        case SEDE:
            c->setCargo(item->text());
            break;
        case CAMPUS:
            c->setCampus(item->text());
            break;
        case EMAIL:
            c->setCorreo(item->text());
            break;
        case CELULAR:
            c->setCelular(item->text());
            break;
        default:
            break;
        }
        this->mSinGuardar = true;
    }
}

void ApolloLink::closeEvent(QCloseEvent *event)  // show prompt when user wants to close app
{
    if (this->mSinGuardar){
        event->ignore();
        int respuesta = QMessageBox::warning(this, "Salir de Apolo Link", "Quieres guardar los datos antes de salir?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        switch (respuesta) {
        case QMessageBox::Yes:
            if (!this->guardarContactos()){
                QMessageBox::critical(this,"Guardar contactos", "No se puede escribir sobre " + ARCHIVO);
            }
            break;
        case QMessageBox::No:
            event->accept();
            break;
        default:
            break;
        }
    }

}


void ApolloLink::on_actionEliminar_triggered()
{
    if (mEstado == Estado::OK){
        QTableWidgetItem *item = ui->tblContactos->currentItem();
        if (!item)
            return;
        Contacto *c = m_contactos.at(item->row());
        QString msg = "Quieres eliminar el registro " + QString::number(item->row()+1) + " de " + c->nombre() + "?";
        int respuesta = QMessageBox::warning(this, "Eliminar contacto", msg, QMessageBox::Yes | QMessageBox::No);
        if (respuesta == QMessageBox::Yes){
            m_contactos.removeAt(item->row());
            ui->tblContactos->removeRow(item->row());
            this->mSinGuardar = true;
        }
    }
}


void ApolloLink::on_actionGuardar_triggered()
{
    // Verificar que exista datos para guardar;
    if (this->m_contactos.size() == 0){
        QMessageBox::warning(this,"Guardar contactos","Agenda sin datos para guardar");
        return;
    }

    if (guardarContactos()){
        QMessageBox::information(this,"Guardar contactos","Contactos guardados con éxito");
    }else{
        QMessageBox::critical(this,"Guardar contactos", "No se puede escribir sobre " + ARCHIVO);
    }
}


void ApolloLink::on_btnBuscar_released()
{
    if (ui->inBuscar->text().isEmpty()) return;

    QString nombre = ui->inBuscar->text();

    ui->tblContactos->selectionModel()->select(ui->tblContactos->selectionModel()->selection(),QItemSelectionModel::Deselect);

    int i = 0;
    bool hallo = false;
    ui->tblContactos->setSelectionMode(QAbstractItemView::MultiSelection);
    foreach (Contacto *c, m_contactos) {
        if (c->nombre().contains(nombre,Qt::CaseInsensitive)){
            ui->tblContactos->selectRow(i);
            hallo = true;
        }
        i++;
    }
    ui->tblContactos->setSelectionMode(QAbstractItemView::SingleSelection);

    if (!hallo){
        QMessageBox::information(this,"Buscar contactos","No se encontró contacto");
    }

}


void ApolloLink::on_inBuscar_returnPressed()
{
    this->on_btnBuscar_released();
}

