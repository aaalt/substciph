#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "___.h"
/****************************************
 *	texttexttexttexttexttext			*
 *										*
 *	a b c d e f g h i j k l m 			*
 *	k k k k k k k k k k k k k 			*
 *										*
 *	n o p q r s t u v w x y z 			*
 *	k k k k k k k k k k k k k 			*
 *										*
 *	::_									*
 *										*
 ****************************************/
///////////////////////////////////////////////////
	typedef struct Coors {
			UH line_x;			//< 4
			UH line_y;			//< 0
			UH map_x;			//<	6
			UH map_y;			//<	3
			UH usr_x;			//<	4
			UH usr_y;			//<	9
	} pCoors;
	typedef pCoors* coors;

	pCoors coor = {4, 0, 6, 3, 4, 12};
	coors crd = &coor;
///////////////////////////////////////////////////

	#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))
	#define clrscr() printf("\e[1;1H\e[2J");

	#define US_IN_LEN 10
///////////////////////////////////////////////////
	S LINE = "Vs lbh nfxrq Oehpr Fpuarvre gb qrpelcg guvf, ur'q pehfu lbhe fxhyy jvgu uvf ynhtu."
	C USER_INPUT[US_IN_LEN];
	I ST = 0;

	enum ATOZ {A_, B_, C_, D_, E_, F_, G_, H_, I_, J_, K_, L_, M_, N_, O_, P_, Q_, R_, S_, T_, U_, V_, W_, X_, Y_, Z_};
	C alphabet[26];			

	//< alphabet[num] -- key for num letetr 

	enum STATES {quit, help, cc, map, hide};
///////////////////////////////////////////////////

//<	states
//<	0: (!) 		help
//<	1: (q) 		quit
//<	2: cc		decrypt
//<	3:	m 		map
//<	4:	h 	hide map


// V user_input();			//<	get user's input into USER_INPUT
// I input_state();		//< returns state, calculates out of USER_INPUT
// V clear_user_input();	//< clear line with y == usr_y

V show_help();			//< five lines at y == map_y; x == map_x
V mod_line(S str);		//< modify line; for ex. str == 'ab'; all a's from text swap with b

V process()
{
	while (st != quit) {
		user_input(USER_INPUT, US_IN_LEN); 				//< get user's input; 
		st = input_state(USER_INPUT);			//< calculates state type from USER_INPUT
		clear_user_input();
		SW(st) { 
			CS(help,{	MAP = 0; show_help();});	
			CS(cc, 	{	mod_map(USER_INPUT, alphabet); 
						mod_line(LINE, USER_INPUT)});
			CS(map, {	MAP = 1; show_map();});
			CS(hide, {	MAP = 0; hide_map();});
			CD: 	error_message("invalid command");
		}
	}

	clear_user_input();
}


I main()
{
	clrscr();
	make_map(LINE, alphabet);				//< create map 
	mod_line("vv");			//< show line without any modify 
	process();
	clrscr();
	R 0;
}







