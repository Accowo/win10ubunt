#include <stdio.h>
void init_array(int *a, int n){
    int i;
    for (i = 0; i < n; i++){
        a[i] = i;
    }
}
int main(void){
    FILE *fp = fopen("f4.dat", "w+");
    int a[20];
    int n = 20;
    init_array(a, n);
    int i;
    for (i = 0; i < n; i++){
        fprintf(fp, "%5d", a[i]);
    }
    int order;
    printf("请输入序号:");
    scanf("%d",&order);
    order = (order-1)*5;
    printf("初始位置指针位置:%ld\n", ftell(fp));
    int num;
    fseek(fp, order, SEEK_SET);
    printf("输入序号后位置指针位置:%ld\n", ftell(fp));
    fscanf(fp, "%5d", &num);
    printf("对应的数据:%d\n", num);
    fclose(fp);

    return 0;
}
