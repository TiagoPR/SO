#include <sys/types.h>
#include <sys/stat.h>

//int mkfifo(const char *pathname, mode_t mode);
//                                      |-> 0 6 0

// Se num ficheiro temos permissão (por exemplo, 0666, como o nosso umask é 0022 é retirado ao 0666 e passa a ter 0644)

int main(){
    mkfifo("fifo",0666);
    return 0;
}