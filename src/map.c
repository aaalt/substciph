#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "___.h"

#include "cfg.h"
#include "min.h"

extern coor crd;
extern C MAP;

//<	S LINE = "Vs lbh nfxrq Oehpr Fpuarvre gb qrpelcg guvf, ur'q pehfu lbhe fxhyy jvgu uvf ynhtu."
	
V hide_map();						//< clear five lines at y == map_y; x == map_x
V print_valids(S alph);

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

I letter_num(C c)
{
	R (c >= 'A' && c <= 'Z') ? (c - 'A') : (c - 'a');
}

V make_map(S line, S alph)			//< scan LINE and compute result into alphabet
{
	I i, len = strlen(line), num;
	C c;

	for (i = 0; i < 26; i++)
		alph[i] = 0;

	for (i = 0; i < len; i++) {
		if (in_alphabet(line[i])) {
			num = letter_num(line[i]);
			alph[num] = (C)tolower(line[i]);
		}
	}
}

C mod_map(S str, S alph)			//< modify map; for ex. str == "ab"; all a's to b
{
	I i, j;
	C c = '1', par = 0;

	for (i = 0; i < 26 && c != tolower(str[1]); i++)
		c = alph[i];

	if (c == tolower(str[1])) {
		error_message("key '", (C)tolower(str[1]), "' already exists");
		R0;
	}

	for (i = 0; i < 26 && c != tolower(str[0]); i++)		//< i - 1
		c = alph[i];

	if (i == 26 && c != tolower(str[0])) {		//< no such letter for swap
		error_message("there is no '", (C)tolower(str[0]), "' in the text");
		R0;
	}

	j = i - 1;
	for (c = alph[i]; i < 26 && c != str[0]; i++)
		c = alph[i];

	if (c == tolower(str[0])) {
		error_message("there are more than one '", (C)tolower(str[0]), "'");
		// error_message("there are more than one '%c'", tolower(str[0]));
		R0;
	}

	alph[j] = tolower(str[1]);

	if (MAP)
		show_map(alph);

	R1;
}

V hide_map()						//< clear five lines at y == map_y; x == map_x
{
	for (I i = 0; i < crd->usr_y - crd->map_y; i++) 
		clear_line(crd->map_y + i);
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




