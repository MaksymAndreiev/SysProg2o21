#include <poll.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


enum { PIPES_COUNT = 2 }; 

int main(int argc, char *argv[])
{
    const char* const pipeNames[PIPES_COUNT] = {"in1", "in2"};
    struct pollfd fds[PIPES_COUNT];
    int openCount = 0;
    int index;

    for (index = 0; index < PIPES_COUNT; index++)
    {
        fds[index].events = POLLIN;
        fds[index].fd = open(pipeNames[index], O_RDONLY | O_NONBLOCK);      
        if (fds[index].fd >= 0)
        {
            openCount++;
        }
    }

    int sum = 0;
    char chr = 0;    
    while((openCount > 0) && (poll(fds, PIPES_COUNT, -1) > 0))
    {      
        for (index = 0; index < PIPES_COUNT; index++)
        {
            if (fds[index].revents & POLLIN) 
            {
                read(fds[index].fd, &chr, sizeof(chr));
                sum += chr - '0';
            }
            else if (fds[index].revents != 0)
            {
                close(fds[index].fd);
                fds[index].fd = -1;
                openCount--;
            }          
        }            
    }
    printf("%d\n", sum);
    return 0;
}
