#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char* const argv[])
{
    char buffer[1024];
    int lidos;
    int fd = open("fifo",O_WRONLY,0666);
    while ((lidos = read(STDIN_FILENO,buffer,1024)) > 0)
    {
        write(fd,buffer,lidos);
    }
    close(fd);
    return 0;
}