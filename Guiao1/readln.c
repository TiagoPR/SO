#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <string.h>

ssize_t readln2(int fd, char *line, size_t size)
{
  int i;
  ssize_t n = read(fd, line , size);
  if (!n)
  {
    return 0;
  }
  for (i  = 0; line[i] != '\n' ; i++);
  for(i++; line[i] == '\n';i++ );
  lseek(fd, i-n, SEEK_CUR);
  return i-1;
}

// ssize_t nl2(int fd,char *line, size_t size){
  
//   int tamanho = readln2(fd, line,size);
//   int offset = 0;
//   int i;
//   for(i = 1; line[tamanho] == '\n' ; i++){
//     printf("%d", tamanho);
//     fprintf(stdout,"%d",i);
//     for(int j = 0; j < tamanho; j++){
//       fprintf(stdout, "%c",line[i]);
//     }
//     tamanho = readln2(fd + offset, line,size);
//     offset += tamanho;
//     printf("%c", line[tamanho]);
//   }
//   return tamanho; 
// }

int main(int argc,char* argv[])
{
    if (argc != 2)
    {
      fprintf(stderr, "usage: %s source destination\n",argv[0]);
      return 1;
    }

    int sfd = open(argv[1], O_RDONLY);
    if (sfd == 1)
    {
      perror(argv[1]);
      return 1;
    }

    //char s[61];
    // int tamanho = readln2(sfd,s,61);

    // printf("readln:\n");
    // for (int i = 0 ; i < tamanho; i++){
    //   printf("%c", s[i]);
    // }
    // printf("\n");

    char line[1024];
    size_t size;
    int i = 0;
    while((size = readln2(sfd, line, 1024))) {
        char lineno[100];
        sprintf(lineno, "%*d  ", 6, i++);
        write(STDOUT_FILENO, lineno, strlen(lineno));
        write(STDOUT_FILENO, line, size);
        write(1,"\n",1);
    }

    close(sfd);

    return 0;
}