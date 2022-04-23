#include <unistd.h>     /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>   /* chamadas wait*() e macros relacionadas */
#include <stdio.h>

//matriz nao aleatoria

#define char valor = 'c';
char matrix[4][1000000]; //qq variavel global é inicializada a zero

int main(){

    matrix[3][999999] = valor;
    matrix[2][999999] = valor;
    pid_t pid;
    int count = 0;

    // Sequencial
    
    // for(int i = 0; i<4; i++){
    //     pid = fork();
    //     if (pid == 0)
    //     {
    //         for(int j = 0; j<1000000; j++){
    //            if (matrix[i][j] == valor){
    //                printf("Encontrei\n");
    //                printf("filho pid = %d, ppid = %d\n", getpid(), getppid());
    //                 _exit(i);
    //            } 
    //         }
    //         _exit(-1);
    //     }
        
    //     int status;
    //     pid_t pid = wait(&status);
    //     if(WIFEXITED(status)){
    //         printf("_exit = %d\n", pid, WEXITSTATUS(status));
    //     }
    // }

    // Funciona, desta maneira consigo usar o WIFEXITED

    // for(int i = 0; i<4; i++){
    //     if ((pid = fork()) == 0)
    //     {
    //         for(int j = 0; j<1000000; j++){
    //            if (matrix[i][j] == valor){
    //                printf("filho pid = %d, ppid = %d\n", getpid(), getppid());
    //                 _exit(1);
    //            } 
    //         }
    //         _exit(0);
    //     }
    //     int status;
    //     pid = wait(&status);
    //     if(WIFEXITED(status)){
    //         if(WEXITSTATUS(status) == 1){
    //             count++;
    //             printf("Encontrei %d\n", pid);
    //         }
    //     }
    // }

    // Não consigo usar WIFEXITED, pois só faz uma vez para um filho ao estar fora do for.

    for(int i = 0; i<4; i++){
        if ((pid = fork()) == 0)
        {
            for(int j = 0; j<1000000; j++){
               if (matrix[i][j] == valor){
                   printf("filho pid = %d, ppid = %d\n", getpid(), getppid());
                    _exit(1);
               } 
            }
            _exit(0);
        }
    }

    int status;
	for(size_t i = 0; i < 4; i++) {
		int pid = wait(&status);
		if(WEXITSTATUS(status) == 1){
            count++;
            printf("Encontrei %d\n", pid);
        }
	}

    printf("Count: %d\n",count);

    //------------------------------------------------------------------------------//

    // dar print de uma variavel sem printf (um à parte)

    // char str[256];
    // snprintf(str,sizeof(str),"%d",i);
    // write(1,str,strlen(str));

    //------------------------------------------------------------------------------//

    // para o ex.6

    // for(j=0; j!= n; j++){
    //     pid = wait(&como);
    //     for(i = 0; pids[i] != pid; i++){
    //         resultados[i] = (WIFEXITED(como) && WEXITSTATUS(como));
    //     }
    // }

    // for(j = 0; j!= n; j++){
    //     if(resultados[j]){
    //         printf("linha %d\n", j);
    //     }
    // }



    return  0;
}