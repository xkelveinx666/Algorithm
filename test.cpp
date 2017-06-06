#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;
int main(void) {
    char ch;

    int fd[2];

    pid_t childpid;
    if (pipe(fd) == -1)

    {
        perror("pipe call");

        return -1;
    }
    childpid = fork();

    if (childpid != 0)

    {
        close(fd[0]);

        while (cin.get(ch) && ch != 'x')

        {
            write(fd[1], &ch, 1);
        }

    }

    else if (childpid == 0)

    {
        close(fd[1]);

        while (read(fd[0], &ch, 1) && ch != 'x')

        {
            if (ch >= 'a' && ch <= 'z')

            {
                cout << (char)(ch + 'A' - 'a');
            }

            else {
                cout << ch;
            }
        }
    }
}
