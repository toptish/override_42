#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a_user_name[256];

int verify_user_name() {
    puts("verifying username....\n");
    return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *buffer) {
    return strncmp(buffer, "admin", 5);
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
    if (check) {
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
