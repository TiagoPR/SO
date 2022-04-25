//
// Created by tiagorodrigues on 25-04-2022.
//

#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc,char* argv[])
{
    //grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l

    int pd[3][2]; // [0][0] - [0][1] OUTRO PIPE [1][0] - [1][1]

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
        execlp("grep","grep","-v","^#","/etc/passwd",NULL);
        perror("grep");
        _exit(1);
    }

    close(pd[0][1]);

    if(pipe(pd[1]) == -1)
    {
        return 1;
    }

    if(!fork())
    {
        dup2(pd[0][0],STDIN_FILENO);
        close(pd[0][0]);
        dup2(pd[1][1],STDOUT_FILENO);
        close(pd[1][1]);
        execlp("cut","cut","-f7","-d:",NULL);
        perror("cut");
        _exit(1);
    }

    close(pd[0][0]);
    close(pd[1][1]);

    if(pipe(pd[2]) < 0)
    {
        perror("pipe");
        return 1;
    }
    if(!fork())
    {
        close(pd[2][0]);
        dup2(pd[1][0],STDIN_FILENO);
        close(pd[1][0]);
        dup2(pd[2][1],STDOUT_FILENO);
        close(pd[2][1]);
        execlp("uniq","uniq",NULL);
        perror("uniq");
        _exit(1);
    }


    close(pd[1][0]);
    close(pd[2][1]);

    if(!fork())
    {
        dup2(pd[2][0],STDIN_FILENO);
        close(pd[2][0]);
        execlp("wc","wc","-l",NULL);
        perror("wc");
        _exit(1);
    }
    close(pd[2][0]);

    if (wait(NULL) == -1) puts("Error");
    if (wait(NULL) == -1) puts("Error");
    if (wait(NULL) == -1) puts("Error");
    if (wait(NULL) == -1) puts("Error");

    return EXIT_SUCCESS; // EXIT_SUCESS => #include <stdlib.h>
}
