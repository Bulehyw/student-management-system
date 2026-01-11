#include "studentmanagementsystem2.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QTableWidgetItem>
#include <QDebug>
#include <QSqlError>

studentmanagementsystem2::studentmanagementsystem2(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    // 连接按钮信号到槽函数
    connect(ui.btnAdd, &QPushButton::clicked, this, &studentmanagementsystem2::btnAdd);
    connect(ui.btnDelete, &QPushButton::clicked, this, &studentmanagementsystem2::btnDelete);
    connect(ui.btnEdit, &QPushButton::clicked, this, &studentmanagementsystem2::btnEdit);
    connect(ui.btnSearch, &QPushButton::clicked, this, &studentmanagementsystem2::btnSearch);
    
    // 初始化表格
    ui.tableStudents->setRowCount(0);
    ui.tableStudents->setColumnCount(3);
    ui.tableStudents->setHorizontalHeaderLabels(QStringList() << "学号" << "姓名" << "班级");
    
    // 连接数据库
    if (connectToDatabase()) {
        createTableIfNotExists();
        loadStudentsFromDatabase();
        ui.txtInfo->append("数据库连接成功！");
    } else {
        ui.txtInfo->append("数据库连接失败！");
    }
}

studentmanagementsystem2::~studentmanagementsystem2()
{
    if (db.isOpen()) {
        db.close();
    }
}

// 连接数据库
bool studentmanagementsystem2::connectToDatabase()
{
    // 使用SQLite数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Student_database.db");
    
    if (db.open()) {
        ui.txtInfo->append("SQLite数据库连接成功！数据库文件：Student_database.db");
        return true;
    } else {
        QString errorMsg = QString();
        
        QMessageBox::critical(this, "数据库连接错误", errorMsg);
        return false;
    }
}

// 创建学生表（如果不存在）
void studentmanagementsystem2::createTableIfNotExists()
{
    QSqlQuery query;
    QString sql = "CREATE TABLE IF NOT EXISTS students ("
                  "id VARCHAR(20) PRIMARY KEY, "
                  "name VARCHAR(50) NOT NULL, "
                  "class_name VARCHAR(50) NOT NULL"
                  ")";
    
    if (!query.exec(sql)) {
        QMessageBox::critical(this, "创建表错误", query.lastError().text());
    }
}

// 从数据库加载学生数据
void studentmanagementsystem2::loadStudentsFromDatabase()
{
    ui.tableStudents->setRowCount(0);
    
    QSqlQuery query("SELECT id, name, class_name FROM students ORDER BY id");
    
    while (query.next()) {
        addStudentToTable(query.value(0).toString(), 
                         query.value(1).toString(), 
                         query.value(2).toString());
    }
}

// 添加学生
void studentmanagementsystem2::btnAdd()
{
    // 获取学生信息
    StudentInfo student = getStudentInfoFromDialog("添加学生");
    if (!student.isValid) return;
    
    // 检查学号是否已存在
    if (isStudentIdExists(student.id)) {
        QMessageBox::warning(this, "错误", "学号已存在！");
        return;
    }
    
    // 插入新学生
    if (insertStudent(student)) {
        loadStudentsFromDatabase();
        ui.txtInfo->append(QString("添加学生成功：学号=%1, 姓名=%2, 班级=%3")
                          .arg(student.id, student.name, student.className));
    }
}

// 删除学生
void studentmanagementsystem2::btnDelete()
{
    int currentRow = ui.tableStudents->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "错误", "请先选择要删除的学生！");
        return;
    }
    QString id = ui.tableStudents->item(currentRow, 0)->text();
    QString name = ui.tableStudents->item(currentRow, 1)->text();
    
    int ret = QMessageBox::question(this, "确认删除", 
                                   QString("确定要删除学生[%1 - %2]吗？").arg(id, name),
                                   QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM students WHERE id = ?");
        query.addBindValue(id);
        
        if (query.exec()) {
            loadStudentsFromDatabase();
            ui.txtInfo->append(QString("删除学生成功：学号=%1").arg(id));
        } else {
            QMessageBox::critical(this, "删除失败", query.lastError().text());
        }
    }
}

// 修改学生信息
void studentmanagementsystem2::btnEdit()
{
    int currentRow = ui.tableStudents->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "错误", "请先选择要修改的学生！");
        return;
    }
    
    QString oldId = ui.tableStudents->item(currentRow, 0)->text();
    QString oldName = ui.tableStudents->item(currentRow, 1)->text();
    QString oldClass = ui.tableStudents->item(currentRow, 2)->text();
    
    bool ok;
    QString newId = QInputDialog::getText(this, "修改学生信息", "请输入新学号：", QLineEdit::Normal, oldId, &ok);
    if (!ok || newId.isEmpty()) return;
    
    QString newName = QInputDialog::getText(this, "修改学生信息", "请输入新姓名：", QLineEdit::Normal, oldName, &ok);
    if (!ok || newName.isEmpty()) return;
    
    QString newClass = QInputDialog::getText(this, "修改学生信息", "请输入新班级：", QLineEdit::Normal, oldClass, &ok);
    if (!ok || newClass.isEmpty()) return;
    
    // 更新学生信息
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE students SET id = ?, name = ?, class_name = ? WHERE id = ?");
    updateQuery.addBindValue(newId);
    updateQuery.addBindValue(newName);
    updateQuery.addBindValue(newClass);
    updateQuery.addBindValue(oldId);
    
    if (updateQuery.exec()) {
        loadStudentsFromDatabase();
        ui.txtInfo->append("修改学生信息成功：原学号=" + oldId + ", 新学号=" + newId);
    } else {
        QMessageBox::critical(this, "修改失败", updateQuery.lastError().text());
    }
}

// 查询学生
void studentmanagementsystem2::btnSearch()
{
    bool ok;
    QString keyword = QInputDialog::getText(this, "查询学生", "请输入学号或姓名：", QLineEdit::Normal, "", &ok);
    if (!ok || keyword.isEmpty()) return;
    
    searchStudents(keyword);
}

// 辅助函数：从对话框获取学生信息
studentmanagementsystem2::StudentInfo studentmanagementsystem2::getStudentInfoFromDialog(const QString& title)
{
    StudentInfo student;
    bool ok;
    
    student.id = QInputDialog::getText(this, title, "请输入学号：", QLineEdit::Normal, "", &ok);
    if (!ok || student.id.isEmpty()) return student;
    
    student.name = QInputDialog::getText(this, title, "请输入姓名：", QLineEdit::Normal, "", &ok);
    if (!ok || student.name.isEmpty()) return student;
    
    student.className = QInputDialog::getText(this, title, "请输入班级：", QLineEdit::Normal, "", &ok);
    if (!ok || student.className.isEmpty()) return student;
    
    student.isValid = true;
    return student;
}

// 辅助函数：检查学号是否存在
bool studentmanagementsystem2::isStudentIdExists(const QString& studentId)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM students WHERE id = ?");
    query.addBindValue(studentId);
    
    return query.exec() && query.next();
}

// 辅助函数：插入学生
bool studentmanagementsystem2::insertStudent(const StudentInfo& student)
{
    QSqlQuery query;
    query.prepare("INSERT INTO students (id, name, class_name) VALUES (?, ?, ?)");
    query.addBindValue(student.id);
    query.addBindValue(student.name);
    query.addBindValue(student.className);
    
    if (query.exec()) {
        return true;
    } else {
        QMessageBox::critical(this, "添加失败", query.lastError().text());
        return false;
    }
}

// 辅助函数：查询学生
void studentmanagementsystem2::searchStudents(const QString& keyword)
{
    ui.tableStudents->setRowCount(0);
    
    QSqlQuery query;
    query.prepare("SELECT id, name, class_name FROM students WHERE id LIKE ? OR name LIKE ?");
    query.addBindValue("%" + keyword + "%");
    
    if (query.exec()) {
        int count = 0;
        while (query.next()) {
            addStudentToTable(query.value(0).toString(), 
                             query.value(1).toString(), 
                             query.value(2).toString());
            count++;
        }
        
        if (count == 0) {
            ui.txtInfo->append("查询结果：未找到匹配的学生");
        } else {
            ui.txtInfo->append(QString("查询结果：找到 %1 个匹配的学生").arg(count));
        }
    } else {
        QMessageBox::critical(this, "查询失败", query.lastError().text());
    }
}

// 辅助函数：添加学生到表格
void studentmanagementsystem2::addStudentToTable(const QString& id, const QString& name, const QString& className)
{
    int row = ui.tableStudents->rowCount();
    ui.tableStudents->insertRow(row);
    
    ui.tableStudents->setItem(row, 0, new QTableWidgetItem(id));
    ui.tableStudents->setItem(row, 1, new QTableWidgetItem(name));
    ui.tableStudents->setItem(row, 2, new QTableWidgetItem(className));
}

