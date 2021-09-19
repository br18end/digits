/*

 * C Program to Implement a Queue using an Array

 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 10
int queue_array[MAX];
int rear = - 1;
int front = - 1;
void insert();
void delete();
void display();

void insert(int add_item){
    if (rear == MAX - 1){
        delete();
    }
    else {
        if (front == - 1) /*If queue is initially empty */
            front = 0;
        rear = rear + 1;
        queue_array[rear] = add_item;
   }
} /*End of insert()*/


void delete(){
    if (front == - 1){
        printf("Queue Underflow \n");
        return ;
    }
    else{front = front + 1;}
} /*End of delete() */


void   display(){
    int i;
    if (front == - 1)
        printf("Queue is empty \n");
    else{
        for (i = front; i <= rear; i++)
            printf("%d ", queue_array[i]);
    }
} /*End of display() */
