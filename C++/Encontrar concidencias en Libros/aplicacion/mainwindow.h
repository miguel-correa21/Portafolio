#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mihilo.h>
#include <vector>
#include <thread>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    std::vector<miHilo *> trabajos;
    std::vector<std::thread> hilos;
    std::thread::id actual;
    std::vector<conjunto_datos> resumen;
    ~MainWindow();
    int valor_barprogress = 0;
    void empezar();
    void crear_widgets_lista();
    void hacer_resumen();
    void llenar_lista(QListWidget*,std::vector<conjunto_datos>);
    static void correr_hilo(miHilo *);

private slots:
    void on_pushButton_clicked();
    void recibir_datos(miHilo *);
//    void recibir_hilo(int id);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
