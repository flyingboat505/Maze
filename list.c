/*
   Abhilash Munnangi
   This program is used for a circular doubly-linked list with a dummy node. The dummy node is used to shorted writting the code.This will be used to implement a given maze game, which uses a stack so that the robot can back track itself
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

//Creating the node
struct node{
	void *data;
	struct node *next;
	struct node *prev;
 };

struct list{
	int count;
	struct node *head; 
	int (*compare)();
};

/*this function returns a pointer to a new list by using the compare,a client given function
creating the list as well "*compare"-creates a pointer and points it to the function  */ 
//run time is O(1)
LIST *createList(int(*compare)()){
	
	//creating the dummy node and returning a point to the dummy node
	struct node *dummy;
	dummy=malloc(sizeof(struct node));//check with TA if syntax correct
	assert(dummy!=NULL);
	dummy->next=dummy;//check with TA
	dummy->prev=dummy;
	
	/*now we need to malloc a list node 
	then have pointer to "->" next equal to NULL;
	then have list pointer point to the dummy node
	*/
	struct list *lp;
	lp=malloc(sizeof(struct list));
	assert(lp!=NULL);
	lp->compare=compare;//ask ta why is this
	lp->head=dummy;
	lp->count=0;
	return lp;
}

/*this function will destroy the list by decllocting all the memory associated with it
  Run time is O(n) */ 
void destroyList(LIST *lp){
	while(lp->count!=0){
		removeFirst(lp);
	}
    free(lp->head);
	free(lp);
  }

//This function returns the number of items in the  list pointed to by lp
//O(1)
int numItems(LIST *lp){
	return lp->count;

}


/*this function adds items as the first item in the list pointed to by lp
  Run Time is O(1) */
void addFirst(LIST *lp,void *item){

	struct node *temp;
	temp=malloc(sizeof(struct node));
	assert(temp!=NULL);
	temp->data=item;

	temp->next=lp->head->next;
	temp->prev=lp->head;
	lp->head->next->prev=temp;
	lp->head->next=temp;
	lp->count++; //correct syntax?
}

/*this function add  items as the last item in the list pointed to by lp
  Run Time is O(1) */
void addLast(LIST *lp,void *item){

	struct node *temp;
	temp=malloc(sizeof(struct node));
	assert(temp!=NULL);
	temp->data=item;

	temp->prev=lp->head->prev;
	temp->next=lp->head;
	lp->head->prev->next=temp;
	lp->head->prev=temp;
	lp->count++; //correct syntax?
}

/*this function removes items as the first  item in the list pointed to by lp and returns the data inside the pointer
  (again we don't care what the actual data is) 
  Run Time is O(1) */
void *removeFirst(LIST *lp){
	assert(lp!=NULL && lp->head->next!=lp->head);
	struct node *p,*dummy,*third;
	void *temp;
	p=lp->head->next;
	dummy=lp->head;
	third=lp->head->next->next;

	dummy->next=dummy->next->next;
	third->prev=third->prev->prev;
	lp->count--;//right syntax?? 

	temp=p->data; 
	free(p);
	return temp;
}


/*this function removes items as the last item in the list pointed to by lp
  Run Time is O(1) */
void *removeLast(LIST *lp){
	assert(lp!=NULL && lp->head->next!=lp->head);
	struct node *p,*dummy,*third;
	void *temp;
	p=lp->head->prev;
	dummy=lp->head;
	third=lp->head->prev->prev;

	dummy->prev=dummy->prev->prev;
	third->next=third->next->next;
	lp->count--;//right syntax?? 

	temp=p->data; 
	free(p);
    
	return temp;
}

/*this function returns the first item in the list
  Run Time is O(1) */
void *getFirst(LIST *lp){

	assert(lp!=NULL);
	return lp->head->next->data;

}
/*this function returns the last item in the list
  Run Time is O(1) */
void *getLast(LIST *lp){
	assert(lp!=NULL);
	return lp->head->prev->data;	
}

/*This function finds the item that is present and returns the node =
  runtime is O(n)
*/
struct node *search(LIST *lp,void *item){
    struct node *p;
    p=lp->head->next;
    while(p!=lp->head){
        if((*lp->compare)(p->data,item)==0){
            return p;
        }
        p=p->next;
    }
    return NULL;
}

//This function finds the item that is present and removes it
//O(1)/O(n) run time
void removeItem(LIST *lp,void *item){
	//fprintf(stderr,"Remove item called.\n");
	assert(lp!=NULL ); //case 1, list is pointing to no dummy node
    struct node *p;
    p=search(lp,item);
    if(p!=NULL){
        p->prev->next=p->next;
        p->next->prev=p->prev;
        free(p);
        lp->count--;
        return;
    }
//	fprintf(stderr,"Item not found\n");
	return;
}


//this function finds the item that is present and returns the data.
//O(n)
void *findItem(LIST *lp,void *item){
  
	assert(lp!=NULL);
	struct node *Dummy,*p;
	Dummy=lp->head;
	p=Dummy->next;
  
	while(p!=Dummy){
     
		fprintf(stderr,"Find item %s \n",(char*)p->data);
		if((*lp->compare)(p->data,item)==0){
    
            return p->data;
		}
		p=p->next;
        
		fprintf(stderr,"found  item  \n");
        
	}
  
	return NULL;
}


//This functions allocates and retruns an array of items in the list pointed to by lp
// O(n) 
void *getItems(LIST *lp){
	fprintf(stderr,"GetItems Enter \n");
	int i=0; 
	assert(lp!=NULL);
	struct node *Dummy,*p;
	Dummy=lp->head;
	p=Dummy->next;
	char **array=malloc(sizeof(void*)*lp->count);
	while(p!=Dummy){
		array[i]=p->data;
		p=p->next;
		i++;
	}
	fprintf(stderr,"GetItems Return \n");
	return array;
}
  
