#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "cfg.h"

#include "min.h"
#include "map.h"

extern coor crd;

V user_input(S str, I len)			//<	get user's input into USER_INPUT
{
	I i;
	C c = '1';
	
	clear_line(crd->usr_y);
	gotoxy(crd->usr_y, crd->usr_x);
	O("::_ ");
	fflush(stdout);

	for (i = 0; i < len && !feof(stdin) && c != '\n'; i++) {
		c = getchar();
		if (c != '\n' && c != 0)
			str[i] = c;
		else 
			str[i] = 0;
	}

	if (i < 2)
		error_message("invalid input", 0, "");

	if (i == len) {
		while (c != 0 && c != '\n')
			c = getchar();
	}
}

I input_state(S str)				//< returns state, calculates out of USER_INPUT
{
	I len = scnt(str);

	// O("input_state [usr.c]\n");

	if (len > 2 || !len)
		R -1;

	if (len == 2 && in_alphabet(str[0]) && in_alphabet(str[1]))
		R cc;

	R 	(str[0] == '!') ? help : 
		(str[0] == 'q' || str[0] == 'Q') ? quit	:
		(str[0] == 'm' || str[0] == 'M') ? map 	:
		(str[0] == 'h' || str[0] == 'H') ? hide : -1;
}
/*
V clear_user_input()				//< clear line with y == usr_y
{
	// O("clear_user_input [usr.c]\n");

	clear_line(crd->usr_y);
	gotoxy(crd->usr_x, crd->usr_y);
	O(" ::_");
	fflush(stdout);
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
	gotoxy(crd->map_y + 6, crd->map_x);
	O("\t* if you want to replace for ex. 'a' with");
	gotoxy(crd->map_y + 7, crd->map_x);
	O("\t  used 'b', just do ::_ bx than ::_ ba");
	fflush(stdout);
}
*/
C mod_line(S str, S key, I len, S alph)		//< modify str; for ex. key == 'ab'; all a's from text swap with b
{
	I i, j = 0;

	for (i = 0; i < len; i++){
		gotoxy(crd->line_y , crd->line_x + i);

		if (nocase_cmp(str[i], key[0])) {
			j = (j) ? j : 1;
			if (case_c(str[i])) {
				str[i] = (C)toupper(key[1]);
				O("%c", (C)toupper(key[1]));
			}
			else {
				str[i] = (C)tolower(key[1]);
				O("%c", (C)tolower(key[1]));
			}
		} 
		else 
			O("%c", str[i]);
	}
	fflush(stdout);

	if (MAP)
		show_map(alph);
	R j;
}

V upd_cph(S str, S key, I len, S alph)
{
	if (mod_map(key, alph)) {
		if (!mod_line(str, key, len, alph))
			error_message("there is no '", (C)tolower(key[0]), "' in line");
	}
}





