/*
-	only 0-9 allowed
-	no variables allowed
-	if somewhere x/0 is present floating point exception not handled yet :>
		
*/
#include"interpreter.h"

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>


int top=-1;
int AST_top=-1;
int main(void){
	
	char input_expression[30];
	struct info_about_tokens exp_info[30];
	struct node *root;//pointer to the printing structure
	printf("\nENTER THE EXPRESSION");
	scanf("%[^\n]s",input_expression);	//accepts spaces now

	printf("\nTHE EXPRESSION IS: %s",input_expression);		
	
	
	char *position;
	position=input_expression;
	int token_cnt=0;
	int i=0,cnt_except_paren=0;		

	int no_of_paren=0;
	while((*position)!='\0'){

		if((*position=='(')||(*position==')'))
			no_of_paren++;

		if(isspace(*position)){
			position++;
		}

		else{
			gettoken(position,&exp_info[i]);
			token_cnt++;
			i++;
			position++;
		}
	}

	printf("\n\v\t\t######	TOKENIZATION DONE	###### ");
	printf("\nLIST OF TOKENS[0=NONE|1=DIGIT|3=PLUS|4=MINUS|5=MULTIPLY|6=DIVIDE|7=LPAREN|8=RPAREN]");
	for(int i=0;i<token_cnt;i++){
		printf("\n (%d,%c)",exp_info[i].d_type,exp_info[i].value);
	}
	
	cnt_except_paren=token_cnt-no_of_paren;
	
	int globalindex=0;
	int success=expr(exp_info,token_cnt,globalindex);
	printf("\n\v\t\t######	PARSING DONE	###### %d",success);
	if(success!=(-1)){
		printf("\nFORMAT MATCHES");
		printf("\n\v\t\t######	CREATING AST	######");
		root=AST(exp_info,token_cnt,cnt_except_paren);
		printf("\nAST CREATED\nprinting the indorder of AST\n");
		printf("-------------------------------------------");
		inorder(root,0);
		printf("-------------------------------------------");
		int ans=eval(root);
		printf("\n^^^^^^ANSWER IS %d",ans);
	}
	else
		printf("\nFORMAT DOSEN'T MATCHES");
	
}
