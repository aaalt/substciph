#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "cfg.h"

#include "min.h"
#include "map.h"
#include "pnt.h"

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

	if (str[0] == '*' && len > 1)
		R lght;

	if (!len || len > 2)
		R -1;

	if (len == 2 && in_alphabet(str[0]) && in_alphabet(str[1]))
		R cc;

	R 	(str[0] == '!') ? help : 
		(str[0] == 'i' || str[0] == 'I') ? imp	:
		(str[0] == 'q' || str[0] == 'Q') ? quit	:
		(str[0] == 'm' || str[0] == 'M') ? map 	:
		(str[0] == 'h' || str[0] == 'H') ? hide : -1;
}



C mod_line(S str, S key, I len, S alph)		//< modify str; for ex. key == 'ab'; all a's from text swap with b
{
	I i, j = 0;

	for (i = 0; i < len; i++){
		gotoxy(crd->line_y , crd->line_x + i);

		if (nocase_cmp(str[i], key[0])) {
			j = (j) ? j : 1;
			if (case_c(str[i])) 
				str[i] = (C)toupper(key[1]);
			else 
				str[i] = (C)tolower(key[1]);
		} 
	}

	if (j) {
		print_line(str);
		if (MAP)
			show_map(alph);
		if (IM_S)
			show_importants(importants, alph);
	}
	R j;
}

V upd_cph(S str, S key, I len, S alph)
{
	if (mod_map(key, alph)) {
		if (!mod_line(str, key, len, alph))
			error_message("there is no '", (C)tolower(key[0]), "' in line");
	}
}

//< keep all substrings len <= 4 in S* ptr
V count_importants(S line, I len, S* ptr_s)
{
	I i, j = 0, k = 0, count = 0;
	C c;

	//< calculate all smalls 
	for (i = 0; i < len; ) {
		count = 0;
		j = i;
		while (line[i] != ' ' && line[i] != ',' && line[i] != '.' && line[i] != 0) {
			c = line[i+1];
			if (c != ' ' && c != ',' && c != '.' && c == line[i]) {
				ptr_s[k++] = &line[j];
				for (; line[i] != ' ' && line[i] != ',' && line[i] !='.'; i++)
					;
					count += 4;
			}
			else {
				i++;
				count++;
			}
		}
		while (line[i] == ' ' || line[i] == ',' || line[i] == '.')
			i++;
		if (count <= 4)
			ptr_s[k++] = &line[j];
	}

	IM = k;
}




