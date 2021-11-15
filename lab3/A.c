#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main(){
	printf("Введите строку:\n");
	char string[1024*2];
	char temp;
	scanf("%[^\n]", string);
	int i, j = 0, k;
	
	FILE *A = fopen("A.txt", "w");
	if(A == NULL){
		printf("Error");
		exit(-1);
	}
	
	int n = strlen(string);
	char *str = (char*) malloc (n-1);
	for(i = 0; i< n; i++){
		if (string[i] >= 'a' && string[i] <= 'z' || string[i] >='A' && string[i] <= 'Z'){
			str[j] = string[i];
			j++;
		} else{
			i++;
		}
	}
	
	n = strlen(str);
	for(i = 0; i < n - 1; i++){
		for(k = 0; k < n - i - 1; k++){
			if(str[k] > str[k + 1]){
				temp = str[k];
				str[k] = str[k + 1];
				str[k  + 1] = temp;
			}
		}
	}
	
	fprintf(A, "%s", str);
	fclose(A);
	free(str);
	return 0;
}
