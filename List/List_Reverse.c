#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
	char name[20];
	int date;
	struct node *next;
}NODE;

NODE *CreatList_headnode(){
	
	NODE *head = (NODE*)malloc(sizeof(NODE));
	if (head == NULL){
		exit(0);
	}
	head->next = NULL;
	
	return head;
}
void AddList_tailnode(NODE *head, const char *name, int date){   //尾部插入

	NODE *pos = head;
	NODE*pnew = (NODE*)malloc(sizeof(NODE));
	
	if (pnew == NULL){
		exit(0);
	}

    strcpy(pnew->name, name);
	pnew->date = date;
	
	while (pos->next != NULL){
		pos = pos->next;
	}
	
	pnew->next = NULL;
	pos->next = pnew;
 
 	
}
void DisplayList(NODE *head){
	
	NODE *pos = head;
	
	while(pos->next != NULL){
		pos = pos->next;
		printf("%s %d\n", pos->name, pos->date);
	}
	
}
void DeleteNode_Bydate(NODE *head, int date){
	
	NODE *index1 = head;
	NODE *index2 = head->next;

	while (index2 != NULL){
		if (index2->date == date){
			index1->next = index2->next;
			free(index2);
			index2 = index1->next;
		}
		else{
			index1 = index1->next;
			index2 = index2->next;
  		}
	}
	
}

void InsertList_Bydate(NODE *head, const char *name, int date){
	
	NODE *index2 = head->next;
	NODE *index1 = head;
	
	NODE *pnew = (NODE*)malloc(sizeof(NODE));
	if (pnew == NULL){
        exit(0);
 	}
 	
 	strcpy(pnew->name, name);
	pnew->date = date;
	
	while (index2 != NULL && index2->date < date ){
			index1 = index1->next;
			index2 = index2->next;
	}
	pnew->next = index2;
	index1->next = pnew;
	
}
void ClearList(NODE *head){

	NODE *pos = head;
	
	while (pos->next != NULL){
		pos = pos->next;
		free(pos);
	}

}
void DestoryList(NODE **head){


	ClearList(*head);
	
	free(*head);
	*head = NULL;
}
NODE *MergeList(NODE *head1,NODE *head2){

	NODE *newhead = head1;
	NODE *pos = newhead;
	NODE *index1 = head1->next;
	NODE *index2 = head2->next;

	while (index1 != NULL && index2 != NULL){
		if (index1->date <= index2->date){
			pos->next = index1;
			index1 = index1->next;
		}
		else {
			pos->next = index2;
			index2 = index2->next;
		}
		pos = pos->next;
	}

	if (index1 == NULL){
		pos->next = index2;
	}
	if (index2 == NULL){
		pos->next = index1;
	}
	
	return newhead;
}
void List_reverse(NODE *head){

	NODE *a,*b,*c;
	a = head;
	b = a->next;
	c = b->next;

	b->next = NULL;
	b = c;
	a = a->next;
	c= b->next;
	while (c != NULL){
		b->next = a;
		a = a->next;
		b = c;
		c = c->next;
    }
    b->next = a;
    
	head->next = b;

}
int main(){

	NODE *head = CreatList_headnode();

	AddList_tailnode(head, " ",8);
	AddList_tailnode(head, " ",7);
	AddList_tailnode(head, " ",6);
	AddList_tailnode(head, " ",5);
	AddList_tailnode(head, " ",4);
	AddList_tailnode(head, " ",3);
	AddList_tailnode(head, " ",2);

	printf("链表:\n");
	DisplayList(head);
	
	List_reverse(head);
	printf("逆序:\n");
	DisplayList(head);

	DisplayList(head);
	return 0;
}
