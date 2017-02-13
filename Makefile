#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= olivierid

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -g

RM= /bin/rm -f

all: shakesServer testclient olivierid_shakes PutCGI PutHTML
#all: shakesServer testclient 

testclient.o: testclient.cpp fifo.h
	$(CC) -c $(CFLAGS) testclient.cpp

shakesServer.o: shakesServer.cpp fifo.h
	$(CC) -c $(CFLAGS) shakesServer.cpp

olivierid_shakes.o: olivierid_shakes.cpp fifo.h
	$(CC) -c $(CFLAGS) olivierid_shakes.cpp

testclient: testclient.o fifo.o
	$(CC) testclient.o fifo.o -o testclient

shakesServer: shakesServer.o fifo.o
	$(CC) shakesServer.o  fifo.o -o shakesServer

fifo.o:		fifo.cpp fifo.h
		g++ -c fifo.cpp
olivierid_shakes: olivierid_shakes.o  fifo.h
	$(CC) olivierid_shakes.o  fifo.o -o olivierid_shakes -L/usr/local/lib -lcgicc

PutCGI: olivierid_shakes
	chmod 757 olivierid_shakes
	cp olivierid_shakes /usr/lib/cgi-bin/$(USER)_olivierid_shakes.cgi 

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp shakes_ajax.html /var/www/html/class/softdev/$(USER)
	cp shakes_ajax.css /var/www/html/class/softdev/$(USER)

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)

clean:
	rm -f *.o shakes_ajax shakesServer testclient
