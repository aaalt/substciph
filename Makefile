all: 
	gcc -g -o tool src/bsc.c src/map.c src/usr.c src/min.c

clear: 
	rm tool 

run:
	./tool