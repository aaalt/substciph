#include <stdio.h>
#include <ctype.h>

#include "cfg.h"

V error_message(S str_1, C str_2, S str_3)
{
	gotoxy(crd->err_y, crd->err_x);
	O("%s%c%s", str_1, str_2, str_3);
}

C in_alphabet(C c)
{
	R ((c >='A' && c <= 'Z') || (c >= 'a' && c <= 'z')) ? 1 : 0;
}

V clear_line(I y)
{
	gotoxy(y, 0);
	printf("\e[2K");
}

C case_c(C c) 			//< 1 -- upper; 0 -- lower
{							
	R (c >= 'A' && c <= 'Z') ? 1 : 0;
}

C nocase_cmp(C a, C b)
{
	R (tolower(a) == tolower(b)) ? 1 : 0;
}

V clear_error()
{
	clear_line(crd->err_y);
}