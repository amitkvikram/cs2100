/*
 * Problem Name:Ex4.c
 * Programmer's Name: Amit Vikram Singh
 * Roll No.: 111601001
 * Email-id: 111601001@smail.iitpkd.ac.in
 * Date: 01/08/2017
 */

#include<stdio.h>
#include<stdlib.h>

struct CLLNode{
	int data;
	struct CLLNode *next; //Pointer to next node in Circular linked list
};


typedef struct CLLNode Node; //setting alias "Node" for "struct CLLNode"

void insert(Node **Headptr){ //Headptr is a pointer to the "Head pointer"
       printf("Enter number of nodes you want to insert: ");
       int n, i;   //n is  number of nodes user wants to insert in list
       scanf("%d",&n);
       printf("Enter %d nodes you want to insert: ",n);
       for(i=0;i<n;i++){
	       int tempData;
               scanf("%d",&tempData);
	       Node *temp= (Node*)malloc(sizeof(Node));  //Dynamically allocating Memory, memory block is pointed by pointer "Node"
	       temp->data=tempData;
	       if(*Headptr==NULL){  
		       *Headptr=temp;
		       temp->next=*Headptr;
	       }

	       else{
			temp->next=*Headptr;
			Node*tempptr= *Headptr;
			while(tempptr->next!=*Headptr){
				tempptr=tempptr->next;
			}

			tempptr->next=temp;
	       }
       }
    

}

void Printlist(Node **Headptr){  //Headptr is a pointer to pointer "Head"
      Node *tempptr=*Headptr;
      if(*Headptr==NULL){  //Checking if list is empty
	      printf("List is EMPTY\n");
	      return;
      }

      while(tempptr->next!=*Headptr){   //traversing through list and printing value of each node
	      printf("%d ", tempptr->data);
              tempptr=tempptr->next;
      }

      printf("%d\n",tempptr->data);
}
		
void search(Node **Headptr){
	printf("Enter the value of node you want to search: ");  //Prompting user to input the value he/she wants to search in list
	int tempData;
	scanf("%d",&tempData);
    Node *tempptr=*Headptr;
    int index=0;
    while(tempptr!=NULL){
        if(tempptr->data!=tempData){ tempptr=tempptr->next;
        index++;
    }
        else {
            index++;
            break;   //breaks the loop if data is found in linked list
        }
    }
   
    if(tempptr==NULL){ 
        printf("Value not found in list\n");
        return;
    }

    printf("Value found at position: %d\n",index);
}


int main(){
	Node *Head;
	Head= NULL;
	insert(&Head);      //Passing address of Head to insert function, insert function inserts nodes in list
        Printlist(&Head);  //Passing address of Head to Printlist function
        search(&Head);  //Passing adress of Head to search function, search function searches a node in linked list and prints its index 
       	return 0;
}

