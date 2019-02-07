
V user_input(S str, I len);						//<	get user's input into USER_INPUT

I input_state(S str);							//< returns state, calculates out of USER_INPUT

V clear_user_input();							//< clear line with y == usr_y

V show_help();									//< five lines at y == map_y; x == map_x

V upd_cph(S str, S key, I len, S alph);

C mod_line(S str, S key, I len, S alph);

S* count_importants(S line, I len, S* ptr_s);	//< keep all substrings len <= 4 in S* ptr
