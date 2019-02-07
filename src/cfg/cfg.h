#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "___.h"

///////////////////////////////////////////////////
typedef struct Coors {
		UH line_x;			//< 4
		UH line_y;			//< 0
		UH map_x;			//<	6
		UH map_y;			//<	3
		UH usr_x;			//<	4
		UH usr_y;			//<	12
		UH err_x;			//<	0
		UH err_y;			//<	13
} pCoors;
typedef pCoors* coor;


typedef struct winsize pTerminal_conf;
typedef pTerminal_conf* ter_conf;


///////////////////////////////////////////////////

typedef enum STATE {quit, help, cc, map, hide, imp, lght, swap} STATE;



#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))
#define clrscr() printf("\e[1;1H\e[2J");


///////////////////////////////////////////////////
// S LINE = "Vs lbh nfxrq Oehpr Fpuarvre gb qrpelcg guvf, ur'q pehfu lbhe fxhyy jvgu uvf ynhtu."
#define US_IN_LEN 600

#define LETTERS 26

#define MENU_WIDTH 58
#define MENU_HIGHT 10


ext I LEN;
/*C alphabet[26];			

//< alphabet[num] -- key for num letetr 

enum STATES {quit, help, cc, map, hide};*/
///////////////////////////////////////////////////


// extern C LINE[];

ext S LINE;
ext C MAP;
ext C USER_INPUT[];
ext I ST;
ext enum STATE STATES;
ext coor crd;

ext I IM;
ext C IM_S;

ext C alphabet[];			
ext S* importants;

ext pTerminal_conf win_size;
ext ter_conf terminal;

ext C LINE_[];
ext I IM_AM;






