#!/bin/bash

EXE="../build/Qt_6_9_3_for_macOS-Debug/countCyclesCPU" # На macOS у бинарников обычно нет расширения .exe
TEMP_OUT="temp_output.txt"
PASSED=0 # В оригинальном скрипте переменная создана, но не инкрементируется, сохраняю как есть
TOTAL=0

for i in {1..50}; do
    # Форматируем число с ведущим нулем (01, 02... 50)
    printf -v NUM "%02d" $i
    TEST_DIR="test_${NUM}"

    if [ -f "${TEST_DIR}/expected.txt" ]; then
        ((TOTAL++))

        # Формируем аргументы динамически
        # Тесты проверки работы с файлами [01-06] запускаются со спец. арг. (!)
        if [ "$i" -eq 1 ]; then
            # Тест 01: Запуск без аргументов
            "$EXE" > "$TEMP_OUT" 2>&1
        elif [ "$i" -eq 2 ]; then
            # Тест 02: Запуск без выходного файла (с одним аргументом)
            "$EXE" "${TEST_DIR}/input.txt" > "$TEMP_OUT" 2>&1
        elif [ "$i" -eq 3 ]; then
            # Тест 03: Входной файл не существует (но указан)
            "$EXE" "${TEST_DIR}/input.txt" "$TEMP_OUT" > "$TEMP_OUT" 2>&1
        elif [ "$i" -eq 4 ]; then
            # Тест 04: Файл весов не существует (но указан)
            "$EXE" "${TEST_DIR}/input.txt" "${TEST_DIR}/weight.txt" "$TEMP_OUT" > "$TEMP_OUT" 2>&1
        elif [ "$i" -eq 5 ]; then
            # Тест 05: Выходной файл не указан (передаем пустую строку)
            "$EXE" "${TEST_DIR}/input.txt" "" > "$TEMP_OUT" 2>&1
        elif [ "$i" -eq 6 ]; then
            # Тест 06: Невозможно создать выходной файл (несуществующая папка)
            "$EXE" "${TEST_DIR}/input.txt" "invalid_dir/output.txt" > "$TEMP_OUT" 2>&1
        else
            # Стандартный запуск для всех остальных тестов
            if [ -f "${TEST_DIR}/weight.txt" ]; then
                "$EXE" "${TEST_DIR}/input.txt" "${TEST_DIR}/weight.txt" "$TEMP_OUT" > "$TEMP_OUT" 2>&1
            else
                "$EXE" "${TEST_DIR}/input.txt" "$TEMP_OUT" > "$TEMP_OUT" 2>&1
            fi
        fi

        # Сравниваем временный файл с эталоном (ВРЕМЕННО)
        if diff -w "$TEMP_OUT" "${TEST_DIR}/expected.txt" > /dev/null 2>&1; then
            echo "[ OK ] Тест ${NUM} пройден."
        else
            echo "[FAIL] Тест ${NUM} провален."
            # Выводим РЕАЛЬНУЮ разницу, чтобы ты видел, в чем проблема
            echo "--- Разница (Фактический вывод vs Ожидаемый) ---"
            diff "$TEMP_OUT" "${TEST_DIR}/expected.txt"
            echo "------------------------------------------------"
        fi
    fi
done
