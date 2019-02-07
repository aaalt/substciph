#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include <sys/ioctl.h>
#include <dirent.h>


#include "../cfg/cfg.h"

#include "min.h"
#include "../lgc/map.h"


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
	O("'!'    --->  help");
	gotoxy(crd->map_y + 1, crd->map_x);
	O("'q'    --->  quit");
	gotoxy(crd->map_y + 2, crd->map_x);
	O("'a''b' --->  swap each 'a' with 'b'");
	gotoxy(crd->map_y + 3, crd->map_x);
	O("'m'    --->  show map");
	gotoxy(crd->map_y + 4, crd->map_x);
	O("'h'    --->  hide map");
	gotoxy(crd->map_y + 5, crd->map_x);
	O("'i'    --->  show importants");
	gotoxy(crd->map_y + 6, crd->map_x);
	O("'*str' --->  highlight str");
	gotoxy(crd->map_y + 7, crd->map_x);
	O("'a^'   --->  swap each a with ^[|]");

	gotoxy(crd->map_y + 9, crd->map_x);
	O("* if you want to replace for ex. 'a' with");
	gotoxy(crd->map_y + 10, crd->map_x);
	O("  used 'b', just do ::_ bx than ::_ ab");
	fflush(stdout);
}

V print_valids(S alph)
{
	I j;
	C i, c = 0;
	gotoxy(crd->usr_y -2, crd->map_x);
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
			O("%c ", (i + 'a'));
	}
}

V show_map(S alph)					//<	five lines at y == map_y; x == map_x
{
	I i;
	hide_map();
	gotoxy(crd->map_y, crd->map_x);
	O("c|    ");
	for (i = 0; i < 6; i++)
		O("%c  ", 'a' + i);
	O("    ");
	for (i = 0; i < 7; i++)
		O("%c  ", 'a' + i + 6);
	O("    |c");

	gotoxy(crd->map_y + 1, crd->map_x);
	O("o|    ");
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
	O("    |o");

	gotoxy(crd->map_y + 3, crd->map_x);
	O("c|    ");
	for (i = 0; i < 6; i++)
		O("%c  ", 'n' + i);
	O("    ");
	for (i = 0; i < 7; i++)
		O("%c  ", 'n' + i + 6);
	O("    |c");

	gotoxy(crd->map_y + 4, crd->map_x);
	O("o|    ");
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
	O("    |o");

	print_valids(alph);

	MAP = 1;
}

V result(S alph)
{
	C c, k;
	I i, j;

	O("\n\tRESULTS:\n\n");

	for (i = 0; i < 13; i++) {
		k = 0;
		O("\t%c  -->  ", 'a' + i);
		for (j = 0; j < 26; j++) {
			if ('a' + i == alph[j]) {
				k = 1;
				O("%c\t", j + 'a');
			}
		}
		if (!k)
			O("*\t");

		k = 0;
		O("\t%c  -->  ", 'a' + i + 13);
		for (j = 0; j < 26; j++) {
			if ('a' + i + 13 == alph[j]) {
				k = 1;
				O("%c\t", j + 'a');
			}
		}
		if (!k)
			O("*\t");
		O("\n");
	}

	O("\n\n");
}

V show_importants(S* ptr, S alph)
{
	I i, j, k = 0, d = 0, len = 0, wh = 0;

	hide_map();

	gotoxy(crd->map_y, crd->map_x);

	for (i = 0; i < IM; i++) {
		len = 0;
		for (j = 0; ptr[i][j] && !is_delim(ptr[i][j]); j++)
			;
		len = j;

		if (wh + len <= terminal->ws_col - crd->map_x*2) {
			for (j = 0; ptr[i][j] && !is_delim(ptr[i][j]); j++, wh++) 
				O("%c", ptr[i][j]);
			fflush(stdout);
			for (j = 0; j < 8 - (len%8) + (len/8)*8 && wh < terminal->ws_col - crd->map_x*2; j++, wh++)
				O(" ");
		}
		else {
			k++;
			gotoxy(crd->map_y + k, crd->map_x);
			wh = 0;
			i--;
		}

	}
	print_valids(alph);
}

V highlight(S str, I len, I adr, I y, I x)
{
	I i, j;

	for (i = 0; i < len; i++) {
		gotoxy(y_of_i(str, adr+i, terminal->ws_col - (crd->line_x*2), crd->line_y), x_of_i(str, adr+i, terminal->ws_col - (crd->line_x*2), crd->line_x));
		O("\e[4m");
		O("%c", str[adr + i]);
		O("\e[24m");
	}
	fflush(stdout);
}

V highlighted_line(S line, S str)
{
	I i, j, l_len = scnt(line), s_len = scnt(str), stat = 0;
	I adrs;
	j = 0;
	for (i = 0; i < l_len; i++) {
		if (tolower_(line[i]) == tolower_(str[j])) {
			if (!j)
				adrs = i;
			j++;
			if (j == s_len) {
				//< line - source; s_len - amount of highlighting
				//<	adrs - first highlighting letter
				//< y, x start of text
				highlight(line, s_len, adrs, crd->line_y, crd->line_x);
				j = 0;
			}
		}
		else 
			j = 0;
	}
}






