/*Abhilash Munnangi
   
   This ADT is similar to the string ADT. HOwever, now we can accept anydata type as we are not constrained to generic pointers any more. However,the client is responsible for managing memory in the system. This is the price to pay .

Since we are not contrained to strings, we cannot use strcmp or strhash becaus those functions are for strings. 

Rather we have to use the client given functions. 
*/

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "set.h"
#include "list.h"

#define AVG_LENGTH 20

//this structure set, contains count,length,data, and flags
//changing data type of "data" to void as well as taking out the two ** so the array of pointers are not needed.
struct set{
	int count;//number of elements
	int length; //numbers
	LIST **list; 
//	int *flags; //array of values that are first pointed by flags
	int (*compare)();//client function
	unsigned(*hash)();//client functions
};

//This function creates the SET
//the run time is Big O(N)
//now we are passing in the client given functions 
//returns a pointer to the set
SET *createSet(int maxElts,int (*compare)(),unsigned (*hash)()){
		int i;
		SET *sp;
		sp=malloc(sizeof(SET));
		assert(sp!=NULL);
		sp->count=0;
		//length is the number of linked list in has table. On average it is 20
		sp->length=maxElts/AVG_LENGTH;
		sp->list=malloc(sizeof(char*)*maxElts);
		assert(sp->list!=NULL);
		sp->compare=compare;
		sp->hash=hash;
		//now that we created a pointer to array of pointers, we now need to initilize each element 
		for(i=0;i<sp->length;i++){
			sp->list[i]=createList(compare);
		}
		return sp;
}

//this returns the number of elements in the set pointed to by sp
//O(1)
int numElements(SET *sp){
		assert(sp!=NULL);
		return(sp->count); 
}

//this function will destroy the set as well as the circular linked lists
//the run time worst case is O(N)
void destroySet(SET *sp){
		int i;
		//destroy all circular lists as well as the struct list
		for(i=0;i<sp->length;i++){
			destroyList(sp->list[i]);
		}
		free(sp->list);
		free(sp);
			 //up to here
}

//thus function adds elt from the set pointed to by sp
//if found element is not in the actual linked list, then we can add the element 
//run time is O(1)/O(n)
void addElement(SET *sp,void *elt){
	//find the key
	//Go to array index
	//Call the find item function, if not found call the Add item function
	assert(sp!=NULL);
	assert(elt!=NULL);
    int key=(*sp->hash)(elt)%sp->length;//CHECK KEY
	if(findItem(sp->list[key],elt)==NULL){//CHECK
		addFirst(sp->list[key],elt);//CHECK SYNTAX
		sp->count++;//CHECK
	}
	return;
	
}

//This function removes the element in the circular linked list 
//The run time of this is O(1)/O(n) 
void removeElement(SET *sp,void *elt){
	assert(sp!=NULL);
	assert(elt!=NULL);
	int key=(*sp->hash)(elt)%sp->length;//CHECK KEY
    void *data=findItem(sp->list[key],elt);
	if(data!=NULL){
        fprintf(stderr,"Item is found \n");
		removeItem(sp->list[key],elt);
		sp->count--;
		fprintf(stderr,"Remove found complete \n");
        return;
	}
} 

//This function will find an Element in the linked list and retuns the actial value
//the Run time for this is O(1)/O(n)
void *findElement(SET *sp,void *elt){

	fprintf(stderr,"Attempt to Find Element \n");
		assert(sp!=NULL);
		assert(elt!=NULL);
	    int key=(*sp->hash)(elt)%sp->length;//CHECK KEY
		if(findItem(sp->list[key],elt)!=NULL){
		fprintf(stderr,"Attempt to Find ElementSucess \n");
			return findItem(sp->list[key],elt); //CHECK THIS
		}
	fprintf(stderr,"Attempt to Find Element Not Sucess \n");
		return NULL;
}
//This function will get the elements and return an array of elements in the set pointed by sp, for a particular element
//the worst case run time is O(n), this is because strdup is O(n) while  the travel time for the look is O(n)
void *getElements(SET *sp){

		fprintf(stderr,"GET enter \n");
		assert(sp!=NULL);
		int i;
		int j;
		int lim;
		int q=0;
		void **toret = malloc(sizeof(void*)*sp->length*AVG_LENGTH);
		assert(toret != NULL);
		void **data;

		for(i=0;i<sp->length;i++)
		{
	   		data = getItems(sp->list[i]);
			lim = numItems(sp->list[i]);
			for(j=0;j<lim;j++){
				toret[q+j] = data[j];
			}
			q+=numItems(sp->list[i]);
		}
		
		fprintf(stderr,"GET Toret \n");
		return toret;
}

