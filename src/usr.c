

// V user_input(S str, I len);			//<	get user's input into USER_INPUT
// I input_state(S str);				//< returns state, calculates out of USER_INPUT
// V clear_user_input();				//< clear line with y == usr_y

// V show_help();						//< five lines at y == map_y; x == map_x
// V mod_line(S str, S key);					//< modify line; for ex. str == 'ab'; all a's from text swap with b


V user_input(S str, I len)			//<	get user's input into USER_INPUT
{
	I i;
	C c = '1';
	for (i = 0; i < len && !feof(stdin); i++) {
		c = getchar();
		if (c != '\n' && c != 0)
			str[i] = c;
		else 
			str[i] = 0;
	}

	if (i < 2)
		error_message("invalid input");

	if (i == len) {
		for (c != 0 && c != '\n')
			c = getchar();
	}
}

I input_state(S str)				//< returns state, calculates out of USER_INPUT
{
	I len = strlen(str);
	if (strlen > 2 || !strlen)
		R -1;

	if (strlen == 2 && in_alphabet(str[0]) && in_alphabet(str[1]))
		R cc;

	R 	(str[0] == '!') ? help : 
		(str[0] == 'q' || str[0] == 'Q') ? quit	:
		(str[0] == 'm' || str[0] == 'M') ? map 	:
		(str[0] == 'h' || str[0] == 'H') ? hide : -1;
}

V clear_user_input()				//< clear line with y == usr_y
{
	clear_line(crd->usr_y);
	gotoxy(crd->usr_x, crd->usr_y);
	O("::_");
	fflush(stdout);
}

V show_help()						//< five lines at y == map_y; x == map_x
{
	hide_map();

	gotoxy(crd->map_x, crd->map_y);
	O("\t'!'    --->  help");
	gotoxy(crd->map_x, crd->map_y + 1);
	O("\t'q'    --->  quit");
	gotoxy(crd->map_x, crd->map_y + 2);
	O("\t'a''b' --->  swap each 'a' with 'b'");
	gotoxy(crd->map_x, crd->map_y + 3);
	O("\t'm'    --->  show map");
	fflush(stdout);
}

C mod_line(S str, S key, I len)		//< modify str; for ex. key == 'ab'; all a's from text swap with b
{
	I i, j = 0;

	for (i = 0; i < len; i++){
		if (nocase_cmp(str[i], key[0])) {
			j = (j) ? j : 1;
			gotoxy(crd->line_x + i, crd->line_y);
			if (case_c(str[i]))
				O("%c", toupper(key[1]));
			else
				O("%c", tolower(key[1]));
		}
	}
	fflush(stdout);
	R j;
}

V upd_cph(S str, S key, I len, S alph)
{
	if (mod_map(key, alph))
		if (!mod_line(str, key, len))
			error_message("there is no '%c' in line", tolower(key[0]));
}

V clear_error()
{
	clear_line(crd->err_y);
}



