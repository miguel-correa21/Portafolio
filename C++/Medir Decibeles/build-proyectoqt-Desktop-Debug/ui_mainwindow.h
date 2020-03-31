/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLCDNumber *lcdNumber;
    QLabel *label;
    QPushButton *pushButton;
    QFrame *Texto;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(741, 526);
        MainWindow->setStyleSheet(QLatin1String("border-color: rgb(0, 170, 255);\n"
"alternate-background-color: rgb(76, 148, 170);\n"
"background-color: rgb(27, 48, 58);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(340, 370, 341, 71));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 370, 171, 71));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 380, 101, 41));
        Texto = new QFrame(centralWidget);
        Texto->setObjectName(QStringLiteral("Texto"));
        Texto->setGeometry(QRect(10, 10, 2, 2));
        Texto->setStyleSheet(QLatin1String("\n"
"font: 0 italic 16pt \"Noto Sans\";"));
        verticalLayout = new QVBoxLayout(Texto);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(300, 10, 151, 51));
        label_2->setStyleSheet(QLatin1String("font: 75 32pt \"Noto Sans\";\n"
"text-decoration: underline;"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(200, 60, 331, 71));
        label_3->setStyleSheet(QStringLiteral("font: 75 28pt \"Noto Sans\";"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(70, 130, 111, 31));
        label_4->setStyleSheet(QStringLiteral("font: 75 18pt \"Noto Sans\";"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(160, 170, 371, 18));
        label_5->setStyleSheet(QStringLiteral("font: 75 18pt \"Noto Sans\";"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(160, 210, 391, 31));
        label_6->setStyleSheet(QStringLiteral("font: 75 18pt \"Noto Sans\";"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(160, 260, 421, 21));
        label_7->setStyleSheet(QStringLiteral("font: 75 18pt \"Noto Sans\";"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 741, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">Decibeles</span></p></body></html>", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Leer", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "ESCOM", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "INSTRUMENTACI\303\223N", nullptr));
        label_4->setText(QApplication::translate("MainWindow", " EQUIPO:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "CORREA MEDINA CARLOS MIGUEL.", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "JUSTO VIZCARRA JAIME ALEGANDRO", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "RAMOS GUERRERO GIBRAN ARMANDO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
