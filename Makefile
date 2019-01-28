all: 
	gcc -g -o tool src/bsc.c src/map.c src/usr.c src/min.c && ./tool

clear: 
	rm tool 

run:
	./tool