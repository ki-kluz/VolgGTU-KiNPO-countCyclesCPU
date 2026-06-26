@echo off
REM Устанавливаем рабочую папку
cd /d "%~dp0"

chcp 65001 >nul
setlocal enabledelayedexpansion

set EXE=..\build\Desktop_Debug\debug\countCyclesCPU.exe

set TEMP_OUT=temp_output.txt
set SORTED_OUT=sorted_out.txt
set SORTED_EXP=sorted_exp.txt
set PASSED=0
set TOTAL=0

echo Запуск тестов...

REM Итерируемся по всем папкам
for /d %%D in (test_*) do (
    set "TEST_DIR=%%D"
    set "NUM=!TEST_DIR:test_=!"

    if exist "!TEST_DIR!\expected.txt" (
        set /a TOTAL+=1

        REM Формируем аргументы динамически
        if "!NUM!"=="01" (
            "!EXE!" > "console.txt" 2>&1
        ) else if "!NUM!"=="02" (
            "!EXE!" "!TEST_DIR!\input.txt" > "console.txt" 2>&1
        ) else if "!NUM!"=="03" (
            "!EXE!" "!TEST_DIR!\input.txt" "out.txt" > "console.txt" 2>&1
        ) else if "!NUM!"=="04" (
            "!EXE!" "!TEST_DIR!\input.txt" "!TEST_DIR!\weight.txt" "out.txt" > "console.txt" 2>&1
        ) else if "!NUM!"=="05" (
            "!EXE!" "!TEST_DIR!\input.txt" "" > "console.txt" 2>&1
        ) else if "!NUM!"=="06" (
            "!EXE!" "!TEST_DIR!\input.txt" "invalid_dir\output.txt" > "console.txt" 2>&1
        ) else (
            REM Стандартный запуск
            if exist "!TEST_DIR!\weight.txt" (
                "!EXE!" "!TEST_DIR!\input.txt" "!TEST_DIR!\weight.txt" "out.txt" > "console.txt" 2>&1
            ) else (
                "!EXE!" "!TEST_DIR!\input.txt" "out.txt" > "console.txt" 2>&1
            )
        )

        REM Сливаем результаты
        type nul > "!TEMP_OUT!"
        if exist "out.txt" (
            type "out.txt" >> "!TEMP_OUT!"
            del "out.txt"
        )
        if exist "console.txt" (
            type "console.txt" >> "!TEMP_OUT!"
            del "console.txt"
        )

        REM Сортируем фактический вывод и эталон
        sort "!TEMP_OUT!" /O "!SORTED_OUT!"
        sort "!TEST_DIR!\expected.txt" /O "!SORTED_EXP!"

        REM Сравниваем отсортированные файлы
        fc /W "!SORTED_OUT!" "!SORTED_EXP!" >nul 2>&1
        
        if !errorlevel! equ 0 (
            echo [ OK ] Тест !NUM! пройден.
            set /a PASSED+=1
        ) else (
            echo [FAIL] Тест !NUM! провален.
            echo --- Разница ---
            fc /W "!SORTED_OUT!" "!SORTED_EXP!"
            echo ------------------------------------------------
        )
    )
)

REM Убираем временные файлы
if exist "!TEMP_OUT!" del "!TEMP_OUT!"
if exist "!SORTED_OUT!" del "!SORTED_OUT!"
if exist "!SORTED_EXP!" del "!SORTED_EXP!"
if exist "out.txt" del "out.txt"
if exist "console.txt" del "console.txt"

REM Финальная статистика
echo ==================================
echo Всего тестов запущено: !TOTAL!
echo Успешно пройдено: !PASSED! / !TOTAL!
echo ==================================
pause