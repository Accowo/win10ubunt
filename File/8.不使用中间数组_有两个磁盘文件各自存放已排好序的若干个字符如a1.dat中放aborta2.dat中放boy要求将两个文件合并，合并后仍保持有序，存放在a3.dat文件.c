/*
8.	有两个磁盘文件，各自存放已排好序的若干个字符
（如a1. dat 中放"abort"，a2.dat中放 "boy"）
要求将两个文件合并，合并后仍保持有序，
存放在a3.dat文件中。
*/
#include <stdio.h>

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
	FILE *fp5 = fopen("a4.dat","w");
	
	if (fp3 == NULL || fp4 == NULL || fp5 == NULL ){
		perror("打开文件发生错误");
		return -1;
	}
	char ch1 = fgetc(fp3);
	char ch2 = fgetc(fp4);
	while(ch1 != EOF && ch2 != EOF){
		if (ch1 <= ch2){
			fputc(ch1,fp5);
			ch1 = fgetc(fp3);
		}
		else {
			fputc(ch2,fp5);
			ch2 = fgetc(fp4);
		}
	}
    while (ch1 != EOF){
    	fputc(ch1,fp5);
		ch1 = fgetc(fp3);
    }
    while (ch2 != EOF){
		fputc(ch2,fp5);
		ch2 = fgetc(fp4);
    }

	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	return 0;
}
