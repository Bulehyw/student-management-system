@echo off
echo ============================================
echo  最终编译 MySQL 驱动（无空格路径）
echo ============================================

REM 设置环境
set PATH=G:\QT\Tools\mingw1120_64\bin;G:\QT\6.5.3\mingw_64\bin;%PATH%

set QT_DIR=G:\QT\6.5.3
set MYSQL_INC=G:\uiii\include
set MYSQL_LIB=G:\uiii\lib\libmysql.lib

echo 检查文件...
if not exist "%MYSQL_INC%\mysql.h" (
    echo [错误] 找不到 mysql.h
    echo 请确认路径：%MYSQL_INC%
    pause
    exit /b 1
)

if not exist "%MYSQL_LIB%" (
    echo [错误] 找不到 libmysql.lib
    echo 请确认路径：%MYSQL_LIB%
    pause
    exit /b 1
)

echo ✓ MySQL 开发文件存在
echo.

REM 进入驱动目录
cd /d %QT_DIR%\Src\qtbase\src\plugins\sqldrivers
echo 当前目录：%cd%

REM 清理
echo 清理旧文件...
rd /s /q build 2>nul
mkdir build
cd build

REM 配置 CMake
echo 配置 CMake...
echo MySQL 包含路径：%MYSQL_INC%
echo MySQL 库文件：%MYSQL_LIB%
echo.

cmake .. -G "MinGW Makefiles" ^
  -DCMAKE_PREFIX_PATH="%QT_DIR%/mingw_64" ^
  -DMySQL_INCLUDE_DIR="%MYSQL_INC%" ^
  -DMySQL_LIBRARY="%MYSQL_LIB%" ^
  -DFEATURE_sql_mysql=ON

if errorlevel 1 (
    echo [错误] CMake 配置失败！
    pause
    exit /b 1
)

echo ✓ CMake 配置成功
echo.

REM 编译
echo 开始编译...
mingw32-make -j4

if errorlevel 1 (
    echo [错误] 编译失败！
    echo 尝试详细编译...
    mingw32-make VERBOSE=1
    if errorlevel 1 (
        pause
        exit /b 1
    )
)

echo ✓ 编译成功
echo.

REM 查找生成的 DLL
echo 查找生成的驱动文件...
set DRIVER_FOUND=
for /r . %%f in (*qsqlmysql*.dll) do (
    echo 找到：%%~f
    set DRIVER_FOUND=%%~f
)

if "%DRIVER_FOUND%"=="" (
    echo [警告] 未找到 qsqlmysql.dll
    echo 尝试查找其他 DLL...
    dir /s /b *.dll
    pause
    exit /b 1
)

REM 复制驱动到插件目录
echo 复制驱动到插件目录...
copy "%DRIVER_FOUND%" "%QT_DIR%\mingw_64\plugins\sqldrivers\" >nul

REM 复制 MySQL 运行时库
if exist "G:\uiii\lib\libmysql.dll" (
    copy "G:\uiii\lib\libmysql.dll" "%QT_DIR%\mingw_64\bin\" >nul
    echo 已复制 libmysql.dll 到 Qt bin 目录
)

echo.
echo ============================================
echo [成功] MySQL 驱动编译完成！
echo.
echo 驱动文件：%QT_DIR%\mingw_64\plugins\sqldrivers\qsqlmysql.dll
echo.
echo 验证：
dir "%QT_DIR%\mingw_64\plugins\sqldrivers\qsqlmysql.dll"
echo.
echo 使用示例：
echo  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
echo  db.setHostName("localhost");
echo  db.setDatabaseName("testdb");
echo  db.setUserName("root");
echo  db.setPassword("password");
echo ============================================
pause