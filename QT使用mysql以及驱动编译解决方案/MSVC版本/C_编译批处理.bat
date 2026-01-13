@echo off
echo ============================================
echo  为VS2022（MSVC2019）编译MySQL驱动
echo ============================================

REM 设置变量 - 根据你的实际情况修改！
set QT_DIR=G:\QT\6.5.3
set MYSQL_DEV=D:\MySQLDev  REM 改为你的MySQL开发文件路径
set BUILD_CONFIG=Release   REM 可选：Debug或Release

echo QT路径: %QT_DIR%
echo MySQL开发路径: %MYSQL_DEV%
echo.

REM 1. 进入驱动源码目录
cd /d %QT_DIR%\Src\qtbase\src\plugins\sqldrivers

if errorlevel 1 (
    echo [错误] QT源码目录不存在！
    echo 请确认QT已安装源码或路径正确
    pause
    exit /b 1
)

REM 2. 清理并创建build目录
echo 清理旧构建...
rd /s /q build 2>nul
mkdir build
cd build

REM 3. 配置CMake（使用Visual Studio生成器）
echo 配置CMake...
echo 使用编译器：MSVC 2019 (VS2022)
echo.

cmake .. ^
  -G "Visual Studio 17 2022" ^
  -A x64 ^
  -DCMAKE_PREFIX_PATH="%QT_DIR%/msvc2019_64" ^
  -DMySQL_INCLUDE_DIR="%MYSQL_DEV%/include" ^
  -DMySQL_LIBRARY="%MYSQL_DEV%/lib/libmysql.lib"

if errorlevel 1 (
    echo [错误] CMake配置失败！
    echo 常见原因：
    echo 1. CMake找不到VS2022
    echo 2. MySQL路径不正确
    echo 3. 缺少必要文件
    pause
    exit /b 1
)

echo ✓ CMake配置成功
echo.

REM 4. 编译指定版本
echo 编译%BUILD_CONFIG%版本...
cmake --build . --config %BUILD_CONFIG%

if errorlevel 1 (
    echo [错误] 编译失败！
    echo.
    echo 尝试以下解决方案：
    echo 1. 检查MySQL库是否匹配（32位/64位）
    echo 2. 尝试Debug版本：set BUILD_CONFIG=Debug
    echo 3. 确保VS2022已安装C++桌面开发组件
    pause
    exit /b 1
)

echo ✓ 编译成功！
echo.

REM 5. 查找生成的驱动文件
echo 生成的驱动文件：
dir /s /b *qsqlmysql*.dll

REM 6. 复制驱动到QT插件目录
set QT_PLUGIN_DIR=%QT_DIR%\msvc2019_64\plugins\sqldrivers
if not exist "%QT_PLUGIN_DIR%" mkdir "%QT_PLUGIN_DIR%"

for /r . %%f in (*qsqlmysql*.dll) do (
    echo 复制: %%~nxf
    copy "%%f" "%QT_PLUGIN_DIR%\" >nul
)

REM 7. 复制MySQL运行时库（重要！）
if exist "%MYSQL_DEV%\bin\libmysql.dll" (
    copy "%MYSQL_DEV%\bin\libmysql.dll" "%QT_DIR%\msvc2019_64\bin\" >nul
    echo 已复制 libmysql.dll 到QT的bin目录
)

echo.
echo ============================================
echo [成功] MySQL驱动编译完成！
echo.
echo 驱动位置: %QT_PLUGIN_DIR%\qsqlmysql.dll
echo 运行时库: %QT_DIR%\msvc2019_64\bin\libmysql.dll
echo.
echo 测试连接代码：
echo   QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
echo   db.setHostName("localhost");
echo   db.setPort(3306);
echo   db.setDatabaseName("testdb");
echo   db.setUserName("root");
echo   db.setPassword("your_password");
echo   if(db.open()) { qDebug() ^<^< "连接成功"; }
echo   else { qDebug() ^<^< "错误：" ^<^< db.lastError().text(); }
echo ============================================
pause