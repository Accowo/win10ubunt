#include <stdio.h>
int sum(int *a, int n){
    int i;
    int sum = 0;
    for (i = 0; i < n; i++){
        sum += a[i];
    }
    return sum;
}
int main(void){
        
    FILE *fp = fopen("f3.dat", "w+");
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int n = 10;
    fwrite(a, sizeof(int), n, fp);
    fread(a, sizeof(int), n, fp);
    printf("%d\n", sum(a, n));
    fclose(fp);
    return 0;
}
