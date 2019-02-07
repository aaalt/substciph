#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <dirent.h>

#include "../cfg/___.h"
#include "../cfg/cfg.h"

#include "../min/min.h"
#include "map.h"
#include "usr.h"
#include "../min/pnt.h"

UJ szfile(FILE *ptr)	
{
	UJ cur, size;
	if (ptr == NULL)
		R 0;
	cur = ftell(ptr);
	fseek(ptr, 0, SEEK_END);

	size = ftell(ptr);
	fseek(ptr, cur, SEEK_SET);
	R size;
}

// ext LINE_[];

I set_start(I argc, S* argv, ter_conf a)
{
	I i, size;
	FILE* ptr;

	// LEN = scnt(LINE_);
	// kbinit();
	ioctl(STDOUT_FILENO, TIOCGWINSZ, a);
	crd->map_x = 10;

	if (a->ws_col < crd->map_x + MENU_WIDTH) {
		error_message("ERROR\n", 0, "your terminal window is too narrow\n");
		O("min width: %d\n", crd->map_x + MENU_WIDTH);
		R0;
	}


	if (argc > 2) {
		error_message("ERROR\n", 0, "usage:  ./tool filename.txt\n");
		R0;
	}

	if (argc == 1) {
		LINE = LINE_;
		size = LEN;
	}
	else {

		ptr = fopen(argv[1], "r");
		if (ptr == NULL) {
			error_message("ERROR\n", 0, "file does not exist\n");
			R0;
		}
		size = szfile(ptr);

		LINE = malloc(SZ(C) * size + 1);
		fread(LINE, SZ(C), size + 1, ptr);
		fclose(ptr);
		LINE[size] = 0;
	}
	LEN = size;

	crd->line_x = 2;
	crd->line_y = 2;

	crd->map_y = lines(LINE, a->ws_col - crd->line_x*2) + crd->line_y + 2;
	crd->usr_x = 4;
	crd->usr_y = crd->map_y + 12;
	crd->err_x = 0;
	crd->err_y = crd->usr_y + 1;

	if (a->ws_row < crd->err_y) {
		error_message("ERROR\n", 0, "your terminal window is too low\n");
		O("min hight: %d\n", crd->err_y);
		free(LINE);
		R0;
	}
/*
	typedef struct Coors {
		UH line_x;			//< 4
		UH line_y;			//< 0
		UH map_x;			//<	6
		UH map_y;			//<	3
		UH usr_x;			//<	4
		UH usr_y;			//<	12
		UH err_x;			//<	0
		UH err_y;			//<	13
} pCoors;

*/
	R1;
}