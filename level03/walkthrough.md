# LEVEL 03

## Команды и ресурсы
gdb

## Уязвимость
Подбор пароля

## Решение
1. Сразу обращаем внимание на настройки безопасности. NX - enabled, присутствует канарейка, то есть перезаписать адрес возврата и исполнить код со стека
не получится.
```bash
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   /home/users/level03/level03

```
2. Посмотрим на саму программу. От нас ожидается ввод валидного пароля, при невалидном программа выходит
3. Посмотрим более детально  в отладчике. Подробный анализ [тут](resources/disas.md)
- Перед нами программа, где в функции main с помощью функции scanf пользователь вводит пароль (число), затем вызывается функция
test(user_input, 322424845), где user_input - пароль-число, введенные пользователем. В функции test в случае если (322424845 - user_input) меньше 21 происходит вызов
функции decrypt(322424845 - user_input), в противном случае вызывается decrypt(rand()).
- В функции decrypt в локальных переменных задается зашифрованная строка "Q}|u`sfg~sf{}|a3", каждый элемент которой дешифруется
с помощью операции XOR с аргументом decrypt. В случае, если дешифрованная строка совпадает со строкой "Congratulations!" происходит
вызов system("/bin/sh"), в противном случае выводится puts("\nInvalid Password")

4. Таким образом, наша задача - подобрать такое число X, чтобы decrypt(322424845 - X) верно дешифровала строку, при этом мы знаем, что
322424845 - X <= 21. Небольшой питоновский скрипт [тут](resources/decode.py) выдает нам число 

322424827


5. Проверим:
```bash
level03@OverRide:~$ ./level03
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf

```

p.s. в программе также присутсвуют неиспользуемые функции


## Воссоздадим бинарный файл
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

void clear_stdin(void) {
    char value = 0;

    while (value != 0xff) {
        value = getchar();
        if (value == 0xa)
            return;
    }
}

uint32_t get_unum(void) {
    uint32_t user_value = 0; // EBP - 0xc

    fflush(stdout);
    scanf("%u", &user_value);
    clear_stdin();
    return user_value;
}

void prog_timeout() {
    exit(1);
}

void decrypt(uint32_t diff) {
    uint8_t buffer[] = "Q}|u`sfg~sf{}|a3";  // EBP - 0x1d
    uint32_t len;                           // EBP - 0x24

    len = strlen(buffer);

    uint32_t i = 0;
    while (i < len) {
        buffer[i] = buffer[i] ^ diff;
        i++;
    }

    if (!strncmp(buffer, "Congratulations!", 0x11)) {
        system("/bin/sh");
        return;
    }
    puts("\nInvalid Password");
}

void test(uint32_t user_pwd, uint32_t real_pwd) {
    uint32_t diff = real_pwd - user_pwd;

    switch (diff)
    {
        case 0x1:
            decrypt(diff);
            break;
        case 0x2:
            decrypt(diff);
            break;
        case 0x3:
            decrypt(diff);
            break;
        case 0x4:
            decrypt(diff);
            break;
        case 0x5:
            decrypt(diff);
            break;
        case 0x6:
            decrypt(diff);
            break;
        case 0x7:
            decrypt(diff);
            break;
        case 0x8:
            decrypt(diff);
            break;
        case 0x9:
            decrypt(diff);
            break;
        case 0x10:
            decrypt(diff);
            break;
        case 0x11:
            decrypt(diff);
            break;
        case 0x12:
            decrypt(diff);
            break;
        case 0x13:
            decrypt(diff);
            break;
        case 0x14:
            decrypt(diff);
            break;
        case 0x15:
            decrypt(diff);
            break;
        default:
            decrypt(rand());
            break;
    }
    return;
}

int main(int argc, char *argv[]) {
    uint32_t user_pwd;

    srand(time(0));
    puts("\b***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("\b***********************************");

    printf("Password:");
    scanf("%d", &user_pwd);
    test(user_pwd, 0x1337d00d); // 322424845
}
```


## Переносим на виртуальную машину, компилируем, проверяем
1. Копируем на виртуальную машину
``` bash
 scp -P 4242 ~/42/override/level03/source.c level03@192.168.56.129:/tmp/source_level03.c
 ```

2. заходим под level04 на виртуальную машину
```bash
su level04
```

3. Компилируем

```bash
cd /tmp
gcc -z lazy -m32 -std=c99 source_level03.c -o level03
```


4. Меняем права
```bash
level03@OverRide:/tmp$ chmod u+s level03; chmod +wx level03; chmod +s level03;

```
5. Возвращаемся в юзера level03 и Запускаем
```bash
level03@OverRide:/tmp$ exit


```
6. Проверяем уязвимость
```bash
level04@OverRide:/tmp$ ./level03
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf



```