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
int main(void){
	
	STAFF *head = CreatList();

	FILE *fp1 = fopen("worker1.rec","r");
	if (fp1 == NULL){
		printf("文件打开错误!");
		return 0;
	}
	Read_List_From_File(head, fp1);
    Sort_List(head);

	FILE *fp2 = fopen("worker2.rec","w");
	if (fp2 == NULL){
		printf("文件打开错误!");
		return 0;
	}
    Write_List_TO_File(head, fp2);
	DisplayList(head);
	fclose(fp1);
	fclose(fp2);
    return 0;
}
