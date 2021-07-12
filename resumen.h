#ifndef RESUMEN_H
#define RESUMEN_H

#include <QWidget>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
namespace Ui {
class Resumen;
}

class Resumen : public QWidget
{
    Q_OBJECT
public:
    explicit Resumen(QWidget *parent = nullptr);
    ~Resumen();
    void setCliente(QString cliente);
    void setResumen(QString informacion);
    void setSubtotal(QString subtotal);
    void setIva(QString iva);
    void setTotal(QString total);

private slots:
    void on_cmdGuardar_released();

private:
    Ui::Resumen *ui;
};

#endif // RESUMEN_H
