#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	FILE *A = fopen("A.txt", "r");
	if (A == NULL){
		printf("Error");
		exit(-1);
	}
	char string[1024];
	fgets(string, 1024, A);
	int i, j, k = 0;
	int n = strlen(string);
	for(i = 0; i < n-1; i++){
		if(i > 0 && string[i] == string[i-1]){
			continue;
		}
		printf("%c :", string[i]);
		for (j = 0; j < n-1; j++){
			if(string[i] == string[j]){
				k ++;
			}
		}
		printf("%d\n", k);
		k = 0;
	}
	return 0;
}
