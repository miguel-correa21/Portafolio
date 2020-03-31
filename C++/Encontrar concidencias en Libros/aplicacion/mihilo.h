#ifndef MIHILO_H
#define MIHILO_H
#include <QThread>
#include <QtCore>
#include <QListWidget>
#include <vector>
#include <mutex>
#include <QTextStream>

struct conjunto_datos
{
    QString palabra;
    int contador;
};

class miHilo : public QObject
{
    Q_OBJECT
public:
    miHilo(QString);
    std::vector<conjunto_datos> palabras_con_contadores;
    QString get_nombre_libro() {return this->nombre_libro;}
    unsigned int id_hilo;
    std::mutex mtx;
    void run();
    const std::vector<QString> palabras
    {
        "regalos", "besos", "cachondeo","delicioso","compañía",
        "confianza","comunicación","pasión","apoyo"
    };

private:
    void buscar_en_linea(QStringList linea);
    void buscar_palabra(QString palabra);
    QFile libro;
    QString nombre_libro;

signals:
    void enviar_datos(miHilo *);
//    void enviar_trabajo(int id);

};

#endif // MIHILO_H
