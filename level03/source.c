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