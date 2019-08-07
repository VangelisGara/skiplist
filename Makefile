#
# In order to execute this "Makefile" just type "make"
#	A. Delis (ad@di.uoa.gr)
#

OBJS 	= stucs.o skplist.o chainedhashing.o record.o
SOURCE = stucs.c skplist.c chainedhashing.c record.c
HEADER = skplist.h chainedhashing.h record.h
OUT  	= stucs
CC	= gcc
FLAGS   = -g -c 
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files >>separately<< 
stucs.o: stucs.c
	$(CC) $(FLAGS) stucs.c

skplist.o: skplist.c
	$(CC) $(FLAGS) skplist.c

chainedhashing.o: chainedhashing.c
	$(CC) $(FLAGS) chainedhashing.c

record.o: record.c
	$(CC) $(FLAGS) record.c


# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)


