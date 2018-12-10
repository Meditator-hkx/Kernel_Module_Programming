gcc -Wall -o hello hello.c
strace ./hello # trace what syscalls are really used
