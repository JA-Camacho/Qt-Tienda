#include "resumen.h"
#include "ui_resumen.h"

void Resumen::setSubtotal(QString subtotal)
{
    ui->outSubtotal->setText(subtotal);
}

void Resumen::setIva(QString iva)
{
    ui->outIva->setText(iva);
}

void Resumen::setTotal(QString total)
{
    ui->outTotal->setText(total);
    m_total = total;
}

Resumen::Resumen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Resumen)
{
    ui->setupUi(this);
}

Resumen::~Resumen()
{
    delete ui;
}

void Resumen::setCliente(QString cliente)
{
    ui->outCliente->setPlainText(cliente);
}

void Resumen::setResumen(QString informacion)
{
    ui->outResumen->setPlainText(informacion);
}

void Resumen::on_cmdGuardar_released()
{

    //Crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::home();

    //Agregar al path absoluto del objeto un nombre por defecto del archivo
    QString pathArchivo = directorio.absolutePath() + "/Venta.txt";

    //Abrir un cuadro de dialogo para seleccionar el nombre y ubicacion del archivo a guardar
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar archivo", pathArchivo, "Archivo de texto(*.txt)");

    //Crear el archivo a partir del nombre arrojado por el cuadro de dialogo
    QFile f(fileName);

    //Crear el objeto QTextstream (permite escribir sobre el archivo)
    QTextStream out(&f);

    //Intentar abrir el archivo ya sea para escribir(si no existe) o para agregar texto(si existe)
    if(!f.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QMessageBox::warning(this, "Resumen", "No se puede abrir el archivo");
        return;
    }

    //Guardar el contenido
    out << "Cliente\n " << ui->outCliente->toPlainText() << "\nResumen de la compra\n" << ui->outResumen->toPlainText() << "\nTotal: " << m_total << "\n------------";
    f.close();
    this->hide();
}
