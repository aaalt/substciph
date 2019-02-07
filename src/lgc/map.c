#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../cfg/___.h"

#include "../cfg/cfg.h"
#include "../min/min.h"
#include "../min/pnt.h"


extern coor crd;
extern C MAP;

//<	S LINE = "Vs lbh nfxrq Oehpr Fpuarvre gb qrpelcg guvf, ur'q pehfu lbhe fxhyy jvgu uvf ynhtu."
	
V hide_map();						//< clear five lines at y == map_y; x == map_x
V print_valids(S alph);

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
			alph[num] = (C)tolower_(line[i]);
		}
	}
}

C mod_map(S str, S alph)			//< modify map; for ex. str == "ab"; all a's to b
{
	I i, j;
	C c = '1', par = 0;

	for (i = 0; i < 26 && c != tolower_(str[1]); i++)
		c = alph[i];

	if (c == tolower_(str[1])) {
		error_message("key '", (C)tolower_(str[1]), "' already exists");
		R0;
	}

	for (i = 0; i < 26 && c != tolower_(str[0]); i++)		//< i - 1
		c = alph[i];

	if (i == 26 && c != tolower_(str[0])) {		//< no such letter for swap
		error_message("there is no '", (C)tolower_(str[0]), "' in the text");
		R0;
	}

	j = i - 1;
	for (c = alph[i]; i < 26 && c != str[0]; i++)
		c = alph[i];

	if (c == tolower_(str[0])) {
		error_message("there are more than one '", (C)tolower_(str[0]), "'");
		// error_message("there are more than one '%c'", tolower_(str[0]));
		R0;
	}

	alph[j] = tolower_(str[1]);

	if (MAP)
		show_map(alph);

	R1;
}


