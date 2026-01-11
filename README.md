# student-management-system
一个使用C++与QT结合创作的学生数据库管理系统
# 学生管理系统 v2.0

## 项目简介
这是一个基于Qt框架和SQLite数据库的学生信息管理系统，实现了完整的学生信息增删改查功能。

## 技术栈
- **框架**: Qt 5/6
- **数据库**: SQLite
- **界面**: Qt Widgets
- **开发环境**: Microsoft Visual Studio 2022

## 功能特性

### 核心功能
- ✅ 学生信息添加
- ✅ 学生信息删除
- ✅ 学生信息修改
- ✅ 学生信息查询
- ✅ 数据库持久化存储

### 用户界面
- 表格展示学生信息（学号、姓名、班级）
- 操作日志输出区域
- 四个功能按钮：添加、删除、修改、查询
- 中文界面，友好用户体验

## 数据库设计

### 表结构
```sql
CREATE TABLE IF NOT EXISTS students (
    id VARCHAR(20) PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    class_name VARCHAR(50) NOT NULL
);
```

### 数据库配置
- **数据库文件**: `Student_database.db`
- **数据库类型**: SQLite
- **兼容工具**: Navicat Premium 16 GUI

## 项目结构

```
student management system2/
├── studentmanagementsystem2.h     # 头文件（包含StudentInfo结构体）
├── studentmanagementsystem2.cpp   # 主实现文件
├── studentmanagementsystem2.ui    # 界面设计文件
├── Student_database.db            # SQLite数据库文件
├── main.cpp                       # 程序入口
└── README.md                      # 项目文档
```

## 代码架构

### 主要类结构
```cpp
class studentmanagementsystem2 : public QMainWindow {
    // 构造函数和析构函数
    studentmanagementsystem2(QWidget *parent = nullptr);
    ~studentmanagementsystem2();
    
    // 槽函数
    void btnAdd();
    void btnDelete();
    void btnEdit();
    void btnSearch();
    
    // 辅助函数
    bool connectToDatabase();
    void createTableIfNotExists();
    void loadStudentsFromDatabase();
    StudentInfo getStudentInfoFromDialog(const QString& title);
    bool isStudentIdExists(const QString& studentId);
    bool insertStudent(const StudentInfo& student);
    void searchStudents(const QString& keyword);
    void addStudentToTable(const QString& id, const QString& name, const QString& className);
};
```

### 数据结构
```cpp
struct StudentInfo {
    QString id;
    QString name;
    QString className;
    bool isValid = false;
};
```

## 功能实现细节

### 1. 数据库连接
- 自动检测并连接SQLite数据库
- 数据库文件不存在时自动创建
- 连接失败时显示错误信息

### 2. 数据验证
- 学号唯一性检查
- 输入字段非空验证
- 操作确认对话框

### 3. 查询功能
- 支持按学号和姓名模糊查询
- 实时显示查询结果数量
- 查询失败时显示错误信息

### 4. 错误处理
- 数据库操作异常捕获
- 用户友好的错误提示
- 操作日志记录

## 编译和运行

### 环境要求
- Qt 5.15+ 或 Qt 6.x
- Microsoft Visual Studio 2022
- SQLite驱动支持

### 编译步骤
1. 打开 `student management system2.sln`
2. 配置Qt环境变量
3. 编译项目
4. 运行程序

## 使用说明

### 添加学生
1. 点击"添加"按钮
2. 输入学号、姓名、班级信息
3. 确认添加

### 删除学生
1. 在表格中选择要删除的学生
2. 点击"删除"按钮
3. 确认删除操作

### 修改学生
1. 在表格中选择要修改的学生
2. 点击"修改"按钮
3. 输入新的学生信息
4. 确认修改

### 查询学生
1. 点击"查询"按钮
2. 输入学号或姓名关键字
3. 查看查询结果

## 技术亮点

### 代码优化
- 模块化设计，功能分离
- 使用结构体封装数据
- 参数化查询防止SQL注入
- 错误处理机制完善

### 用户体验
- 中文界面，操作直观
- 实时反馈操作结果
- 数据验证和确认机制
- 友好的错误提示

## 注意事项

1. 数据库文件 `Student_database.db` 会与程序在同一目录下创建
2. 建议使用Navicat Premium 16进行数据库管理
3. 程序启动时会自动加载已有学生数据
4. 所有操作都会实时更新数据库和界面显示

## 版本历史

- **v2.0**: 优化代码结构，增加辅助函数，提高可维护性
- **v1.0**: 基础功能实现，支持增删改查操作

## 开发者信息

- 开发环境: Microsoft Visual Studio 2022
- 框架: Qt
- 数据库: SQLite
- 界面: Qt Widgets

---

*最后更新: 2026年1月11日*
