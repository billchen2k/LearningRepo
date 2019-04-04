/********************************************************************************
** Form generated from reading UI file 'NQueens_QT.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NQUEENS_QT_H
#define UI_NQUEENS_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NQueens_QTClass
{
public:
    QWidget *centralWidget;
    QPushButton *HelloQT;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NQueens_QTClass)
    {
        if (NQueens_QTClass->objectName().isEmpty())
            NQueens_QTClass->setObjectName(QString::fromUtf8("NQueens_QTClass"));
        NQueens_QTClass->resize(626, 548);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        NQueens_QTClass->setFont(font);
        centralWidget = new QWidget(NQueens_QTClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        HelloQT = new QPushButton(centralWidget);
        HelloQT->setObjectName(QString::fromUtf8("HelloQT"));
        HelloQT->setGeometry(QRect(170, 220, 321, 81));
        NQueens_QTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NQueens_QTClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 626, 22));
        NQueens_QTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(NQueens_QTClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        NQueens_QTClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(NQueens_QTClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        NQueens_QTClass->setStatusBar(statusBar);

        retranslateUi(NQueens_QTClass);
        QObject::connect(HelloQT, SIGNAL(clicked()), HelloQT, SLOT(click()));

        QMetaObject::connectSlotsByName(NQueens_QTClass);
    } // setupUi

    void retranslateUi(QMainWindow *NQueens_QTClass)
    {
        NQueens_QTClass->setWindowTitle(QApplication::translate("NQueens_QTClass", "NQueens_QT", nullptr));
        HelloQT->setText(QApplication::translate("NQueens_QTClass", "HelloQT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NQueens_QTClass: public Ui_NQueens_QTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NQUEENS_QT_H
