/********************************************************************************
** Form generated from reading UI file 'studentmanagementsystem2.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTMANAGEMENTSYSTEM2_H
#define UI_STUDENTMANAGEMENTSYSTEM2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_studentmanagementsystem2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *studentmanagementsystem2Class)
    {
        if (studentmanagementsystem2Class->objectName().isEmpty())
            studentmanagementsystem2Class->setObjectName("studentmanagementsystem2Class");
        studentmanagementsystem2Class->resize(600, 400);
        menuBar = new QMenuBar(studentmanagementsystem2Class);
        menuBar->setObjectName("menuBar");
        studentmanagementsystem2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(studentmanagementsystem2Class);
        mainToolBar->setObjectName("mainToolBar");
        studentmanagementsystem2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(studentmanagementsystem2Class);
        centralWidget->setObjectName("centralWidget");
        studentmanagementsystem2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(studentmanagementsystem2Class);
        statusBar->setObjectName("statusBar");
        studentmanagementsystem2Class->setStatusBar(statusBar);

        retranslateUi(studentmanagementsystem2Class);

        QMetaObject::connectSlotsByName(studentmanagementsystem2Class);
    } // setupUi

    void retranslateUi(QMainWindow *studentmanagementsystem2Class)
    {
        studentmanagementsystem2Class->setWindowTitle(QCoreApplication::translate("studentmanagementsystem2Class", "studentmanagementsystem2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class studentmanagementsystem2Class: public Ui_studentmanagementsystem2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTMANAGEMENTSYSTEM2_H
