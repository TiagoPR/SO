#include <signal.h>
#include <sys/types.h>
typedef void (*sighandler_t)(int);

int ctrl_c_counter = 0;
int tempo = 0;
// size_t seconds = 0;

void ctrl_c_handler(int signum){
    printf("CTRL+C\nTempo:%d\n", tempo);
    tempo = 0;
    ctrl_c_counter++;
}

void ctrl_barra_handler(int signum){
    printf("CTRL+C's: %d\n", ctrl_c_counter);
    exit(0);
}

// void sigalrm_handler(int signum) {
//     seconds++;
//     alarm(1);
// }

int main(){
    if (signal(SIGINT,ctrl_c_handler) == SIG_ERR)
    {
        perror("SIGINT failed");
    }

    if (signal(SIGQUIT,ctrl_barra_handler) == SIG_ERR)
    {
        perror("SIGQUIT failed");
    }

    // if(signal(SIGALRM, sigalrm_handler) == SIG_ERR) {
    //     puts("Erro com SIGALRM");
    //     exit(1);
    // }

    // alarm(1);
    // while(1);

    while (1) // alternativa com um SIGALRM
    {
        printf("working...\n");
        tempo += 1;
        sleep(1);
    }

    return 0;
    
}