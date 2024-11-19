#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(2, "Usage: getcnt <syscall number>\n");
        exit(1);
    }
    int syscall_number = atoi(argv[1]);
    int count = getcnt(syscall_number);
    if (syscall_number <= 0 || syscall_number > 22) {
        fprintf(2, "Invalid syscall number.\n");
        exit(1);
    }
    printf("Syscall %d has been called %d times.\n", syscall_number, count);

    exit(0);

}
