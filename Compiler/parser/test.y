%token Realnumber
%left '+' '-'
%left '*' '/'
%{
	#include<stdio.h>
	int Ans = 0;
%}
%%
statement : expression
		{	printf("\nAnswer%d => %d\n\n================\n",++Ans,$1);}
		| statement '\n' expression
		{	printf("\nAnswer%d => %d\n\n================\n",++Ans,$2);}
	    ;				
expression :
		| factor {$$ = $1;}
		| expression '+' factor
		{	
			$$ = $1 + $3;
			printf("%d add %d\n",$1,$3);
		}
		| expression '-' factor
		{
			$$ = $1 - $3;
			printf("%d cut %d\n",$1,$3);
		}
		;
factor : primary {$$ = $1;}
		| factor '*' primary
		{
			$$ = $1 * $3;
			printf("%d multiply %d\n",$1,$3);
		}
		| factor '/' primary
		{
			$$ = $1 / $3;
			printf("%d divide %d\n",$1,$3);
		}
		;
primary : Realnumber
		| '(' expression ')' {$$ = $2;}
		;

%%
int main()
{
	yyparse();
	return 0;
}
int yyerror(char *msg)
{
	printf("Error:%s \n", msg);
}