#ifndef CONTACTO_H
#define CONTACTO_H

#include <QObject>

class Contacto : public QObject
{
    Q_OBJECT
public:
    explicit Contacto(QObject *parent = nullptr);
    Contacto(const QString &nombre, const QString &sede, const QString &campus, const QString &cargo, const QString &unidad, int extencion, const QString &celular, const QString &correo);
    Contacto(const QString &csvLine);

    QString nombre() const;
    void setNombre(const QString &newNombre);
    QString sede() const;
    void setSede(const QString &newSede);
    QString campus() const;
    void setCampus(const QString &newCampus);
    QString cargo() const;
    void setCargo(const QString &newCargo);
    QString unidad() const;
    void setUnidad(const QString &newUnidad);
    int extencion() const;
    void setExtencion(int newExtencion);
    QString celular() const;
    void setCelular(const QString &newCelular);
    QString correo() const;
    void setCorreo(const QString &newCorreo);

    QString toCSV() const;

signals:

    void nombreChanged();
    void sedeChanged();
    void campusChanged();
    void cargoChanged();
    void unidadChanged();
    void extencionChanged();
    void celularChanged();
    void correoChanged();

private:

    QString mNombre;
    QString mSede;
    QString mCampus;
    QString mCargo;
    QString mUnidad;
    int mExtencion;
    QString mCelular;
    QString mCorreo;

    Q_PROPERTY(QString nombre READ nombre WRITE setNombre NOTIFY nombreChanged)
    Q_PROPERTY(QString sede READ sede WRITE setSede NOTIFY sedeChanged)
    Q_PROPERTY(QString campus READ campus WRITE setCampus NOTIFY campusChanged)
    Q_PROPERTY(QString cargo READ cargo WRITE setCargo NOTIFY cargoChanged)
    Q_PROPERTY(QString unidad READ unidad WRITE setUnidad NOTIFY unidadChanged)
    Q_PROPERTY(int extencion READ extencion WRITE setExtencion NOTIFY extencionChanged)
    Q_PROPERTY(QString celular READ celular WRITE setCelular NOTIFY celularChanged)
    Q_PROPERTY(QString correo READ correo WRITE setCorreo NOTIFY correoChanged)
};

#endif // CONTACTO_H
