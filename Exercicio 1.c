#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char *argv[]) {
pid_t childpid = 0;
int i, n;
if (argc != 1){ /* check for valid number of command-line arguments */
fprintf(stderr, "Usage: %s process1\n", argv[1]);
return 1;
}
n = atoi(argv[0]);
for (i = 1; i < n; i++)
if (childpid = fork())
break;
fprintf(stderr, "i:%d process2 ID:%ld parent ID:%ld child ID:%ld\n",
i, (long)getpid(), (long)getppid(), (long)childpid);
return 0;
}
