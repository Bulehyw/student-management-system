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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_studentmanagementsystem2Class
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnEdit;
    QPushButton *btnSearch;
    QTableWidget *tableStudents;
    QTextEdit *txtInfo;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *studentmanagementsystem)
    {
        if (studentmanagementsystem->objectName().isEmpty())
            studentmanagementsystem->setObjectName("studentmanagementsystem");
        studentmanagementsystem->resize(600, 500);
        centralwidget = new QWidget(studentmanagementsystem);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        btnAdd = new QPushButton(groupBox);
        btnAdd->setObjectName("btnAdd");

        horizontalLayout->addWidget(btnAdd);

        btnDelete = new QPushButton(groupBox);
        btnDelete->setObjectName("btnDelete");

        horizontalLayout->addWidget(btnDelete);

        btnEdit = new QPushButton(groupBox);
        btnEdit->setObjectName("btnEdit");

        horizontalLayout->addWidget(btnEdit);

        btnSearch = new QPushButton(groupBox);
        btnSearch->setObjectName("btnSearch");

        horizontalLayout->addWidget(btnSearch);


        verticalLayout->addWidget(groupBox);

        tableStudents = new QTableWidget(centralwidget);
        if (tableStudents->columnCount() < 3)
            tableStudents->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableStudents->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableStudents->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableStudents->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableStudents->setObjectName("tableStudents");

        verticalLayout->addWidget(tableStudents);

        txtInfo = new QTextEdit(centralwidget);
        txtInfo->setObjectName("txtInfo");
        txtInfo->setReadOnly(true);

        verticalLayout->addWidget(txtInfo);

        studentmanagementsystem->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(studentmanagementsystem);
        statusbar->setObjectName("statusbar");
        studentmanagementsystem->setStatusBar(statusbar);

        retranslateUi(studentmanagementsystem);

        QMetaObject::connectSlotsByName(studentmanagementsystem);
    } // setupUi

    void retranslateUi(QMainWindow *studentmanagementsystem)
    {
        studentmanagementsystem->setWindowTitle(QCoreApplication::translate("studentmanagementsystem2Class", "\345\255\246\347\224\237\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        groupBox->setTitle(QCoreApplication::translate("studentmanagementsystem2Class", "\345\255\246\347\224\237\347\256\241\347\220\206", nullptr));
        btnAdd->setText(QCoreApplication::translate("studentmanagementsystem2Class", "\346\267\273\345\212\240\345\255\246\347\224\237", nullptr));
        btnDelete->setText(QCoreApplication::translate("studentmanagementsystem2Class", "\345\210\240\351\231\244\345\255\246\347\224\237", nullptr));
        btnEdit->setText(QCoreApplication::translate("studentmanagementsystem2Class", "\344\277\256\346\224\271\344\277\241\346\201\257", nullptr));
        btnSearch->setText(QCoreApplication::translate("studentmanagementsystem2Class", "\346\237\245\350\257\242\345\255\246\347\224\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableStudents->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("studentmanagementsystem2Class", "\345\255\246\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableStudents->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("studentmanagementsystem2Class", "\345\247\223\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableStudents->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("studentmanagementsystem2Class", "\347\217\255\347\272\247", nullptr));
        txtInfo->setPlaceholderText(QCoreApplication::translate("studentmanagementsystem2Class", "\347\263\273\347\273\237\344\277\241\346\201\257\345\260\206\346\230\276\347\244\272\345\234\250\350\277\231\351\207\214...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class studentmanagementsystem2Class: public Ui_studentmanagementsystem2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTMANAGEMENTSYSTEM2_H
