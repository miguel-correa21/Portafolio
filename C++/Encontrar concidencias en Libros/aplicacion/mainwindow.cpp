#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
#include <QDir>
#include <QDebug>
#include <mihilo.h>
#include <map>
#include <iostream>

const QString ruta = "/home/senpai/Documents/ESCOM/SeptimoSemestre/redes2/Practicas/Practica1/Libros";

const std::vector<QString> palabras
{
    "regalos", "besos", "cachondeo","delicioso","compañía",
    "confianza","comunicación","pasión","apoyo"
};


MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir dir(ruta);
    foreach (auto archivo, dir.entryList())
        ui->comboBox->addItem(archivo);
    foreach(auto &palabra,palabras)
    {
        conjunto_datos dato;
        dato.palabra = palabra;
        dato.contador = 0;
        resumen.push_back(dato);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QDir dir2(ruta +"/"+ ui->comboBox->currentText());
    foreach(auto var, dir2.entryInfoList())
        if(var.isFile())
        {
            miHilo *trabajo = new miHilo(var.absoluteFilePath());
            trabajos.push_back(trabajo);
            connect(trabajos.back(),SIGNAL(enviar_datos(miHilo *)),
                    this,SLOT(recibir_datos(miHilo *)));
    //        connect(trabajos.back(),SIGNAL(enviar_trabajo(int)),
     //               this, SLOT(recibir_hilo(int)));
        }

    empezar();
    hacer_resumen();
}

void MainWindow::empezar()
{
    std::cout <<"creando hilos... " << std::endl;
    foreach(miHilo *trabajo, trabajos)
    {
        hilos.emplace_back(std::thread(correr_hilo,trabajo));
        actual = hilos.back().get_id();
    }

    for(size_t i = 0; i < hilos.size(); i++)
        hilos[i].join();
}

void MainWindow::correr_hilo(miHilo *trabajo)
{
   trabajo->run();
}


void MainWindow::recibir_datos(miHilo *datos)
{
    //valor_barprogress += 5;
    //ui->progressBar->setValue(valor_barprogress);
    QStringList aux = datos->get_nombre_libro().split("/");
    ui->listaLIbros->addItem("Archivo :" + aux.back());
    ui->listaLIbros->addItem("hilo :" +
                             QString::number(datos->id_hilo));

    for(size_t i = 0; i < datos->palabras_con_contadores.size(); i++)
    {
        ui->listaLIbros->addItem(
                    datos->palabras_con_contadores[i].palabra + " : " +
                    QString::number(datos->palabras_con_contadores[i].contador));
    }
    ui->listaLIbros->addItem(" ");
    ui->listaLIbros->addItem(" ");
    ui->listaLIbros->addItem(" ");
    ui->listaLIbros->update();
}

void MainWindow::hacer_resumen()
{
    for(size_t i = 0; i < trabajos.size(); i++)
    {
        for(size_t j = 0; j < resumen.size(); j++)
       {
           foreach(auto &dato, trabajos[i]->palabras_con_contadores)
           {
              if(QString::compare(dato.palabra,resumen[j].palabra) == 0)
                  resumen[j].contador += dato.contador;
           }
       }
    }
    ui->listWidget->addItem("Numero de Archivos: " +
                            QString::number(trabajos.size()));
    for(size_t i = 0 ; i < resumen.size(); i++)
        ui->listWidget->addItem(resumen[i].palabra + " : " +
    QString::number(static_cast<double>(
     static_cast<double>(resumen[i].contador )/
                    static_cast<double>( trabajos.size()))) + "%");
}

/*void MainWindow::recibir_hilo(int id)
{
   //ui->label->setText("Hilo trabajando : " + QString::number(id));
}*/
