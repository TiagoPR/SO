#include <unistd.h>     /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>   /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

// pid_t getpid(void); recebe o pid do filho
// pid_t getppid(void); (parent proccess id) recebe o pid do pai do filho
// void _exit(int status); 
// ps - process status
// pidt_t wait(int *status); 
// int WIFEXITED(int status); /* macro */



int main(){
    // Exercício 1,2
    // pid_t pid;
    // printf("Ola\n");
    // pid = fork();
    // if(pid == 0){
    //     printf("filho pid = %d, ppid = %d\n", getpid(), getppid());
    //     _exit(0);
    // }
    // sleep(1); // o pai termina o processo mais rápido que o filho
    // printf("pai pid = %d, ppid = %d, filho = %d\n", getpid(), getppid(), pid);
    // return  0;

    //Exercicio 4

    // pid_t pid;
    // int count = 0;
    // // criação de 10 filhos 
    // while(count < 10){
    //     pid = fork();
    //     if(pid == 0){
    //         printf("filho pid = %d, ppid = %d\n", getpid(), getppid());
    //         _exit(count);
    //     }
    //     count++;
    // }
    // //ciclo que espero pelo final
    // for(int i = 0; i!= 10; i++){
    //     int status;
    //     pid_t pid = wait(&status);
    //     if(WIFEXITED(status)){
    //         printf("pid = %d, _exit = %d\n", pid, WEXITSTATUS(status));
    //     }
    // }
    // sleep(1);
    // return  0;

    // Exercicio 3

    pid_t pid;
    int count = 0;
    // criação de 10 filhos 
    while(count < 10){
        pid = fork();
        if(pid == 0){
            printf("filho pid = %d, ppid = %d\n", getpid(), getppid());
            _exit(count);
        }
        int status;
        pid_t pid = wait(&status);
        if(WIFEXITED(status)){
            printf("_exit = %d\n", pid, WEXITSTATUS(status));
        }
        count++;
    }
    sleep(1);
    return  0;
}