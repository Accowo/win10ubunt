#include <stdio.h>

int main(void){
    FILE *fp = fopen("a.txt","r+");
    if (fp == NULL){
        perror("open file error");
        return 0;
    }
    fputc(1,fp);
    fputc(2,fp);
    fputc(3,fp);
    fputc(4,fp);
    fputc(5,fp);

    char ch;
    ch = fgetc(fp);
    while (ch != EOF){
        putchar(ch);
        ch = fgetc(fp);
    }
    fclose(fp);
    return 0;
}
