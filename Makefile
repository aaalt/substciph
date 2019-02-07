all: 
	gcc -g -o tool src/lgc/bsc.c src/lgc/set.c src/min/min.c src/min/pnt.c src/lgc/map.c src/lgc/usr.c

clear: 
	rm tool 

run:
	gcc -g -o tool src/lgc/bsc.c src/lgc/set.c src/min/min.c src/min/pnt.c src/lgc/map.c src/lgc/usr.c && ./tool