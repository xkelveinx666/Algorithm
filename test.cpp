#include <unistd.h>
#include <iostream>
using namespace std;
int main(void) {
    int fd[2];
    pid_t childpid;
    if (pipe(fd) < 0) {
        cout << "pipe create error" << endl;
        return -1;
    }
    if ((childpid = fork()) > 0) {
        if ((childpid = fork()) > 0) {
            sleep(1);
            cout << "f" << endl;
            char ch1[37];
            char ch2[37];
            close(fd[1]);
            read(fd[0], &ch1, 37);
            cout << ch1 << endl;
            read(fd[0], &ch2, 37);
            cout << ch2 << endl;
        } else {
            cout << "s2" << endl;
            char ch1[] = "Child process2 is sending a message!";
            close(fd[0]);
            write(fd[1], ch1, 37);
            close(fd[1]);
        }
    } else {
        cout << "s1" << endl;
        char ch1[] = "Child process1 is sending a message!";
        close(fd[0]);
        write(fd[1], ch1, 37);
        close(fd[1]);
    }
    return 0;
}
