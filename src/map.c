

/*
V make_map(S line, S alph);			//< scan LINE and compute result into alphabet
V show_map(S alph);			//<	five lines at y == map_y; x == map_x
V hide_map();			//< clear five lines at y == map_y; x == map_x
C mod_map(S str, S alph);		//< modify map; for ex. str == "ab"; all a's to b

*/
//<	S LINE = "Vs lbh nfxrq Oehpr Fpuarvre gb qrpelcg guvf, ur'q pehfu lbhe fxhyy jvgu uvf ynhtu."


	
V show_map(S alph)					//<	five lines at y == map_y; x == map_x
{
	I i;
	gotoxy(crd->map_x, crd->map_y);
	for (i = 0; i < 13; i++)
		O("%c ", 'a' + i);

	gotoxy(crd->map_x, crd->map_y + 1);
	for (i = 0; i < 13; i++) {
		if (alph[i])
			O("%c ", alph[i]);
		else 
			O("? ");
	}

	gotoxy(crd->map_x, crd->map_y + 3);
	for (i = 0; i < 13; i++)
		O("%c ", 'n' + i);

	for (i = 0; i < 13; i++) {
		if (alph[i + 13])
			O("%c ", alph[i + 13]);
		else 
			O("? ");
	}
}

V make_map(S line, S alph)			//< scan LINE and compute result into alphabet
{
	I i, len = strlen(line);
	C c;

	for (i = 0; i < 26; i++)
		alph[i] = 0;

	for (i = 0; i < len; i++) {
		if (in_alphabet(line[i]))
			alph[tolower(line[i]) - 'a'] = tolower(line[i]);
	}
}

C mod_map(S str, S alph)			//< modify map; for ex. str == "ab"; all a's to b
{
	I i, j;
	C c = '1', par = 0;

	for (i = 0; i < 26 && c != tolower(str[1]); i++)
		c = alph[i];

	if (c == tolower(str[1])) {
		error_message("key '%c' already exists", tolower(str[1]));
		R0;
	}

	for (i = 0; i < 26 && c != tolower(str[0]); i++)		//< i - 1
		c = alph[i];

	if (i == 26 && c != tolower(str[0])) {		//< no such letter for swap
		error_message("there is no '%c' in the text", tolower(str[0]));
		R0;
	}

	j = i - 1;
	for (c = alph[i]; i < 26 && c != str[0]; i++)
		c = alph[i];

	if (c == tolower(str[0])) {
		error_message("there are more than one '%c'", tolower(str[0]));
		R0;
	}

	alph[j] = tolower(str[1]);

	if (MAP)
		show_map();

	R1;
}

V hide_map()						//< clear five lines at y == map_y; x == map_x
{
	for (i = 0; i < usr_y - map_y; i++) 
		clear_line(crd->map_y + i);
}

