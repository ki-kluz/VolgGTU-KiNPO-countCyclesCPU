#!/bin/bash

EXE="../build/Qt_6_9_3_for_macOS-Debug/countCyclesCPU" # На macOS у бинарников обычно нет расширения .exe
TEMP_OUT="temp_output.txt"
PASSED=0
TOTAL=0

# Итерируемся по всем папкам, имя которых начинается с test_
for TEST_DIR in test_*; do
    # Проверяем, что это действительно существующая директория
    [ -d "$TEST_DIR" ] || continue
    
    # Извлекаем номер теста из имени папки (отрезаем "test_")
    NUM="${TEST_DIR#test_}"

    if [ -f "${TEST_DIR}/expected.txt" ]; then
        ((TOTAL++))

        # Формируем аргументы динамически на основе НОМЕРА папки
        if [ "$NUM" = "01" ]; then
            # Тест 01: Запуск без аргументов
            "$EXE" > "$TEMP_OUT" 2>&1
        elif [ "$NUM" = "02" ]; then
            # Тест 02: Запуск без выходного файла (с одним аргументом)
            "$EXE" "${TEST_DIR}/input.txt" > "$TEMP_OUT" 2>&1
        elif [ "$NUM" = "03" ]; then
            # Тест 03: Входной файл не существует (но указан)
            "$EXE" "${TEST_DIR}/input.txt" "$TEMP_OUT" > "$TEMP_OUT" 2>&1
        elif [ "$NUM" = "04" ]; then
            # Тест 04: Файл весов не существует (но указан)
            "$EXE" "${TEST_DIR}/input.txt" "${TEST_DIR}/weight.txt" "$TEMP_OUT" > "$TEMP_OUT" 2>&1
        elif [ "$NUM" = "05" ]; then
            # Тест 05: Выходной файл не указан (передаем пустую строку)
            "$EXE" "${TEST_DIR}/input.txt" "" > "$TEMP_OUT" 2>&1
        elif [ "$NUM" = "06" ]; then
            # Тест 06: Невозможно создать выходной файл (несуществующая папка)
            "$EXE" "${TEST_DIR}/input.txt" "invalid_dir/output.txt" > "$TEMP_OUT" 2>&1
        else
            # Стандартный запуск для всех остальных тестов (с 07 и далее)
            if [ -f "${TEST_DIR}/weight.txt" ]; then
                "$EXE" "${TEST_DIR}/input.txt" "${TEST_DIR}/weight.txt" "$TEMP_OUT" > "$TEMP_OUT" 2>&1
            else
                "$EXE" "${TEST_DIR}/input.txt" "$TEMP_OUT" > "$TEMP_OUT" 2>&1
            fi
        fi
        
        # Сравниваем временный файл с эталоном
        # (*) предварительно сортируем строки по алфавиту
        if diff -w <(sort "$TEMP_OUT") <(sort "${TEST_DIR}/expected.txt") > /dev/null 2>&1; then
            echo "[ OK ] Тест ${NUM} пройден."
            ((PASSED++)) # Добавил инкремент, раз уж переменная объявлена
        else
            echo "[FAIL] Тест ${NUM} провален."
            # Выводим РЕАЛЬНУЮ разницу отсортированных версий
            echo "--- Разница (Фактический вывод vs Ожидаемый) ---"
            diff -w <(sort "$TEMP_OUT") <(sort "${TEST_DIR}/expected.txt")
            echo "------------------------------------------------"
        fi
    fi
done

# Финальная статистика
echo "=================================="
echo "Всего тестов запущено: $TOTAL"
echo "Успешно пройдено: $PASSED / $TOTAL"
echo "=================================="
