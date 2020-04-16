#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _DEBUG

#ifdef _DEBUG
#define DEBUG(fromat,...) printf("FILE: "__FILE__";      LINE: %d;     check:"fromat"\n", __LINE__, ##__VA_ARGS__)
#else
#define DEBUG(fromat,...)
#endif

typedef struct STAFF{
    char Number[20];
    char Name[20];
    char Sex;
    int Age;
    int Wage;
    struct STAFF *next;
}STAFF;

STAFF *CreatList(){
    STAFF *head = (STAFF *)malloc(sizeof(STAFF));
    if (head == NULL){
        exit(0);
    }
    head->next = NULL;
    return head;
}
void Add_List(STAFF *head){
	
    STAFF *p = head;
    STAFF *pnew = (STAFF *)malloc(sizeof(STAFF));
    if (pnew == NULL){
    	printf("申请内存出错\n");
        exit(0);
    }

    while(p->next != NULL){
        p = p->next;
    }
    
    scanf("%s %s %c", pnew->Number, pnew->Name, &pnew->Sex);
	scanf("%d %d", &pnew->Age, &pnew->Wage);
    
    pnew->next = NULL;
    p->next = pnew;
}

void DisplayList(STAFF *head){

	STAFF *pos = head;
	printf("\t职工号\t\t姓名\t性别\t年龄\t工资\n");
	while(pos->next != NULL){
		pos = pos->next;
		printf("\t%s\t%s\t%c", pos->Number, pos->Name, pos->Sex);
		printf("\t%d\t%d\n", pos->Age, pos->Wage);
		
		DEBUG("职工号字节空间：%d ", pos->Number_size);
		DEBUG("名字字节空间：%d\n", pos->Name_size);
	}

}
void Write_List_TO_File(STAFF *head, FILE *fp){
	
	STAFF *p = head;
    
	fseek(fp, 0, SEEK_SET);
	while (p->next != NULL){
		p = p->next;
		DEBUG("%d\n", sizeof(*p));
		DEBUG("%d\n", sizeof(STAFF));
		fwrite(p, sizeof(*p), 1, fp);
	}
	fclose(fp);
}
void Read_List_From_File(STAFF *head, FILE *fp){

	STAFF *p = head;

	fseek(fp, 0, SEEK_SET);
	while (!feof(fp)){
		STAFF *pnew = (STAFF *)malloc(sizeof(STAFF));
	    if (pnew == NULL){
	    	printf("申请内存出错\n");
	        exit(0);
	    }
		if(fread(pnew, sizeof(*pnew), 1, fp) == 0){
           break; 
		}
	   	while(p->next != NULL){
	       	p = p->next;
	   	}
	    pnew->next = NULL;
	    p->next = pnew;
	    p = head;
	}
	fclose(fp);
}

void Sort_List(STAFF *head){
    STAFF *a, *b, *c;
    if (head->next != NULL){
        a = head;
        b = head->next;
        c = head->next->next;
        b->next = NULL;
        while (c != NULL){
                        b = c;
            while (c->Wage < a->next->Wage && a->next->next != NULL){
                a = a->next;
			}
                        if (c->Wage < a->next->Wage && a->next->next == NULL){
                                c = c->next;
                                b->next = NULL;
                                a->next->next = b;
  						}
                        else {
                                c = c->next;
                                b->next = a->next;
                                a->next = b;
  						}
                                a = head;
  		}
 	}
}
void Insert_New_staff(STAFF *head){
    STAFF *p = head;
    STAFF *pnew = (STAFF *)malloc(sizeof(STAFF));
    if (pnew == NULL){
    	printf("申请内存出错\n");
        exit(0);
    }

    while(p->next != NULL){
        p = p->next;
    }
    printf("请按顺序输入职工号 职工名 性别(0-女 1-男) 年龄 工资\n");
    scanf("%s %s %c", pnew->Number, pnew->Name, &pnew->Sex);
	scanf("%d %d", &pnew->Age, &pnew->Wage);
    STAFF *index1 = head;
    STAFF *index2 = head->next;
    while (index2->Wage > pnew->Wage && index2 != NULL){
        index2 = index2->next;
        index1 = index1->next;
    }
    pnew->next = index2;
    index1->next = pnew;
}
void Del_Bynumber(STAFF *head, char *number){
    STAFF *index1 = head;
    STAFF *index2 = head->next;

    while (index2 != NULL && strcmp(number, index2->Number) != 0){
        index2 = index2->next;
        index1 = index1->next;
    }
    if (index2 != NULL){
        index1->next = index2->next;
        free(index2);
        index2 = index2->next;
        printf("删除成功!\n");
    }
    else{
        printf("找不到此员工,删除失败!\n");
    }
}
int main(void){
	
	STAFF *head = CreatList();

	FILE *fp1 = fopen("worker2.rec","r+");
	if (fp1 == NULL){
		printf("文件打开错误!\n");
		return 0;
	}

	Read_List_From_File(head, fp1);//读取员工信息
    DisplayList(head);
    
    printf("请输入删除员工的职工号:");
    char number[20];
    
    scanf("%s", number);
    
    Del_Bynumber(head, number);//删除员工信息
    
    DisplayList(head);
    
	fclose(fp1);
	FILE *fp2 = fopen("worker2.rec","w");
    Write_List_TO_File(head, fp2);//保存到原文件

	fclose(fp2);
    return 0;
}
