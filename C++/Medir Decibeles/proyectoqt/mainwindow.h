#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_UNO = 66;
    static const quint16 arduino_MEGA = 67;
    QString arduino_puerto;
    bool arduino_esta_disponible;
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    void ConectarArduino();
};

#endif // MAINWINDOW_H
