#include <stdio.h>
#include <ctype.h>
#include <sys/ioctl.h>

#include "../cfg/cfg.h"

C tolower_(C c)
{
	if (c >= 'A' && c <= 'Z')
		R c + ' ';
	if (c == '|')
		R '^';
	R c;
}

C toupper_(C c)
{
	if (c >= 'a' && c <= 'z')
		R c - ' ';
	if (c == '^')
		R '|';
	R c;
}

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
	R ((c >= 'A' && c <= 'Z') || c == '|') ? 1 : 0;
}

C nocase_cmp(C a, C b)
{
	R (tolower_(a) == tolower_(b)) ? 1 : 0;
}

V clear_error()
{
	clear_line(crd->err_y);
}

//< place of letter --> place(line[i]) == y: i / height x: i % width 

I print_parse(S str, I width, I x, I y);

I x_of_i(S str, I i_, I width, I x)
{
	I len = 0, line_pos = 0, i = 0, j = 0, k, l;
	I word_ptr = 0, lines = 1;  				
	x++; 
	while(str[i]) {

		//< line break if needed
		if (line_pos >= width) {
			line_pos = 0;
		}

		//<	get word (everything but ' ', 0 and '\n')
		//< len -- word len; i -- num at next ' ' or end
		for (len = 0, word_ptr = i; str[i] && str[i] != ' ' && str[i] != '\n'; len++, i++)
			;

		//<	if len == 0 --> find 
		if (len) {
			//<	words with line break
			if (line_pos + len > width) {
				//< make spaces
				if (line_pos) {
					line_pos = 0;
				}
				//<	write word
				for (k = 0; k < len/width; k++) {
					for (l = 0; l < width; l++) {
						if (word_ptr == i_)
							R line_pos + x + x;
						word_ptr++;
						line_pos++;
					}
					line_pos = 0;

				}
				for (k = 0; k < len%width; k++) {
					if (word_ptr == i_)
							R line_pos + x;
					word_ptr++;
					line_pos++;
				}

			}
			//<	words without line break
			else {
				for (j = 0; j < len; j++) {
					if (word_ptr == i_)
							R line_pos + x;
					word_ptr++;
					line_pos++;
				}
			}
			i = word_ptr;
		}
		//< if it's ' ', '\n' or end
		else {
			//<	if ' '
			for (;str[i] == ' '; i++) {
				if (word_ptr == i_)
							R line_pos + x;
				if (line_pos < width) 
					line_pos++;
				// }
				else {
						line_pos = 0;
				}
			}
			//<	if '\n'
			for (;str[i] == '\n'; i++) {
				if (word_ptr == i_)
							R line_pos + x;
				line_pos = 0;		
			}
		}
	}
	R -1;
}

I y_of_i(S str, I i_, I width, I y)
{
	//< line_pos -- a place, where next char will be placed 0 ... width-1
	I len = 0, line_pos = 0, i = 0, j = 0, k, l;
	I word_ptr = 0, lines = 1;  				

	while(str[i]) {

		//< line break if needed
		if (line_pos >= width) {
			lines++;
			line_pos = 0;
		}

		//<	get word (everything but ' ', 0 and '\n')
		//< len -- word len; i -- num at next ' ' or end
		for (len = 0, word_ptr = i; str[i] && str[i] != ' ' && str[i] != '\n'; len++, i++)
			;

		//<	if len == 0 --> find 
		if (len) {
			//<	words with line break
			if (line_pos + len > width) {
				//< make spaces
				if (line_pos) {
					lines++;
					line_pos = 0;
				}
				//<	write word
				for (k = 0; k < len/width; k++) {
					for (l = 0; l < width; l++) {
						if (word_ptr == i_)
							R lines + y;
						word_ptr++;
						line_pos++;
					}
					lines++;
					line_pos = 0;

				}
				for (k = 0; k < len%width; k++) {
					if (word_ptr == i_)
							R lines + y;
						word_ptr++;
					line_pos++;
				}

			}
			//<	words without line break
			else {
				for (j = 0; j < len; j++) {
					if (word_ptr == i_)
							R lines + y;
					word_ptr++;
					line_pos++;
				}
			}
			i = word_ptr;
		}
		//< if it's ' ', '\n' or end
		else {
			//<	if ' '
			for (;str[i] == ' '; i++) {
				if (i == i_)
					R lines + y;
				if (line_pos < width) {
					line_pos++;
				}
				else {
						lines++;
						line_pos = 0;
				}
			}
			//<	if '\n'
			for (;str[i] == '\n'; i++) {
				if (i == i_)
					R lines + y;
				lines++;
				line_pos = 0;		
			}
		}
	}
	R -1;
}

I print_line(S str)
{
	I i = print_parse(str, terminal->ws_col - (crd->line_x*2), crd->line_x, crd->line_y);
	fflush(stdout);
	R i;
}

I lines(S str, I width)
{
	R y_of_i(str, strlen(str) - 1, width, 0);
}

I print_parse(S str, I width, I x, I y)
{
	//< line_pos -- a place, where next char will be placed 0 ... width-1
	I len = 0, line_pos = 0, i = 0, j = 0, k, l;
	I word_ptr = 0, lines = 1;  				
	x ++; 
	// y++;


	gotoxy(y + lines, x);

	while(str[i]) {

		//< line break if needed
		if (line_pos >= width) {
			// lines++;
			gotoxy(++lines + y, x);
			line_pos = 0;
		}

		//<	get word (everything but ' ', 0 and '\n')
		//< len -- word len; i -- num at next ' ' or end
		for (len = 0, word_ptr = i; str[i] && str[i] != ' ' && str[i] != '\n'; len++, i++)
			;

		//<	if len == 0 --> find 
		if (len) {
			//<	words with line break
			if (line_pos + len > width) {
				//< make spaces
				if (line_pos) {
					for (j = line_pos; j < width; j++)
						O(" ");
					gotoxy(++lines + y, x);
					line_pos = 0;
				}
				//<	write word
				for (k = 0; k < len/width; k++) {
					for (l = 0; l < width; l++) {
						O("%c", str[word_ptr++]);
						line_pos++;
					}

					gotoxy(++lines + y, x);
					line_pos = 0;

				}
				for (k = 0; k < len%width; k++) {
					O("%c", str[word_ptr++]);
					line_pos++;
				}

			}
			//<	words without line break
			else {
				for (j = 0; j < len; j++) {
					O("%c", str[word_ptr++]);
					line_pos++;
				}
			}
			i = word_ptr;
		}
		//< if it's ' ', '\n' or end
		else {
			//<	if ' '
			for (;str[i] == ' '; i++) {
				if (line_pos < width) {
					O(" ");
					line_pos++;
				}
				else {
						gotoxy(++lines + y, x);
						line_pos = 0;
				}
			}
			//<	if '\n'
			for (;str[i] == '\n'; i++) {
				gotoxy(++lines + y, x);
				line_pos = 0;		
			}
		}
		fflush(stdout);
	}
	R lines;
}

C is_delim(C c)
{
	if (c == '\'')
		R 0;
	if (((c >= ' ' && c < 'A') || (c > 'Z' && c < 'a') || (c > 'z' && c < 127) || c == '\n') && c != '^' && c != '|')
		R1;
	R0;
}











