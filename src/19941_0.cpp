#include<stdio.h>

void printTable(char input[]){
	printf("%s", input);
}

int countTable(int n, char input[]){
	int result = 0;
	for(int i = 0; i<n; i++){
		if(input[i] == '*')result++;
	}
	return result;
}

int main(void){
	int n, k;
	scanf("%d %d", &n, &k);
	char input[n+1];
	
	scanf("%s", input);
	
	
	for(int i = 0; i < n; i++){
		if(input[i] == 'P')
			for(int j = i-k; j < i+k+1; j++){
				if(input[j] == 'H'){
					input[j] = '*';
					break;
				}	
			}
	}
	printf("%d", countTable(n, input));
	return 0;
}