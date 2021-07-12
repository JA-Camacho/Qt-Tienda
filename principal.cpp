#include "principal.h"
#include "ui_principal.h"
#include <QDebug>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    m_productos.append(new Producto(1,"Leche",0.85));
    m_productos.append(new Producto(2,"Pan",0.15));
    m_productos.append(new Producto(3,"Queso",2.0));
    for(int i = 0; i< m_productos.size(); i++)
        ui->inProducto->addItem(m_productos.at(i)->nombre());
    //Colocar la cabecera de la tabla
    QStringList cabecera = {"Cantidad", "Producto", "SubTotal"};
    ui->outDetalle->setColumnCount(3);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    //Inicializar subtotal global
    m_subtotal = 0;
}

Principal::~Principal()
{
    delete ui;
}

bool Principal::verificador(QString cedula)
{
    //Creamos una lista temporal
    QString temp[10];
    int aux;
    int sumaPar = 0;
    int sumaImpar = 0;
    //Recogemos de la cedula los 9 primeros digitos
    for(int i = 0; i < 9; i++)
    {
        //A la lista temporal le vamos ingresando los valores de la cedula uno por uno
        temp[i] = cedula[i];
        //Le damos el valor de la lista temporal, en posicion i, a la variable aux
        aux = temp[i].toInt();
        //Si i + 1 es par
        if((i+1)%2==0)
            //Se aumenta a sumaPar
            sumaPar += aux;
        //Si no
        else
        {
            //Si al multiplicar el aux por 2 rebasa 9
            if(aux * 2 > 9)
                //Aumentaremos a sumaImpar el aux multiplicado por 2 y restado 9
                sumaImpar = sumaImpar + ((aux * 2) - 9);
            //Si no
            else
                //Se aumenta a sumaImpar
                sumaImpar += aux * 2;
        }
    }
    //Se obtiene el ultimo digito de la cedula
    int ultimoCedula = cedula.toInt()%10;
    //Obtenemos el módulo de la suma de los numeros pares e impares
    int verificador = (sumaPar + sumaImpar)%10;
    //Si verificador es diferente de cero
    if(verificador !=0)
        //De 10 se le resta el verificador
        verificador = 10 - verificador;
    return ultimoCedula == verificador? true : false;
}

void Principal::limpiar()
{
    ui->inCedula->clear();
    ui->inNombre->clear();
    ui->inTelefono->clear();
    ui->inEmail->clear();
    ui->inDireccion->clear();
    informacion.clear();
    ui->outDetalle->clear();
    m_subtotal = 0;
    ui->outSubtotal->setText("$ " + QString::number(m_subtotal, 'f', 2));
    ui->outIva->setText("$ " + QString::number(0.0, 'f', 2));
    ui->outTotal->setText("$ " + QString::number(0.0, 'f', 2));
}


void Principal::on_cmdAgregar_released()
{
    //Obtener datos de la GUI
    int cantidad = ui->inCantidad->value();

    //Validar que no se agreguen productos con 0 cantidad
    if(cantidad == 0)
        return;
    int index = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(index);

    //Calcular el subtotal del producto
    float subtotal = cantidad * p->precio();

    //Agregar datos a la tabla
    int fila = ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(fila);
    ui->outDetalle->setItem(fila,0,new QTableWidgetItem(QString::number(cantidad)));
    ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));
    ui->outDetalle->setItem(fila,2,new QTableWidgetItem("$ " + QString::number(subtotal, 'f',2)));

    //Agregar los datos de compra a la informacion
    informacion =informacion + "----------------------------"
                               "\nCant: " + QString::number(cantidad)
            + "\nProducto: " + p->nombre()
            + "\nSubTotal: $" + QString::number(subtotal,'f',2) + "\n";

    //Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    //Invocar a calcular
    calcular(subtotal);
}


void Principal::on_inProducto_currentIndexChanged(int index)
{
    //Obtener el precio del producto
    float precio = m_productos.at(index)->precio();
    ui->outPrecio->setText("$ " + QString::number(precio,'f',2));
}

void Principal::calcular(float stProducto)
{
    m_subtotal += stProducto;
    m_iva = m_subtotal * IVA/100;
    m_total = m_subtotal + m_iva;
    ui->outSubtotal->setText("$ " + QString::number(m_subtotal, 'f', 2));
    ui->outIva->setText("$ " + QString::number(m_iva, 'f', 2));
    ui->outTotal->setText("$ " + QString::number(m_total, 'f', 2));
}

void Principal::on_cmdCompra_released()
{
    //Recibimos la informacion del cliente
    QString cedula = ui->inCedula->text();
    QString nombre = ui->inNombre->text();
    QString telf = ui->inTelefono->text();
    QString correo = ui->inEmail->text();
    QString dir = ui->inDireccion->toPlainText();
    //Si no se ha comprado nada se muestra un mensaje de avertencia
    if(informacion.isEmpty())
        ui->outAdvertencia->setText("<p style=color:#FF0000;><b>Error:</b> La cesta esta vacia!!</p>");

    //Si la cedula esta vacia se muestra un mensaje de advertencia
    else if(cedula.isEmpty())
        ui->outAdvertencia->setText("<p style=color:#FF0000;><b>Error:</b> La cedula debe ser ingresada</p>");

    //Si la cedula es ingresada con 9, se creara un cliente como consumidor final
    else if(cedula == "9999999999")
    {
        Cliente *p = new Cliente();
        Resumen *resumen = new Resumen();
        resumen->setCliente(p->informacion());
        resumen->setResumen(informacion);
        resumen->setSubtotal("$ " + QString::number(m_subtotal, 'f', 2));
        resumen->setIva("$ " + QString::number(m_iva, 'f', 2));
        resumen->setTotal("$ " + QString::number(m_total, 'f', 2));
        resumen->show();
        limpiar();
    }
    //Si el nombre esta vacio se muestra un mensaje de advertencia
    else if(nombre.isEmpty())
        ui->outAdvertencia->setText("<p style=color:#FF0000;><b>Error:</b> El nombre debe ser ingresado</p>");

    //Si la cedula es valida, se crea el cliente y se muestra la compra
    else if(verificador(cedula))
    {
        Cliente *p = new Cliente(cedula, nombre, telf, correo, dir);
        Resumen *resumen = new Resumen();
        resumen->setCliente(p->informacion());
        resumen->setResumen(informacion);
        resumen->setSubtotal("$ " + QString::number(m_subtotal, 'f', 2));
        resumen->setIva("$ " + QString::number(m_iva, 'f', 2));
        resumen->setTotal("$ " + QString::number(m_total, 'f', 2));
        resumen->show();
        limpiar();
    }
    //Si la cedula no es valida, se muestra un mensaje de advertencia
    else if(!verificador(cedula))
        ui->outAdvertencia->setText("<p style=color:#FF0000;><b>Error:</b> La cedula que ha ingresado es Incorrecta</p>");
}
