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
typedef pCoors* coors;

pCoors coor = {4, 0, 6, 3, 4, 12, 0, 13};
coors crd = &coor;
///////////////////////////////////////////////////

#define gotoxy(x,y) printf("\033[%d;%dH",(x),(y))
#define clrscr() printf("\e[1;1H\e[2J");

#define US_IN_LEN 10
#define MAP 0
#define LEN strlen(LINE)

///////////////////////////////////////////////////
S LINE = "Vs lbh nfxrq Oehpr Fpuarvre gb qrpelcg guvf, ur'q pehfu lbhe fxhyy jvgu uvf ynhtu."
C USER_INPUT[US_IN_LEN];
I ST = 0;

// enum ATOZ {A_, B_, C_, D_, E_, F_, G_, H_, I_, J_, K_, L_, M_, N_, O_, P_, Q_, R_, S_, T_, U_, V_, W_, X_, Y_, Z_};
C alphabet[26];			

//< alphabet[num] -- key for num letetr 

enum STATES {quit, help, cc, map, hide};
///////////////////////////////////////////////////
