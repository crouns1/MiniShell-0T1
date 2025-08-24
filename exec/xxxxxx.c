#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd2 = dup(fd);
    close(fd);
    write(fd, "ABCedwd", 8);
    write(fd2, "DEFdwedwe", 10);

    close(fd);
    close(fd2);
    return 0;
}

// #include <stdio.h>
// #include <unistd.h>
// #include <fcntl.h>

// int main(int c , char **v) {
//     int fd_3 = open("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.txt" , O_CREAT | O_RDWR, 0644);
//     // int fd_4 = open("file_out.txt" , O_CREAT | O_RDWR | O_TRUNC, 0644);
//     // int child = fork();
//     // int fd[2];
//     // pipe(fd);

//     // int old0 = dup(0);
//     // int old1 = dup(1);
//     // close(0);
//     // close(1);
//     // dup(fd_3);
//     // dup(fd_4);
//     // close(fd_3);
//     // close(fd_4);
//     // dup(in);
//     // dup(out);
//     // close(0);
//     // close(1);
//     int in = dup(fd_3);
//     write(fd_3 , "zzzzzz" , 7);
//     write(in , "xxxxxxxxx" , 10);
//     close(fd_3);
//     close(in);
//     // int child = fork();
//     // if(child == 0) {
//     //     // int in = dup(fd_3);
//     //     // dup(in);
//     //     // printf("%d %d" , in , out);
//     //     // in = dup(0);
//     //     // out = dup(1);
//     //     int in = dup(fd_3);
//     //     close();
//     //     execvp("/bin/cat" , (char *[]){"cat" , "-e" , NULL});
//     // }        
// //         // in = dup(0);
// //         // out = dup(1);
// //         // dup2(in, STDIN_FILENO);
// //         // dup2(out, STDOUT_FILENO);
// //         // close(in);
// //         // close(out);
// //         // printf("error\n");
// //     }
// //     close(0);
// //     close(1);
// //     dup(old0);
// //     dup(old1);
// //     printf("errorxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
// //     close(old0);
// //     close(old1);
// // }

// }