/*
8.	有两个磁盘文件，各自存放已排好序的若干个字符
（如a1. dat 中放"abort"，a2.dat中放 "boy"）
要求将两个文件合并，合并后仍保持有序，
存放在a3.dat文件中。
*/
#include <stdio.h>
#include <string.h>
void sort(char *str){
	
	int n = strlen(str);
	int i,j;
	char t;
	for (i = 0; i < n-1; i++){
		for (j = 0; j < n-i-1; j++){
			if (str[j] > str[j+1]){
				t = str[j];
				str[j] = str[j+1];
				str[j+1] = t;
			}
		}
		
	}
}
int main(void){
/*
	FILE *fp1 = fopen("a1.dat", "w");
	FILE *fp2 = fopen("a2.dat","w");
	if (fp1 == NULL || fp2 == NULL){
		perror("打开文件发生错误");
		return -1;
	}
	fputs("abort", fp1);
	fputs("boy", fp2);
	fclose(fp1);
	fclose(fp2);

*/
	FILE *fp3 = fopen("a1.dat", "r");
	FILE *fp4 = fopen("a2.dat","r");
	FILE *fp5 = fopen("a3.dat","w");
	
	if (fp3 == NULL || fp4 == NULL || fp5 == NULL ){
		perror("打开文件发生错误");
		return -1;
	}
	char str[20] = {'\0'};
	char ch;
	int i;
	for (i = 0; i < 20; i++){
		ch = fgetc(fp3);
		if (!feof(fp3)){
			str[i] = ch;
  		}
		else {
			ch = fgetc(fp4);
			if (!feof(fp4)){
				str[i] = ch;
	  		}
	  		else {
	  			break;
			}
		}
	}
	sort(str);
	printf("%s", str);

	fputs(str, fp5);

	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	return 0;
}
