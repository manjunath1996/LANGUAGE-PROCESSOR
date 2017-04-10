d [0-9]
lt [A-Za-z]
end [$\t\n ]
sign [-+]
ident {lt}({lt}|{d})*
integer {sign}?{d}+
float {sign}?{d}+"."{d}+("e"{sign}?{d}+)?
punct "+"|"-"|"*"|"%"|"/"|"("|")"|";"
logical "=="|">="|"<="|">"|"<"|"||"|"&&"|"="
%%
(if|while|for|switch)/[ "("]                          {printf("\n %s keywords\n",yytext);}
{ident}/({punct}|{end}|{logical})                                {printf("\n %s Identifier\n",yytext);}
{integer}({lt}+({integer}+)?)+                                       {printf(" ");}
{integer}/({punct}|{end}|{logical})                                   {printf("\n %s Integer\n",yytext);}
{float}/({punct}|{end}|{logical})            {printf("\n %s flaoating point number\n",yytext);}
{logical}/({ident}|{integer}|{float}|{end})                   {printf("\n %s Logical operator\n",yytext);}
{punct}/({end}|{ident})           {printf("\n %s Punctuation mark\n",yytext);}
%%

int main() {
        printf("Enter text\n"); 
        yyin=fopen("inp.txt","r");
        yylex();
        return 0;
}

/*
int a=b=5=20.4e-5;
1a float b=22=-5.2e+5;2a
b=b=b;
*/