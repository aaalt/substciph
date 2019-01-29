V clear_user_input();				//< clear line with y == usr_y
V show_help();						//< five lines at y == map_y; x == map_x
V hide_map();						//< clear five lines at y == map_y; x == map_x
V show_map(S alph);					//<	five lines at y == map_y; x == map_x
V print_valids(S alph);

V count_importants(S line, I len, S* ptr_s);

V show_importants(S* ptr, S alph);

V highlighted_line(S line, S str);

V result(S alph);


