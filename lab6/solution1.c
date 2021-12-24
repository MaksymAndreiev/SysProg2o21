#include <stdio.h>
#include <string.h>

int main(){
    char line[256];
    char arr[100][50];
    int i = 0;

    fgets(line, sizeof(line), fopen("/proc/self/stat", "r"));

    char * token = strtok(line, " ");
    while( token != NULL ) {
        strcpy(arr[++i], token);
        token = strtok(NULL, " ");
    }
    printf( "%s\n", arr[4]);
    return 0;
}
