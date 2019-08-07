#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chainedhashing.h"
#include "skplist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chainedhashing.h"
#include "skplist.h"

void print_menu()
{
	printf(" \n \n ");
	printf(" UNIVERSITY OPERATIONS MENU : \n");
	printf(" ------------------------------------------ \n");
	printf(" -> i(nsert) student [ex:i 176064 Patterson Denise 8.58 11 DEN 15788 ]\n");
	printf(" -> q(uery) student [ex:q 188464] \n");
	printf(" -> m(odify) student's gpa and number of courses [ex:m 144626 6.51 8]  \n");
	printf(" -> d(elete) a student [ex:d 163464]  \n");
	printf(" -> ra(verage) students of id restriction [ex:ra 148702 167447] \n");
	printf(" -> a(verage) GPA of students living in postcode [ex:a  73131]  \n");
	printf(" -> ta(verage) k top students living in that postcode [ex:ta 12 26500]  \n");
	printf(" -> b(ottom) query k students with minimum gpa [ex:b 3]  \n");
	printf(" -> ct(courses-to-take) student's gpa for people living on postcode [ex:ct 26500 POL] \n");
	printf(" -> f(ind) students with the biggest number of courser above the specific gpa [ex:f 9.00] \n");
	printf(" -> p(ercentile) of students living on postcode [ex:p 26500] \n");
	printf(" -> pe(ercentiles) of students living on each postcode [ex:pe] \n");
	printf(" -> e(xit) [ex:e] \n");

	printf(" Enter the letter for the desired operation \n ");
	printf("------------------------------------------ \n");
}


int main(int argc,char *argv[])
{
	int t;
	int arg = 0 ;
	int hashentries = 400 ;
	char operationfile[30] ;

	//gets arguments for the excecution
	for(t=0;t<argc;t++)
	{
		if ( !strcmp(argv[t],"-l") )
		{
			strcpy(operationfile,argv[t+1]);
			arg = 1;
		}
		if ( !strcmp(argv[t],"-b") )
		{
			hashentries = atoi(argv[t+1]);
		}
	}

	//printf(" %s %d \n ",operationfile,hashentries);
	record *rec ;
	srand(time(NULL));

	//creation of skiplist
	skiplist EKPA ;
	skiplist*  EKPAptr = &EKPA  ;
	initialize_skiplist(EKPAptr) ;

	//creation of hash table
	chash EKPAhash;
	chash* EKPAhashptr = &EKPAhash;
	init_chash(EKPAhashptr,hashentries);

	int studid, numofcourses , postcode ;
	char lastname[10] , firstname[10] , deprt[10] ;
	float gpa ;

	int int1,int2,int3;

	char buffer[100];
	FILE * fp;
	//decides if are going to use a file as an input or stdin
	if( arg == 1 )
	{
		fp = fopen (operationfile, "r");
	}
	else
	{
		fp = stdin ;
	}

	if( !arg )
		print_menu();

	while (fgets(buffer,sizeof buffer,fp) != NULL)
	{
		size_t len = 0;
		int n = 0;
		int ch;
		sscanf(buffer, "i %d %s %s %f %d %s %d %n",
		&studid, lastname, firstname, &gpa, &numofcourses, deprt, &postcode, &n);
		if( n )
		{
			rec = (record*)malloc(sizeof(record));
			//setrecord(rec);
			rec->studid = studid ;
			strcpy(rec->lastname,lastname);
			strcpy(rec->firstname,firstname);
			rec->gpa = gpa;
			rec->numofcourses = numofcourses ;
			strcpy(rec->deprt,deprt);
			rec->postcode = postcode ;

			rec = skiplist_insert( EKPAptr , rec->studid , rec );
			if ( rec != NULL)
				insertToHash(EKPAhashptr,rec->postcode , rec);

			if( !arg ) print_menu();
			continue;

		}
		sscanf(buffer, "q %d %n", &studid, &n);
		if( n )
		{
			printf("q %d \n",studid);
			int student_to_search = studid;
			//printf("Enter student's id to search \n");
			//scanf("%d",&student_to_search);
			rec = skiplist_search( EKPAptr , student_to_search );
			if( rec == NULL)
				fprintf(stderr,"%s","not found \n");
			else
				printrecord(rec);
			if( !arg ) print_menu();
			continue;
		}
		sscanf(buffer, "m %d %f %d %n", &studid,&gpa,&numofcourses,&n);
		if( n )
		{
			printf("m %d %.2f %d \n", studid,gpa,numofcourses);
			int student_to_search = studid;
			//printf("Enter student's id to modify \n");
			//scanf("%d",&student_to_search);
			rec = skiplist_search( EKPAptr , student_to_search );
			if(rec == NULL)
				fprintf(stderr,"%s","not found \n");
			else
			{
				float new_gpa = gpa ;
				int new_numcourses = numofcourses;
				//printf("New gpa:\n");
				//scanf("%d",&new_gpa);
				//printf("New number of courses:\n");
				//scanf("%d",&new_numcourses);
				rec->gpa = new_gpa ;
				rec->numofcourses = new_numcourses;
				printrecord(rec);
			}
			if( !arg ) print_menu();
			continue;
		}
		sscanf(buffer, "d %d %n", &studid,&n);
		if( n )
		{
			printf("d %d \n",studid);
			int student_to_search = studid ;
			int found = skiplist_delete(EKPAptr,student_to_search) ;
			//printf("Enter student's id to delete \n");
			//scanf("%d",&student_to_search);
			if ( found == 1 )
			{
				fprintf(stderr,"%s","not found \n");
			}
			else
			{
				deleteFromHash(EKPAhashptr,found,student_to_search);
			}
			if( !arg ) print_menu();
			continue;

		}
		sscanf(buffer, "ra %d %d %n",&int1,&int2,&n);
		if( n )
		{
			printf("ra %d %d \n",int1,int2);
			int studida = int1 ;
			int studidb = int2 ;
			float result ;
			//printf("Specify the id limits : \n");
			//printf("enter studida \n");
			//scanf("%d",&studida);
			//printf("enter studidb \n");
			//scanf("%d",&studidb);
			raverage(EKPAptr,studida,studidb); //number of students within range
			if( !arg ) print_menu();
			continue;
		}
		sscanf(buffer, "b %d %n",&int3,&n);
		if( n )
		{
			printf("b %d \n",int3);
			int k = int3 ;
			//printf("Enter k \n");
			//scanf("%d",&k);
			bottom(EKPAptr,int3);
			if( !arg ) print_menu();
			continue;
		}
		sscanf(buffer, "f %f %n",&gpa,&n);
		if(n)
		{
			printf("f %.2f \n",gpa);
			int new_gpa = gpa;
			//printf("Enter Gpa \n");
			//scanf("%d",&gpa);
			find(EKPAptr,new_gpa);
			if( !arg ) print_menu();
			continue ;
		}
		sscanf(buffer,"p %d %n",&int1,&n);
		if( n )
		{
			printf("p %d \n",int1);
			int postcode=int1;
			//printf("Enter Postcode \n");
			//scanf("%d",&postcode);
			percentile(EKPAhashptr ,postcode, EKPAptr->size);
			if( !arg ) print_menu();
			continue;
		}
		sscanf(buffer, "pe %n",&n);
		if( n )
		{
			printf("pe \n");
			percentiles(EKPAhashptr,EKPAptr->size);
			if( !arg ) print_menu();
			continue ;
		}
		sscanf(buffer, "ct %d %s %n" , &postcode , deprt , &n);
		if( n )
		{
			printf("ct %d %s \n",postcode,deprt);
			int postcode_to_search = postcode;
			//printf("Enter postcode \n");
			//scanf("%d",&postcode);
			//printf("Enter department \n");
			//scanf("%s",deprt);
			courses_to_take(EKPAhashptr,postcode_to_search,deprt);
			if( !arg ) print_menu();
			continue ;
		}
		sscanf(buffer, "a  %d %n",&postcode,&n);
		if( n )
		{
			printf("a %d \n",postcode);
			int key;
			key = postcode ;
			//printf("Enter postcode \n");
			//scanf("%d",&postcode);
			average(EKPAhashptr,key);
			if( !arg ) print_menu();
			continue;
		}
		sscanf(buffer,"ta %d %d %n",&int1,&postcode,&n);
		if( n )
		{
			printf("ta %d %d \n",int1,postcode);
			int postcode_to_search = postcode ;
			int k = int1;
			//printf("Enter postcode \n");
			//scanf("%d",&postcode);
			//printf("Enter k\n");
			//scanf("%d",&k);
			taverage(EKPAhashptr,postcode_to_search,k);
			if( !arg ) print_menu();
			continue ;
		}
		sscanf(buffer,"e %n",&n);
		if( n )
		{
			printf("e \n");
			destroy_skiplist(EKPAptr);
			destroy_hash(EKPAhashptr);
			break;
		}
	}
}
