#include "cliente.h"

Cliente::Cliente(QObject *parent) : QObject(parent)
{
    m_cedula = "9999999999";
    m_nombre = "CONSUMIDOR FINAL";
    m_telefono = "N/A";
    m_correo = "N/A";
    m_direccion = "N/A";
}

Cliente::Cliente(QString cedula, QString nombre, QString telefono, QString correo, QString direccion)
{
    m_cedula = cedula;
    m_nombre = nombre;
    m_telefono = telefono;
    m_correo = correo;
    m_direccion = direccion;
}

QString Cliente::informacion()
{
    return "Cedula: " + m_cedula +
            "\nNombre: " + m_nombre +
            "\nTelefono: " + m_telefono +
            "\nE-mail: " + m_correo +
            "\nDirección: " + m_direccion;
}
