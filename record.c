#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "record.h"


//Setting Record With Values Given From Keyboard, 
//for insertion without specific format
void  setrecord( record* recptr)
{
	int studid, gpa , numofcourses , postcode ;
	char lastname[10], firstname[10], deprt[10] ;

	printf("Enter studid \n");
        scanf("%d" , &studid) ;
         printf("Enter lastname \n");
	 	scanf("%s" , lastname);
		 printf("Enter firstname \n");
    	scanf("%s" , firstname);
     	 printf("Enter department \n");
     	scanf("%s" , deprt);
     	 printf("Enter gpa \n");
     	scanf("%d", &gpa);
     	 printf("Enter number of courses \n");
     	scanf("%d", &numofcourses);
    	 printf("Enter postcode \n");
     	scanf("%d", &postcode);

	recptr->studid = studid;
	strcpy(recptr->lastname,lastname);
	strcpy(recptr->firstname,firstname);
	strcpy(recptr->deprt,deprt) ;
	recptr->gpa = gpa;
	recptr->numofcourses = numofcourses ;
	recptr->postcode = postcode ;
}

//Prints Record
void printrecord(record* recptr)
{
	printf("%d", recptr->studid);
	printf(" %s", recptr->lastname);
	printf(" %s", recptr->firstname);
	printf(" %.2f", recptr->gpa);
	printf(" %d", recptr->numofcourses);
	printf(" %s", recptr->deprt);
	printf(" %d \n", recptr->postcode);
}
