#ifndef __RECORDS__
#define __RECORDS__

typedef struct record
{
	int studid, numofcourses, postcode;
	char lastname[10], firstname[10], deprt[10];
	float gpa;
}record;

void  setrecord( record* recptr);
void printrecord(record* recptr);

#endif
