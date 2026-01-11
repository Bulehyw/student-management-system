#pragma once

#include <QtWidgets/QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "ui_studentmanagementsystem2.h"

class studentmanagementsystem2 : public QMainWindow
{
    Q_OBJECT

public:
    struct StudentInfo {
        QString id;
        QString name;
        QString className;
        bool isValid = false;
        
        StudentInfo() : isValid(false) {}
    };

    studentmanagementsystem2(QWidget *parent = nullptr);
    ~studentmanagementsystem2();

private:
    Ui::studentmanagementsystem2Class ui;
    QSqlDatabase db;
    
    // 数据库相关方法
    bool connectToDatabase();
    void createTableIfNotExists();
    void loadStudentsFromDatabase();
    
    // 辅助函数
    StudentInfo getStudentInfoFromDialog(const QString& title);
    bool isStudentIdExists(const QString& studentId);
    bool insertStudent(const StudentInfo& student);
    void searchStudents(const QString& keyword);
    void addStudentToTable(const QString& id, const QString& name, const QString& className);

private slots:
    void btnAdd(); //增加
    void btnDelete();//删除
    void btnEdit(); //修改
    void btnSearch(); //查询

};

