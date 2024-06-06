#ifndef AGREGARCONTACTO_H
#define AGREGARCONTACTO_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>

#include "contacto.h"

namespace Ui {
class AgregarContacto;
}

class AgregarContacto : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarContacto(QWidget *parent = nullptr);
    ~AgregarContacto();

    Contacto *contacto() const;

private slots:
    void on_inNombre_editingFinished();
    void on_inExtencion_valueChanged(int arg1);

    void on_cmbSede_currentIndexChanged(int index);

    void on_buttonBox_accepted();

private:
    Ui::AgregarContacto *ui;

    void puedeCerrar();

    QStringList CAMPUS_QUITO = {"Girón", "Sur", "Cayambe"};
    QStringList CAMPUS_CUENCA = {"El Vecino", "Rectorado"};
    QStringList CAMPUS_GUAYAQUIL = {"Centenario", "María Auxiliadora", "Edificio Administrativo"};

    Contacto *m_contacto;

};

#endif // AGREGARCONTACTO_H
