#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (int argc , char * argv[]){
    int pd[argc - 2][2];


    if(pipe(pd[0]) == -1)
    {
        return 1;
    }

    if (!fork())
    {
        //filho
        close(pd[0][0]);
        dup2(pd[0][1],STDOUT_FILENO);
        close(pd[0][1]);
        execlp(argv[1],argv[1],NULL);
        perror(argv[1]);
        _exit(1);
    }

    for (int i = 1; i < argc-2; ++i){
        if(pipe(pd[i]) == -1)
        {
            return 1;
        }

    }

    return 1;
}

