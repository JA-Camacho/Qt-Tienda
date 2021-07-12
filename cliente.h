#ifndef CLIENTE_H
#define CLIENTE_H

#include <QObject>

class Cliente : public QObject
{
    Q_OBJECT
private:
    QString m_cedula;
    QString m_nombre;
    QString m_telefono;
    QString m_correo;
    QString m_direccion;
public:
    explicit Cliente(QObject *parent = nullptr);
    Cliente(QString cedula, QString nombre, QString telefono, QString correo, QString direccion);
    QString informacion();
signals:

};

#endif // CLIENTE_H
