%{
	#include<stdio.h>
	int Total_Num=0;
	int Total_Float=0;
	int Total_ID=0;
	int Total_Error=0;
%}
%option noyywrap 
%%
[0-9]+;	{
		printf("Find a Number: %s\n",yytext);
		Total_Num++;
}
[0-9]+\.[0-9]+;	{
		printf("Find a Float: %s\n",yytext);
		Total_Float++;
}
[A-Za-z][A-Za-z0-9_]*;	{
		printf("Find a ID: %s\n",yytext);
		Total_ID++;
}
[.]*[A-Za-z0-9.\+\-\*\/\_]*[.]*[;]*	{
		printf("Find a Error: %s\n",yytext);
		Total_Error++;
}
\n	{}
%%
int main()
{
	yylex();
	printf("Total_Num = %d\n",Total_Num);
	printf("Total_Float = %d\n",Total_Float);
	printf("Total_ID = %d\n",Total_ID);
	printf("Total_Error = %d\n",Total_Error);
	return 0;
}