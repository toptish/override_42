# LEVEL 00

## Команды и ресурсы
gdb

## Уязвимость


## Решение
1. Попробуем запустить программу
```bash
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   /home/users/level00/level00
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:zasd

Invalid Password!

```

При запуске программы, видим, что ожидается ввод пароля. При неверном вводе программа завершает работу.

2. Посмотрим в отладчике
```asm
(gdb) disas main
Dump of assembler code for function main:
   0x08048494 <+0>:	push   %ebp
   0x08048495 <+1>:	mov    %esp,%ebp
   0x08048497 <+3>:	and    $0xfffffff0,%esp
   0x0804849a <+6>:	sub    $0x20,%esp
   0x0804849d <+9>:	movl   $0x80485f0,(%esp)
   0x080484a4 <+16>:	call   0x8048390 <puts@plt>
   0x080484a9 <+21>:	movl   $0x8048614,(%esp)
   0x080484b0 <+28>:	call   0x8048390 <puts@plt>
   0x080484b5 <+33>:	movl   $0x80485f0,(%esp)
   0x080484bc <+40>:	call   0x8048390 <puts@plt>
   0x080484c1 <+45>:	mov    $0x804862c,%eax
   0x080484c6 <+50>:	mov    %eax,(%esp)
   0x080484c9 <+53>:	call   0x8048380 <printf@plt>
   0x080484ce <+58>:	mov    $0x8048636,%eax
   0x080484d3 <+63>:	lea    0x1c(%esp),%edx
   0x080484d7 <+67>:	mov    %edx,0x4(%esp)
   0x080484db <+71>:	mov    %eax,(%esp)
   0x080484de <+74>:	call   0x80483d0 <__isoc99_scanf@plt>
   0x080484e3 <+79>:	mov    0x1c(%esp),%eax
   0x080484e7 <+83>:	cmp    $0x149c,%eax
   0x080484ec <+88>:	jne    0x804850d <main+121>
   0x080484ee <+90>:	movl   $0x8048639,(%esp)
   0x080484f5 <+97>:	call   0x8048390 <puts@plt>
   0x080484fa <+102>:	movl   $0x8048649,(%esp)
   0x08048501 <+109>:	call   0x80483a0 <system@plt>
   0x08048506 <+114>:	mov    $0x0,%eax
   0x0804850b <+119>:	jmp    0x804851e <main+138>
   0x0804850d <+121>:	movl   $0x8048651,(%esp)
   0x08048514 <+128>:	call   0x8048390 <puts@plt>
   0x08048519 <+133>:	mov    $0x1,%eax
   0x0804851e <+138>:	leave  
   0x0804851f <+139>:	ret    
End of assembler dump.

```

Видим, что пользовательский ввод сравнивается с числом 5276 ($0x149c)

```asm
   0x080484de <+74>:	call   0x80483d0 <__isoc99_scanf@plt>
   0x080484e3 <+79>:	mov    0x1c(%esp),%eax
   0x080484e7 <+83>:	cmp    $0x149c,%eax
```

, после чего в случае неравенства программа переходит
к main+121, а в случае равенства вызывается system с аргументом "/bin/sh"

```asm
(gdb) x/s 0x8048649
0x8048649:	 "/bin/sh"

```

```bash
level00@OverRide:~$ ./level00 5276
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL

```

## Воссоздадим бинарный файл
```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int password;

    puts("***********************************")
    puts("* \t     -Level00 -\t\t  *")
    puts("***********************************")
    printf("Password:")
    scanf("%d", password)
    if (password == 0x149c)
    {
        puts("\nAuthenticated!");
        system("/bin/sh");
        return (0);
    }
    puts("\nInvalid Password!");
    return (1);
}
```

## Переносим на виртуальную машину, компилируем, проверяем
1. Копируем на виртуальную машину
``` bash
 scp -P 4242 ~/42/override/level00/source.c level00@192.168.56.129:/tmp/source_level00.c
 ```

2. заходим под bonus1 на виртуальную машину
```bash
su level01
```

3. Компилируем

```bash
cd /tmp
gcc -fno-stack-protector -z lazy -m32 source_level00.c -o level00

```
```bash
level01@OverRide:/tmp$ checksec --file level00
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   level00

```

4. Меняем права
```bash
level01@OverRide:/tmp$ chmod u+s level00; chmod +wx level00;

```
5. Возвращаемся в юзера bonus0 и Запускаем
```bash
level01@OverRide:/tmp$ exit


```
6. Проверяем уязвимость
```bash
level00@OverRide:/tmp$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL

```
