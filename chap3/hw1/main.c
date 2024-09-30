#include <stdio.h>
#include <string.h>
#include "copy.h"

#define NumStrings 5

void SortStringsLength(char arr[][MAXLINE],int n);

int main(){
	char lines[NumStrings][MAXLINE];
	int count =0;

	while(count< NumStrings){
		gets(lines[count]);
		count++;
	}
	SortStringsLength(lines, NumStrings);

	for (int i =0; i< NumStrings; i++){
		printf("%s\n",lines[i]);
	}

	return 0;
}

void SortStringsLength(char arr[][MAXLINE], int n) {
    char temp[MAXLINE];
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strlen(arr[i]) < strlen(arr[j])) {
                copy(arr[i], temp); 
                copy(arr[j], arr[i]);
                copy(temp, arr[j]);
            }
        }
    }
}
