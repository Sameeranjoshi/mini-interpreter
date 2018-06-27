#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define NONE_OF_THESE 0
#define DIGIT 1
#define PLUS 3
#define MINUS 4
#define MULTIPLY 5
#define DIVIDE 6
struct info_about_tokens{
	int d_type;
	char value;		//beaware it's in char when value needed parse it!
};
void gettoken(char *position,struct info_about_tokens *ptr_to_str){
	
	if(isdigit(*position)){
				ptr_to_str->d_type=DIGIT;
				ptr_to_str->value=(*position);
	}
	else if(((*position)=='+')||((*position)=='-')||((*position)=='*')||((*position)=='/')||((*position)=='=')){
				switch(*position){
					case '+':
						ptr_to_str->d_type=PLUS;
						break;	
					case '-':
						ptr_to_str->d_type=MINUS;
						break;
					case '*':
						ptr_to_str->d_type=MULTIPLY;
						break;
					case '/':
						ptr_to_str->d_type=DIVIDE;
						break;						
				}

				ptr_to_str->value=(*position);	
	}
	else {
				ptr_to_str->d_type=NONE_OF_THESE;
				ptr_to_str->value='N';		//INSERT AS NULL VALUE
	}

}
int validate(int data_type,int identifier){
	if(data_type==identifier)
		return 1;
	else
		return 0;
}
int parse(struct info_about_tokens *ptr,int token_cnt){
	int i=0;
	int isvalid;
	
	isvalid=validate(ptr->d_type,DIGIT);
	if(isvalid){
		token_cnt--;
		ptr++;
		/*this checks for the initial condition (ex.INPUT = 2)
		*/
		if(token_cnt==0)
			return 0;
		
		while(token_cnt!=0){
	//if operator matches
	if((validate(ptr->d_type,PLUS)||validate(ptr->d_type,MINUS)||validate(ptr->d_type,MULTIPLY)||validate(ptr->d_type,DIVIDE)))
			{

				ptr++;
				token_cnt--;
				if(validate(ptr->d_type,DIGIT)){//now the 2nd para matches
					ptr++;
					token_cnt--;
				}
				else
					return 0;	
			}
			else{
				return 0;
			}

		
		}
		return 1;
	
	}
	else{
		return 0;
	}


}
int main(void){
	
	char input_expression[30];
	struct info_about_tokens exp_info[10];
	printf("\nENTER THE EXPRESSION");
	scanf("%[^\n]s",input_expression);	//accepts spaces now
	printf("\nTHE EXPRESSION IS: %s",input_expression);
	
	char *position;	
	position=input_expression;
	int token_cnt=0;
	int i=0;		
	

	while((*position)!='\0'){
		if(isspace(*position)){
			position++;
			printf("\nskipped a space");
		}
		else{
			gettoken(position,&exp_info[i]);
			token_cnt++;
			i++;
			position++;		
		}		

	}

	printf("\nTHE EXPRESSION STRUCTURE IS(after lexing):");
	printf("\n(DATATYPE,VALUE)");
	for(int i=0;i<token_cnt;i++){
		printf("\n (%d,%c)",exp_info[i].d_type,exp_info[i].value);
	}
	
	int success=parse(exp_info,token_cnt);	
	if(success)
		printf("\nFORMAT MATCHES");
	else
		printf("\nFORMAT DOSEN'T MATCHES");
	
}
