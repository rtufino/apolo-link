#ifndef APOLLOLINK_H
#define APOLLOLINK_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include <QDebug>

#include "contacto.h"
#include "agregarcontacto.h"

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
    void on_btnGuardar_released();

    void closeEvent(QCloseEvent *event);

    void on_actionEliminar_triggered();

    void on_actionGuardar_triggered();

    void on_btnBuscar_released();

    void on_inBuscar_returnPressed();

    void on_actionNuevo_triggered();

    void on_tblContactos_itemChanged(QTableWidgetItem *item);

private:
    Ui::ApolloLink *ui;
    const QString ARCHIVO = "agenda.csv";

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
    bool guardarContactos();
    int estaRepetida(int ext);
};
#endif // APOLLOLINK_H
