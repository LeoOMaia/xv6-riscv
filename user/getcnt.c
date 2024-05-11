#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if (argc > 1)
    printf("syscall %d has been called %d times\n", atoi(argv[1]), getcnt(atoi(argv[1])));
  exit(0);
}