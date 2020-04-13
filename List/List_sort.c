#include <stdio.h>
#include <stdlib.h>
typedef struct NODE{
    int date;
    struct NODE *next;
}NODE;
NODE *CreatList(){
    NODE *head = (NODE *)malloc(sizeof(NODE));
    if (head == NULL){
        exit(0);
    }
    head->next = NULL;

    return head;
}
void AddList(NODE *head, int date){
    NODE *pnew = (NODE *)malloc(sizeof(NODE));
    if (pnew == NULL){
        exit(0);
    }
    pnew->date = date;
    NODE *p = head;
    while (p->next != NULL){
        p = p->next;
    }
    pnew->next = NULL;
    p->next = pnew;
}
  
void DisplayList(NODE *head){
    NODE *p;
    p = head->next;
    while (p != NULL){
        printf("%d\n", p->date);
        p = p->next;
    }
}

void Sort_List(NODE *head){
    NODE *a, *b, *c;
    if (head->next != NULL){
        a = head;
        b = head->next;
        c = head->next->next;
		b->next = NULL;
        while (c != NULL){
			b = c;	
            while (c->date > a->next->date && a->next->next != NULL){
                a = a->next;
            }
			if (c->date > a->next->date && a->next->next == NULL){
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
int main(void){
    NODE *head = CreatList();
    AddList(head, 5);
    AddList(head, 4);
    AddList(head, 8);
    AddList(head, 2);
    AddList(head, 1);
    AddList(head, 9);
    DisplayList(head);
	printf("\n");
    Sort_List(head);
    DisplayList(head);
	DestoryList(&head);
    return 0;
}
