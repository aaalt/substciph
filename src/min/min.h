V error_message(S str_1, C str_2, S str_3);

C in_alphabet(C c);

V clear_line(I y);

C case_c(C c) ;			//< 1 -- upper; 0 -- lower

C nocase_cmp(C a, C b);

V clear_error();

I print_line(S str);

I x_of_i(S str, I i_, I width, I x);

I y_of_i(S str, I i_, I width, I y);

I lines(S str, I width);

C is_delim(C c);

C tolower_(C c);

C toupper_(C c);


// I print_parse(S str, I width, I x, I y);