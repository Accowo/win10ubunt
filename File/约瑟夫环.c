#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
	int number;
	struct node *next;
}NODE;

NODE *CreatList_headnode(){

	NODE *head = (NODE*)malloc(sizeof(NODE));
	if (head == NULL){
		exit(0);
	}
	head->number = 1; //第一个人的编号
	head->next = head;//一个人的环

	return head;
}
void AddList_Cycle(NODE *head ,int number){   //尾部插入

	NODE *pos = head;
	NODE *pnew = (NODE*)malloc(sizeof(NODE));

	if (pnew == NULL){
		exit(0);
	}

	pnew->number = number;

	while (pos->next != head){
		pos = pos->next;
	}

	pnew->next = head;
	pos->next = pnew;

}

NODE *Del(NODE *head, int number){

	NODE *index1 = head;
	NODE *index2 = head->next;

	while (1){
		if (index2->number == number){
			index1->next = index2->next;
			free(index2);
			index2 = index1->next;
			return index2;
		}
        else {
            index1 = index1->next;
            index2 = index2->next;
        
        }
        
	}
}

void DestoryList(NODE **head){  //形参二级指针,一级指针无法改变head的指向
	NODE *p = *head;
	while ((*head)->next != *head){
		p = (*head)->next;
		(*head)->next = p->next;
		free(p);
	}
	free(*head);
	*head = NULL; //使head指向NULL,
}
int main(){

	NODE *head = CreatList_headnode();
	int i;
	int j = 0;  //报数
	int n; //总人数
	int k;  //报数数
    printf("请输入总人数:");
    scanf("%d", &n);
    printf("请输入报到数:");
    scanf("%d", &k);

	for (i = 2; i <= n; i++){
		AddList_Cycle(head, i);
	}
	
	NODE *p1 = head;
	NODE *p2 = head->next;
	
	while (head->next != head){
		j++;
		if (j == k){
			j = 0;
			printf("%d ", p1->number);
			head = Del(head, p1->number);
		}
		p1 = p2;
		p2 = p2->next;
	}
	printf("\n存活者编号:%d\n", head->number);
	DestoryList(&head);
	return 0;
}
