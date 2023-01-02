# Лабораторная работа №1 по курсу "Операционные системы"

Студент группы: M80-207Б-21, Крючков Артемий Владимирович\
Контакты: artemkr2003@mail.ru\
Работа выполнена: 17.09.2022\
Преподаватель: Миронов Евгений Сергеевич

### Постановка задачи

Цель работы: Приобретение практических навыков диагностики работы программного обеспечения.

## Задание

При выполнении последующих лабораторных работ необходимо продемонстрировать ключевые системные вызовы, которые в них используются и то, что их использование соответствует варианту ЛР.

По итогам выполнения всех лабораторных работ отчет по данной должен содержать краткую сводку по исследованию последующих ЛР.

## Выводы

### Лабораторная работа 2

В ходе выполнения лабораторной работы был приобретён навык в управлении процессами в ОС и
обеспечении обмена данных между процессами посредством каналов. Использованы системные
вызовы:

1. fork() – создание дочернего процесса
2. open() – открытие файла
3. close() – закрытие файла
4. write() – запись последовательности байт
5. read() – чтение последовательности байт
6. execl() – замена образа памяти процесса
7. dup2() – переназначение файлового дескриптора

### Лабораторная работа 3

В ходе выполнения работы были приобретены навыки в распараллеливании вычислений,
управлении потоками и обеспечении синхронизации между ними. Использованы библиотечные
вызовы:

1. pthread_create() – создание нового потока
2. pthread_join() – ожидание окончания потока
3. pthread_mutex_init() – инициализация мьютекса
4. pthread_mutex_lock() – блокировка мьютекса
5. pthread_mutex_unlock() – разблокировка мьютекса
6. pthread_mutex_destroy() – удаление мьютекса

### Лабораторная работа 4

В ходе выполнения работы получены навыки в обеспечении обмена данных между процессами
посредством технологии «File mapping». В написанной программе используются следующие
системные вызовы:

1. unlink() – удаление имени из файловой системы
2. fork() – создание дочернего процесса
3. open() – открытие файла
4. close() – закрытие файла
5. write() – запись последовательности байт
6. lseek() - установка смещения в файловом дескрипторе
7. mmap() - создание отражения файла в памяти
8. munmap() - удаление отражения файла в памяти

### Лабораторная работа 5

В ходе выполнения работы приобретены практические навыки в создании динамических
библиотек, создании программ, использующих динамические библиотеки, освоена работа со
сборочной моделью. В полученных программах используются системные вызовы dlopen, dlsym,
dlclose – открытие динамической библиотеки, получение функции и закрытие соответственно.

### Лабораторные работы 6-8

В ходе выполнения лабораторных работ получен навык в управлении серверами сообщений, применении отложенных вычислений и интеграции программных систем друг с другом.