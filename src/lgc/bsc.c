#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <dirent.h>

#include "../cfg/___.h"
#include "../cfg/cfg.h"

#include "set.h"
#include "../min/min.h"
#include "map.h"
#include "usr.h"
#include "../min/pnt.h"

extern coor crd;

C LINE_[] = "Vs lbh nfxrq Oehpr Fpuarvre gb qrpelcg guvf, ur'q pehfu lbhe fxhyy jvgu uvf ynhtu.";

S LINE;

C MAP = 0;

I ST = 2;
I IM;
C IM_S = 0;
I H_ = 0;

I LEN;

C USER_INPUT[US_IN_LEN];
C alphabet[LETTERS];			
S* importants;
I IM_AM;

// pCoors coors = {4, 3, 7, 6, 0, 17, 0, 18};
pCoors coors;
coor crd = &coors;


pTerminal_conf win_size;
ter_conf terminal = &win_size;


//< alphabet[num] -- key for num letetr 

// enum STATES {quit, help, cc, map, hide};

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
 *	[error_line]						*
 ****************************************/
/*
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
	S LINE = "Vs lbh nfxrq Oehpr Fpuarvre gb qrpelcg guvf, ur'q pehfu lbhe fxhyy jvgu uvf ynhtu."
	C USER_INPUT[US_IN_LEN];
	I ST = 0;

	C alphabet[26];			

	//< alphabet[num] -- key for num letetr 

	enum STATES {quit, help, cc, map, hide};
///////////////////////////////////////////////////
*/
//<	states
//<	0: 	! 		help
//<	1: 	q 		quit
//<	2: 	cc		decrypt
//<	3:	m 		map
//<	4:	h 		hide map
//<	5:	i 		show importants
//<	6:	*str 	highlight substrings str
//<	7:	a^		swap a with ^

V process()
{
	while (ST != quit) {
		user_input(USER_INPUT, US_IN_LEN); 				//< get user's input; 
		clear_error();
		ST = input_state(USER_INPUT);			//< calculates state type from USER_INPUT

		SW(ST) { 
			CS(help,{	MAP = 0; show_help();});	
			CS(cc, 	{	upd_cph(LINE, USER_INPUT, LEN, alphabet);});
			CS(lght,{	highlighted_line(LINE, USER_INPUT + 1);});
			CS(map, {	MAP = 1; IM_S = 0; show_map(alphabet);});
			CS(hide,{	IM_S = 0; MAP = 0; hide_map();});
			CS(imp,	{	IM_S = 1; MAP = 0; show_importants(importants, alphabet);});
			// CS(swap,{	upd_cph(LINE, USER_INPUT, LEN, alphabet);});
			CS(quit,{	break;});
			CD: 		error_message("invalid command", 0, "");
		}
	}

}

//< place of letter --> place(line[i]) == y: i / height x: i % width 

I main(I argc, S* argv)
{
	I i, size;
	FILE* ptr;

	LEN = scnt(LINE_);
	// LEN = scnt(LINE_);
	// kbinit();

	clrscr();
	if (!set_start(argc, argv, terminal))
		R0;


	// clrscr();
	
	print_line(LINE);
	make_map(LINE, alphabet);
	// O("COUNT importants\n");
	importants = count_importants(LINE, LEN, importants);
	show_help();

	process();
	result(alphabet);
	O("\n");
	// free(LINE);
	// free(importants);
	getchar();
	clrscr();
	O("\n");


	// kbfini();
	return 0;
}





