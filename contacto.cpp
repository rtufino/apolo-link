#include "contacto.h"

Contacto::Contacto(QObject *parent)
    : QObject{parent}
{

}

QString Contacto::nombre() const
{
    return mNombre;
}

void Contacto::setNombre(const QString &newNombre)
{
    if (mNombre == newNombre)
        return;
    mNombre = newNombre;
    emit nombreChanged();
}

QString Contacto::sede() const
{
    return mSede;
}

void Contacto::setSede(const QString &newSede)
{
    if (mSede == newSede)
        return;
    mSede = newSede;
    emit sedeChanged();
}

QString Contacto::campus() const
{
    return mCampus;
}

void Contacto::setCampus(const QString &newCampus)
{
    if (mCampus == newCampus)
        return;
    mCampus = newCampus;
    emit campusChanged();
}

QString Contacto::cargo() const
{
    return mCargo;
}

void Contacto::setCargo(const QString &newCargo)
{
    if (mCargo == newCargo)
        return;
    mCargo = newCargo;
    emit cargoChanged();
}

QString Contacto::unidad() const
{
    return mUnidad;
}

void Contacto::setUnidad(const QString &newUnidad)
{
    if (mUnidad == newUnidad)
        return;
    mUnidad = newUnidad;
    emit unidadChanged();
}

int Contacto::extencion() const
{
    return mExtencion;
}

void Contacto::setExtencion(int newExtencion)
{
    if (mExtencion == newExtencion)
        return;
    mExtencion = newExtencion;
    emit extencionChanged();
}

QString Contacto::celular() const
{
    return mCelular;
}

void Contacto::setCelular(const QString &newCelular)
{
    if (mCelular == newCelular)
        return;
    mCelular = newCelular;
    emit celularChanged();
}

QString Contacto::correo() const
{
    return mCorreo;
}

void Contacto::setCorreo(const QString &newCorreo)
{
    if (mCorreo == newCorreo)
        return;
    mCorreo = newCorreo;
    emit correoChanged();
}

QString Contacto::toCSV() const
{
    return this->nombre() + ";" +
           QString::number(this->extencion()) + ";" +
           this->cargo() + ";" +
           this->unidad() + ";" +
           this->sede() + ";" +
           this->campus() + ";" +
           this->correo() + ";" +
           this->celular() + ";";
}
;
Contacto::Contacto(const QString &nombre, const QString &sede, const QString &campus, const QString &cargo, const QString &unidad, int extencion, const QString &celular, const QString &correo) :
    mNombre(nombre),
    mSede(sede),
    mCampus(campus),
    mCargo(cargo),
    mUnidad(unidad),
    mExtencion(extencion),
    mCelular(celular),
    mCorreo(correo)
{}

Contacto::Contacto(const QString &csvLine){
    QStringList datos = csvLine.split(";");
    mNombre = datos[0];
    mExtencion = datos[1].toInt();
    mCargo = datos[2];
    mUnidad = datos[3];
    mSede = datos[4];
    mCampus = datos[5];
    mCorreo = datos[6];
    if (datos.size()>7)
        mCelular = datos[7];
}
