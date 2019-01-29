#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "cfg.h"

#include "min.h"
#include "map.h"

ext coor crd;
ext I IM;

V clear_user_input()				//< clear line with y == usr_y
{
	// O("clear_user_input [usr.c]\n");

	clear_line(crd->usr_y);
	gotoxy(crd->usr_x, crd->usr_y);
	O(" ::_");
	fflush(stdout);
}

V hide_map()						//< clear five lines at y == map_y; x == map_x
{
	for (I i = 0; i < crd->usr_y - crd->map_y; i++) 
		clear_line(crd->map_y + i);
}

V show_help()						//< five lines at y == map_y; x == map_x
{
	hide_map();
	gotoxy(crd->map_y, crd->map_x);
	O("\t'!'    --->  help");
	gotoxy(crd->map_y + 1, crd->map_x);
	O("\t'q'    --->  quit");
	gotoxy(crd->map_y + 2, crd->map_x);
	O("\t'a''b' --->  swap each 'a' with 'b'");
	gotoxy(crd->map_y + 3, crd->map_x);
	O("\t'm'    --->  show map");
	gotoxy(crd->map_y + 4, crd->map_x);
	O("\t'h'    --->  hide map");
	gotoxy(crd->map_y + 5, crd->map_x);
	O("\t'i'    --->  show importants");
	gotoxy(crd->map_y + 6, crd->map_x);
	O("\t'*str' --->  highlight str");

	gotoxy(crd->map_y + 8, crd->map_x);
	O("\t* if you want to replace for ex. 'a' with");
	gotoxy(crd->map_y + 9, crd->map_x);
	O("\t  used 'b', just do ::_ bx than ::_ ba");
	fflush(stdout);
}

V print_valids(S alph)
{
	I j;
	C i, c = 0;
	gotoxy(crd->map_y + 6, crd->map_x);
	O("valids:    ");
	for (i = 0; i < 26; i++) {
		c = 0;
		for (j = 0; j < 26; j++) {
			if (alph[j] == (i + 'a')) {
				c = 1;
				j = 26;
			}
		}
		if (!c)
			O("%c   ", (i + 'a'));
	}
}

V show_map(S alph)					//<	five lines at y == map_y; x == map_x
{
	I i;
	hide_map();
	gotoxy(crd->map_y, crd->map_x);
	O("cipher|    ");
	for (i = 0; i < 6; i++)
		O("%c  ", 'a' + i);
	O("    ");
	for (i = 0; i < 7; i++)
		O("%c  ", 'a' + i + 6);
	O("    |cipher");

	gotoxy(crd->map_y + 1, crd->map_x);
	O("origin|    ");
	for (i = 0; i < 6; i++) {
		if (alph[i])
			O("%c  ", alph[i]);
		else 
			O("*  ");
	}
	O("    ");
	for (i = 0; i < 7; i++) {
		if (alph[i + 6])
			O("%c  ", alph[i + 6]);
		else 
			O("*  ");
	}
	O("    |origin");

	gotoxy(crd->map_y + 3, crd->map_x);
	O("cipher|    ");
	for (i = 0; i < 6; i++)
		O("%c  ", 'n' + i);
	O("    ");
	for (i = 0; i < 7; i++)
		O("%c  ", 'n' + i + 6);
	O("    |cipher");

	gotoxy(crd->map_y + 4, crd->map_x);
	O("origin|    ");
	for (i = 0; i < 6; i++) {
		if (alph[i + 13])
			O("%c  ", alph[i + 13]);
		else 
			O("*  ");
	}
	O("    ");
	for (i = 0; i < 7; i++) {
		if (alph[i + 19])
			O("%c  ", alph[i + 19]);
		else 
			O("*  ");
	}
	O("    |origin");

	print_valids(alph);

	MAP = 1;
}



V show_importants(S* ptr, S alph)
{
	I i, j, k = 0;

	hide_map();
	gotoxy(crd->map_y, crd->map_x);
	for (i = 0; i < IM; i++) {

		for (j = 0; ptr[i][j] != ' ' && ptr[i][j] != ',' && ptr[i][j] != '.'; j++)
			O("%c", ptr[i][j]);
		O("\t");
		fflush(stdout);
		if (!((i + 1)%3)) {
			k++;
			gotoxy(crd->map_y + k, crd->map_x);
		}
	}

	print_valids(alph);
}


V highlight(S str, I y, I x)
{
	I i;
	gotoxy(y, x);
	O("%s%s%s", "\e[4m", str, "\e[24m");
	fflush(stdout);
}

V highlighted_line(S line, S str)
{
	I i, j, l_len = scnt(line), s_len = scnt(str), stat = 0;
	I adrs;
	j = 0;
	for (i = 0; i < l_len; i++) {
		if (line[i] == str[j]) {
			if (!j)
				adrs = i;
			j++;
			if (j == s_len) {
				highlight(str, crd->line_y, crd->line_x + adrs);
				j = 0;
			}
		}
		else 
			j = 0;
	}
}






