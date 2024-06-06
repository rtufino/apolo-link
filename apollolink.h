#ifndef APOLLOLINK_H
#define APOLLOLINK_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QCloseEvent>

#include "contacto.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ApolloLink; }
QT_END_NAMESPACE

class ApolloLink : public QMainWindow
{
    Q_OBJECT

public:
    ApolloLink(QWidget *parent = nullptr);
    ~ApolloLink();

private slots:
    void on_cmbSede_currentIndexChanged(int index);
    void on_btnAgregar_released();

    void on_btnGuardar_released();

    void on_tblContactos_itemChanged(QTableWidgetItem *item);

    void closeEvent(QCloseEvent *event);


    void on_actionEliminar_triggered();

    void on_actionGuardar_triggered();

    void on_btnBuscar_released();

    void on_inBuscar_returnPressed();

private:
    Ui::ApolloLink *ui;
    const QString ARCHIVO = "agenda.csv";

    QStringList CAMPUS_QUITO = {"Girón", "Sur", "Cayambe"};
    QStringList CAMPUS_CUENCA = {"El Vecino"};
    QStringList CAMPUS_GUAYAQUIL = {"Centenario", "María Auxiliadora", "Edificio Administrativo"};

    QList<Contacto *> m_contactos;

    enum Estado{
        OK, CARGANDO, AGREGANDO
    };

    Estado mEstado;
    bool mSinGuardar;

    enum Columna{
        NOMBRE, EXTENCION, CARGO, UNIDAD, SEDE, CAMPUS, EMAIL, CELULAR
    };

    void cargarContactos();
    void agregarATabla(Contacto *);
    void limpiar();
    bool guardarContactos();
    int estaRepetida(int ext);
};
#endif // APOLLOLINK_H
