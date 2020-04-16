/*
17211164125 阿卡丽 79 73 90
17211164126 阿木木 83 73 92
17211164127 奥恩 67 88 83
17211164128 艾克 90 93 93
17211164129 潘森 88 74 74
*/
#include <stdio.h>
#include <stdlib.h>
struct SCORE{
	int Chinese;
	int Math;
	int English;
	int Sum;
	int Ave;
};
typedef struct STUDENT{
	char Number[20];
	char Name[20];
	struct SCORE Score;
	struct STUDENT *next;
}NODE;

NODE *CreatList(){
	
	NODE *head = (NODE *)malloc(sizeof(NODE));
	if (head == NULL){
		exit(0);
	}
	head->next = NULL;

	return head;
}
NODE *AddList(NODE *head){
	
	NODE *p = head;
	NODE *pnew = (NODE *)malloc(sizeof(NODE));
	if (pnew == NULL){
		exit(0);
	}
	while (p->next != NULL){
		p = p->next;
	}
	scanf("%s %s", pnew->Number, pnew->Name);
	scanf("%d %d %d", &pnew->Score.Chinese, &pnew->Score.Math ,&pnew->Score.English);
	pnew->Score.Sum = pnew->Score.Chinese + pnew->Score.Math + pnew->Score.English;
	pnew->Score.Ave = pnew->Score.Sum / 3;
	
	pnew->next = NULL;
	p->next = pnew;
}
void DisplayList(NODE *head){
	
	NODE *p = head;
	printf("\t学号\t\t姓名\t语文\t数学\t英语\t总分\t平均分\n");
	while (p->next != NULL){
		p = p->next;
		printf("\t%s\t%s", p->Number, p->Name);
		printf("\t%d\t%d\t%d", p->Score.Chinese, p->Score.Math ,p->Score.English);
		printf("\t%d\t%d\n", p->Score.Sum, p->Score.Ave);
	}
}


void DestroyList(NODE **head){
	
	NODE *p = *head;
	while ((*head)->next != NULL){
		p = (*head)->next;
		
		(*head)->next = p->next;
		free(p);
	}
	free(*head);
	*head = NULL;
}
void SaveFile(NODE *head, FILE *fp){
	
	NODE *p = head;
	while (p->next != NULL){
		p = p->next;
		fprintf(fp, "%s %s ", p->Number, p->Name);
		fprintf(fp, "%d %d %d ", p->Score.Chinese, p->Score.Math ,p->Score.English);
		fprintf(fp, "%d %d\n", p->Score.Sum, p->Score.Ave);
	}
}
void ReadFile(NODE *head, FILE *fp){
	
	NODE *p;
//	fseek(fp, 0, SEEK_SET);
	int n = 5;
	while (n--){
		p = head;
		while (p->next != NULL){
			p = p->next;
		}
		NODE *pnew = (NODE *)malloc(sizeof(NODE));
		if (pnew == NULL){
			exit(0);
		}
		fscanf(fp,"%s %s", pnew->Number, pnew->Name);
		fscanf(fp,"%d %d %d ", &pnew->Score.Chinese, &pnew->Score.Math, &pnew->Score.English);
		fscanf(fp,"%d %d", &pnew->Score.Sum, &pnew->Score.Ave);

		pnew->next = NULL;
		p->next = pnew;
	}

}

int main(){
/*	
	FILE *fp = fopen("stud.rec", "w");
	if (fp == NULL){
		perror("打开文件时发生错误!");
		return -1;
	}
	NODE *head = CreatList();
	int n = 5;
	printf("请按顺序输入学号,姓名;语文,数学,英语的成绩\n");
	while (n--){
		AddList(head);
	}
	SaveFile(head, fp);
	DisplayList(head);
	fclose(fp);
	DestroyList(&head);
*/

	FILE *fp2 = fopen("stud.rec", "r");
	if (fp2 == NULL){
		perror("打开文件时发生错误!");
		return -1;
	}
	NODE *head2 = CreatList();
	
	ReadFile(head2, fp2);
	DisplayList(head2);
	
	fclose(fp2);
	DestroyList(&head2);

	return 0;
}
