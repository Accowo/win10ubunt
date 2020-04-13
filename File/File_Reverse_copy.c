#include <stdio.h>

int main(int argc, char **argv){
    if (argc != 3){
        printf("input error\n");
        return 0;
    }
    FILE *fp1 = fopen(argv[1],"r");
    FILE *fp2 = fopen(argv[2],"w");
    if (fp1 == NULL || fp2 == NULL){
        fclose(fp1);
        fclose(fp2);
    }
    fseek(fp1, -2, SEEK_END);
    char ch;
    while (1){
        ch = fgetc(fp1);
        fputc(ch, fp2);
        if (fseek(fp1, -2, SEEK_CUR) == EOF){
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}
