//  		        	 	1=1
//					2=10			3=11
//			4=100		5=101	6=110		7=111
// In this program i tried to use the seuence of numbers to insert and delete
// the first '1' in the binary to start.
// after '1' means go to the left and '0' go to the right.	
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "patientqueue.h"
int N = 1;
int bin[30];
struct q {
	Patient *p;
	PatientQueue *left, *right;
};	
//B tree

PatientQueue *newPQ(int size) {
	return NULL;
}
// to create a binary number
// it is a reversed one now(we will be traversing it from the top to the bottum.)
int binary(int n){
    int top = 0;
	for (top = 0;n>0;top++){
		bin[top] = n%2;
        n = n /2;
	}
	for(int i = top-1;i>=0;i--)
		printf("%d",bin[i]);
	return top;
}		

void swap(Patient* p1, Patient* p2){
	Patient temp = *p1;
	*p1	= *p2;
	*p2 = temp;
}
void heapify(PatientQueue* root,PatientQueue* pre,int n){
	if(root->right == NULL && root->left == NULL)
		return;
	if(bin[n] == 0 && root->right != NULL){
		heapify(root->right,root,n-1);
		if(root->p->severity <= root->right->p->severity){
			swap(root->p,root->right->p);
		}
	}else if (root->left != NULL){	
		heapify(root->left,root,n-1);
		if(root->p->severity <= root->left->p->severity){
			swap(root->p,root->left->p);
		}
	}
}
PatientQueue* insert(PatientQueue* root, PatientQueue* new, int i){
	if(root == NULL)	
		return new;
	if(bin[i] == 0){
		root->right = insert(root->right,new,i-1);
        if(root->p->severity < root->right->p->severity){
			swap(root->p,root->right->p);
		}
    }else{
		root->left = insert(root->left,new,i-1);
        if(root->p->severity < root->left->p->severity){
			swap(root->p,root->left->p);
	    }
    }
	return root;
}	
// Append in a heap.
PatientQueue *PQAppend(PatientQueue *q, Patient *p) {
	PatientQueue *newq = (PatientQueue *) malloc(sizeof(PatientQueue));
	int n = N;
	int top;
	newq->p = p;
	newq->right = newq->left = NULL;

	if(PQEmpty(q)){
		N++;
		return newq;
	} 
	// create a binary number of counter.
    top = binary(n);
	// top - 2 because the elements is from 0 to top-1 and the other -1 is for the first digit 1 to be taken out
	q = insert(q,newq,top-2);
//	heapify(q,q,top-2);
	N++;
	return q;
}	
//This functions heapifies the tree after deleting the "peak"
void heapifydelete(PatientQueue* root,PatientQueue* pre){
	if(root->right == NULL && root->left == NULL)
		return;
	// in case the there is only one leaf
	if(root->right != NULL && root->left == NULL){
		if(root->p->severity < root->right->p->severity){
			swap(root->p,root->right->p);
		}
		heapifydelete(root->right,root);
		
	}else if (root->left != NULL && root->right == NULL){	
		if(root->p->severity <= root->left->p->severity){
			swap(root->p,root->left->p);
		}
		heapifydelete(root->left,root);
		
	}else{// we have both leafs.
		if(root->right->p->severity >= root->left->p->severity){
			swap(root->p,root->right->p);
			heapifydelete(root->right,root);
		}else{
			swap(root->p,root->left->p);
			heapifydelete(root->left,root);
		}
	}
}	

// this functions return the last patient by reference.
PatientQueue* returnLast(PatientQueue* root,Patient** p,int i){
	if(root->left == NULL && root->right == NULL){
		*p = root -> p;
		root = NULL;
		return root;
	}	
	if(bin[i] == 0)
		root->right = returnLast(root->right,p,i-1);
	else
		root->left = returnLast(root->left,p,i-1);
	return root;
}						
			
Patient *PQMaxServe(PatientQueue **root){
	if(PQEmpty(*root)) return NULL;
	else {
		Patient * patient;
		Patient* itemToReturn;
		int top;
		int n = N -1;
		if ((*root)->right == NULL && (*root)->left == NULL){
			itemToReturn = (*root)->p;
			*root = NULL;
		}else {
			top = binary(n);
			itemToReturn = (*root)->p;
			*root = returnLast(*root,&patient,top-2);
			(*root) -> p = patient;
			heapifydelete(*root,*root);
		}
		N--;
		return itemToReturn;
	}
}
void print(PatientQueue * root,int n){
	if(root == NULL )return;
	print(root->left,n+1);
	for (int i = 0;i<n;i++)	
		printf("\t");

	printf("%s\n",root->p->name);
	print(root->right,n+1);
}
// Print a binary tree
// FINISHED
void printPQ(PatientQueue * root) {
	print(root,0);
	printf("\n");
}

int PQEmpty(PatientQueue *q) {
	return q == NULL;
}

int PQFull(PatientQueue *q){
	return 0;
}