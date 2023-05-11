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