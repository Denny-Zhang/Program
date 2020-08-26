%{
	#include"y.tab.h"
%}
%option noyywrap
%%
[0-9]+	{	
			yylval = atoi(yytext);
			return(Realnumber);	
		}
[\+\-\*\/\(\)\n]   { yylval = yytext[0]; return yytext[0]; }
\t		{}
.		{	return yytext[0];}
%%