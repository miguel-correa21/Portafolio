#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <typeinfo>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConectarArduino();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int valores[8] = {1,2,4,8,16,32,64,128};
    int decimal;

    if(arduino_esta_disponible && arduino->isReadable())
    {
        decimal = 0;
        QByteArray pines = arduino->readAll();
        std::string binario = pines.toStdString();
        for(int i = 0,j = 7; i < 8;i++,j--)
        {
            if((binario[i]) =='1')
                decimal += valores[j];
        }
        ui->lcdNumber->display(decimal);
    }

}

void MainWindow::ConectarArduino()
{
    arduino_esta_disponible = false;
    QString arduino_puerto = "";
    arduino = new QSerialPort;
    QString nombreDispositivoSerial = "";
    int nombreProductID = 0;

    foreach (const QSerialPortInfo &serialPortInfo,
             QSerialPortInfo::availablePorts())
    {
        if(serialPortInfo.hasVendorIdentifier())
        {
             if(serialPortInfo.productIdentifier() == arduino_UNO ||
                     serialPortInfo.productIdentifier() == arduino_MEGA)
             {
                 arduino_esta_disponible = true;
                 nombreDispositivoSerial = serialPortInfo.portName();
                 nombreProductID = serialPortInfo.productIdentifier();
             }
         }
    }

    if(arduino_esta_disponible)
    {
        arduino_puerto = nombreDispositivoSerial;
        arduino ->setPortName(arduino_puerto);
        arduino->open(QIODevice::ReadWrite);
        arduino->setDataBits(QSerialPort::Data8);
        arduino ->setBaudRate(QSerialPort::Baud115200);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }

}
