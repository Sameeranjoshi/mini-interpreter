#include<stdio.h>
#include<ctype.h>
#define NONE_OF_THESE 0
#define OPERAND 1
#define OPERATOR 2
struct info_about_tokens{
	int d_type;
	char value;
};
void gettoken(char *position,struct info_about_tokens *ptr_to_str){
	
	if(isdigit(*position)){
				ptr_to_str->d_type=OPERAND;
				ptr_to_str->value=(*position);
	}
	else if(((*position)=='+')||((*position)=='-')||((*position)=='*')||((*position)=='/')||((*position)=='=')){
				ptr_to_str->d_type=OPERATOR;
				ptr_to_str->value=(*position);	
	}
	else {
				ptr_to_str->d_type=NONE_OF_THESE;
				ptr_to_str->value='N';		//INSERT A NULL IN VALUE
	}

}
int main(void){
	
	char input_expression[30];
	struct info_about_tokens exp_info[10];
	printf("\nENTER THE EXPRESSION");
	scanf("\n%s",input_expression);
	printf("\nTHE EXPRESSION IS: %s",input_expression);
	
	char *position;	
	position=input_expression;
	int token_cnt=0;
	int i=0;
	while((*position)!='\0'){
		gettoken(position,&exp_info[i]);
		token_cnt++;
		i++;
	position++;		
	}

	printf("\nTHE EXPRESSION STRUCTURE IS(after lexing):");
	printf("\n(DATATYPE,VALUE)");
	for(int i=0;i<token_cnt;i++){
		printf("\n (%d,%c)",exp_info[i].d_type,exp_info[i].value);
	}
		
}
