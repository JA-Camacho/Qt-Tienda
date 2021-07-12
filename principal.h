#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include "producto.h"
#include "verificador.h"
#include "cliente.h"
#include "resumen.h"
#define IVA 12
QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();
    bool verificador(QString cedula);
    void limpiar();
private slots:
    void on_cmdAgregar_released();
    void on_inProducto_currentIndexChanged(int index);
    void on_cmdCompra_released();

private:
    Ui::Principal *ui;
    QList<Producto*> m_productos;
    float m_subtotal;
    float m_iva;
    float m_total;
    QString informacion;
    void calcular(float stProducto);
};
#endif // PRINCIPAL_H
