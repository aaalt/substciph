V error_message(S str)
{
	gotoxy(crd->err_x, crd->err_y);
	O("%s", str);
}

C in_alphabet(C c)
{
	R ((c >='A' && c <= 'Z') || (c >= 'a' && c <= 'z')) ? 1 : 0;
}

V clear_line(I y)
{
	gotoxy(0, y);
	printf("\e[2K");
}

