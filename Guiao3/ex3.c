#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    if (argc < 0)
    {
        return 0;
    }

    for(int i = argc; i >= 0; i--){
        if(fork() == 0){
        execlp(argv[i],argv[i],NULL);
        perror(argv[i]);
        _exit(1);   
        }
    }

    while(wait(NULL) != -1);

    return 0;
}