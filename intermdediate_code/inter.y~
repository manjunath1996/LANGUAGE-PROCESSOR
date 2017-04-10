%{
 #include<ctype.h>
 #include <stdio.h>
 int fre=0;
 int asign=0;

 struct node{
        struct node* l,*r;
        int val;
        char sign;
        int ind;
 };


      struct node*  mknode1(struct node *l,struct node *r,int val,char sign){
                struct node* k=malloc(sizeof(struct node));
                k->l=l;
                k->r=r;
                k->val=val;
                k->sign=sign;
                
                return k;
        }
       struct node* mknode2 (struct node *l){
                return l;
        }
        struct node* ar[1000];
        
        void print(struct node *k){
                if(k==NULL)
                        return ;
                print(k->l);
                print(k->r);
                k->ind=asign++;
                if(k->val!=-10000){
                        printf("t%d =  %d \n",k->ind,k->val);
                }
                else
                        printf("t%d =t%d %c t%d\n ",k->ind,k->l->ind,k->sign,k->r->ind);
               
        };

%}
%token digit
%%

S: E {printf("Intermediate code :\n");print(ar[$$]);}
  ;
E : E'+'T  {ar[fre]=mknode1(ar[$1],ar[$3],-10000,'+');$$=fre++;}
   | T     {ar[fre]=mknode2(ar[$1]);$$=fre++;}
    ;


T : T'*'F  {ar[fre]=mknode1(ar[$1],ar[$3],-10000,'*');$$=fre++;}
   | F     {ar[fre]=mknode2(ar[$1]);$$=fre++;}
   ;

F :P '^' F  {ar[fre]=mknode1(ar[$1],ar[$3],-10000,'^');$$=fre++;}
  | P          {ar[fre]=mknode2(ar[$1]);$$=fre++;}
  ;
P : '('E')' {ar[fre]=mknode2(ar[$2]);$$=fre++;}
  |digit {ar[fre]=mknode1(NULL,NULL,$1,'!');$$=fre++;}
  ;

%%

int main()
{
 printf("Enter an expression\n");
 yyparse();
 return 0;
}

yyerror()
{
 printf("NITW Error\n");
}

