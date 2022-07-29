# OTUS-CPP-Professional-HomeWork_8  
# Утилита для обнаружения файлов-дубликатов, разаработана с применением библиотеки Boost.  

Цель: Разработать утилиту для обнаружения файлов-дубликатов, применением  библиотеки Boost.  

Утилита должна иметь возможность через параметры командной строки принимать 
- директории для сканирования (может быть несколько) 
- директории для исключения из сканирования (может быть несколько)  
- уровень сканирования (один на все директории, 0 - только указанная директория без вложенных)
- минимальный размер файла, по умолчанию проверяются все файлы больше 1 байта.
- маски имен файлов разрешенных для сравнения (не зависят от регистра)
- размер блока, которым производится чтения файлов, параметр -S
- один из имеющихся алгоритмов хэширования (crc32), параметр -H

Результат работы утилиты список полных путей файлов с идентичным содержимым, выводимый на стандартный вывод.   
Одна строка- один файл. Идентичные файлы должны подряд, одной группой. Разные группы разделяются пустой строкой.   
Обязательно свойство утилиты - бережное обращение с дисковым вводом выводом.  
