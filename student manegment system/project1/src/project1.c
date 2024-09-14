/*
 ============================================================================
 Name        : project1.c
 Author      : abdelrhman adel sakr
 Version     :project1 1st file
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct student{
	int id;
	char name[50];
	int age;
	float gpa;
}student;
struct node{
	struct student data;
	struct node *next;
};
struct node *head=NULL;
struct node *current=NULL;
void insertf(struct student *data){// this function inserts a new node at the begining of the list
	struct node *link=(struct node*)malloc(sizeof(struct node));
struct node *ptr=(struct node*)malloc(sizeof(struct node));
ptr=head;
link->data=*data;
while(ptr!=NULL){
if(link->data.id==ptr->data.id){
	printf("ID is already taken\n");
	return;
}
ptr=ptr->next;
}
link->next=head;
head=link;
}
void print(void){//this function prints all the nodes in the linked list
	struct node *ptr=head;

		while (ptr!=NULL){
			printf("[");
			printf("name=%s",ptr->data.name);
			printf(" age=%d",ptr->data.age);
			printf(" gpa=%0.2f",ptr->data.gpa);
			printf(" id=%d",ptr->data.id);
			printf("]");
			ptr=ptr->next;
			printf("\n");
		}
}
void printst(int idd){//this function print the student information with the id I entered
	struct node *ptr=(struct node*)malloc(sizeof(struct node));
	ptr=head;
while(ptr!=NULL){
	if(ptr->data.id==idd){
		printf("[");
		printf("name=%s ",ptr->data.name);
					printf("age=%d ",ptr->data.age);
					printf("gpa=%0.2f ",ptr->data.gpa);
					printf("id=%d",ptr->data.id);
					printf("]");
					printf("\n");
					return;
	}
	ptr=ptr->next;

}
printf("id does not exist\n");
}
void update(int iddd){//this function updates the info of the student whom I put hia ID
	char namee[50];
	int age;
	float gpa;
	struct node *ptr=(struct node*)malloc(sizeof(struct node));
		ptr=head;
	while(ptr!=NULL){
		if(ptr->data.id==iddd){
			struct node *link=(struct node*)malloc(sizeof(struct node));
			link=ptr;
			printf("the new info for student with ID %d",iddd);
			printf("New name:");
			scanf("%s",namee);
		strcpy(link->data.name,namee);
		printf("New age:");
		scanf("%d",&age);
		printf("New GPA");
		scanf("%f",&gpa);
		return;
		}
		ptr=ptr->next;
}
	printf("id does not exist\n");
}
void avg(void){//this function calculates the average of the GPA's of all the students
	float avre=0,sum=0,count=0;
	struct node *ptr=(struct node*)malloc(sizeof(struct node));
	ptr=head;
	while(ptr!=NULL){
		sum+=ptr->data.gpa;
		ptr=ptr->next;
		count++;
	}
	avre=sum/count;
	printf("gpa average=%f\n",avre);
}
void max(void){//this function find and prints the information of the student with highest GPA
	struct node *ptr=(struct node*)malloc(sizeof(struct node));
	struct node *ptr1=(struct node*)malloc(sizeof(struct node));
	int id=0;
		int age=0;
		char nameee[50];
		ptr=head;
	ptr1=head;
	float max=ptr->data.gpa;
	while(ptr!=NULL){
		if(ptr->data.gpa>max){
			max=ptr->data.gpa;
			ptr1=ptr;
		}
		ptr=ptr->next;
	}
	printf("the maximum gpa is %f \n",max);
	age=ptr1->data.age;
	printf("the maximum gpa student age %d \n",age);
	id=ptr1->data.id;
	printf("the maximum gpa student ID is %d \n",id);
	strcpy(nameee,ptr1->data.name);
	printf("the maximum gpa student name is %s \n",nameee);

}
void delete(int iddd){//this function deletes all the student information with the ID I entered
	struct node *ptr=(struct node*)malloc(sizeof(struct node));
	struct node *ptr1=(struct node*)malloc(sizeof(struct node));
	ptr=head->next;
	ptr1=head;
	while(ptr!=NULL){
		if(ptr->data.id==iddd){
			ptr1->next=ptr->next;
			free(ptr);
			return;
		}
		ptr=ptr->next;
		ptr1=ptr1->next;
	}
	printf("the ID is invalid\n");
}
void clearInputBuffer() {//this function to end the infinte loop that I get in some cases while adding students
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {

    }
}
int main(void) {
	setvbuf(stdout,NULL,_IONBF,0);
	setvbuf(stderr,NULL,_IONBF,0);
	int choice=0;
	int newid=0;
	int id=0;
	struct student a;
	while(choice!=8){
		printf("------------------------\n");
		printf("1-add student\n2-display students\n3-search students by id\n4-update student information\n5-delete a student\n6-calculate average gpa\n7-find student with highest gpa\n8-exit\n");
		printf("enter choice:");
		scanf("%d",&choice);
		printf("------------------------\n");
		switch(choice){
		case 1://this case I add a new student with all his information
printf("enter the student id:");
while(scanf("%d",&a.id)==0){
	printf("invalid input try again");
	clearInputBuffer();
}
printf("enter the student name:");
scanf("%s",a.name);
printf("enter the student age:");
while(scanf("%d",&a.age)==0){
	printf("invalid input try again");
	clearInputBuffer();
}
printf("enter students gpa:");
while(scanf("%f",&a.gpa)==0){
	printf("invalid input try again");
	clearInputBuffer();
}
			insertf(&a);
			break;
		case 2://in this case I print all students information

print();
break;
        case 3://this case I search for a specific student and print his data
printf("enter the ID of the student you want to search for");
scanf("%d",&id);
printst(id);
break;
		case 4://this case I update a student information
printf("enter the id you want to update:");
scanf("%d",&newid);
			update(newid);
			break;
		case 5://this case I enter ID of the student that I am going to delete
			printf("enter id of the student you want to delete:");
			scanf("%d",&id);
			delete(id);
			break;
		case 6://this case I calculate the average gpa

			avg();
break;
		case 7://this case I find the student with max GPA and print his information

			max();
break;
		case 8://this case where I exit the program
			break;
		default://this in case the user put any number other than 1->8
			printf("invalid input try again\n");
		}
	}
	printf("\nyou have exited the program");
}
