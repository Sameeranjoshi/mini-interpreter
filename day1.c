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
int operator(int data_type){
	//operator:PLUS|MINUS|MULTIPLY|DIVIDE
	if((data_type==PLUS)||(data_type==MINUS)||(data_type==MULTIPLY)||(data_type==DIVIDE))
		return 1;
	else
		return 0;
}
int factor(int data_type){
	//factor:INTEGER|ALPHABET|VARIABLE
	printf("\tfactor called");
	if(data_type==DIGIT)
		return 1;
	else 
		return 0;
}
int term(struct info_about_tokens *ptr,int token_cnt,int globalindex){
	printf("\tterm called");
	/*
		term:factor (((mul)|(div))factor)*
	*/	

	int isvalid;
	
	isvalid=factor(ptr->d_type);
	if(isvalid){
		
		token_cnt--;
		ptr++;
		globalindex++;			//goes to next ele
		/*this checks for the initial condition (ex.INPUT = 2)(this saves you!!)
		*/
//		if(token_cnt==0)
//			return 0;
		
		while(token_cnt!=0){
			//if operator matches
			
			if((ptr->d_type==MULTIPLY)||(ptr->d_type==DIVIDE))
			{
				printf("\tOPERATOR MATCH FOUND");
				ptr++;
				token_cnt--;
				if(factor(ptr->d_type)){//now the 2nd para matches
					ptr++;
					token_cnt--;

			//why 2 times?as we check DIGIT OPERATOR then only increase the count else invalid
					globalindex++;
					globalindex++;
				}
				else
					return (-1);	//-1 for no match
			}
			else if((ptr->d_type==PLUS)||(ptr->d_type==MINUS)){
				return globalindex;//ex like = 2+
			}
			else{
				return (-1);		//ex. like = 2 3
			}
		
		}
	return globalindex;
	
	}
	else{
		return (-1);
	}


}
int expr(struct info_about_tokens *ptr,int token_cnt){//remaining to complete
	printf("\texpr called");

	struct info_about_tokens *start_address=ptr;
	int isvalid,globalindex=0;
	globalindex=term(ptr,token_cnt,globalindex);
	printf("\nINSIDE EXPR GLOBALINDEX IS :%d\nprinting array",globalindex);
	for(int i=0;i<token_cnt;i++)
		printf("\n%d",ptr[globalindex].value);

//	printf("\nprt is %d index is %d",ptr,globalindex);
	ptr=start_address+globalindex;		//take ptr ahead

//	printf("\nprt is %d index is %d",ptr,globalindex);

	printf("\n%d %c ",ptr->d_type,ptr->value);
	
	int save;
	if(globalindex!=-1){
//				printf("\ndatatype%c %d globalindex %d",ptr[globalindex-1].value,ptr->d_type,globalindex);
		while(globalindex<token_cnt){
			if((ptr->d_type==PLUS)||(ptr->d_type==MINUS)){
				globalindex++;
				printf("\nsameeran %d",globalindex);
			    if(globalindex<token_cnt){
					if(factor(start_address[globalindex].d_type)){
						printf("trapped");
						globalindex++;
					}
					else{	
						printf("\nin else %d",globalindex);
						return 0;	
					}
			    }		
			    else{
				return 0;//if like e.x=2+ and string ends after +
			    }			
			}
			else{
				return 1;//the term(...)* the expression in () isnottrue	
			}
		}
		return 1;//this says the term has already checked all(ex. 2*3*5)
	}
	else{
		return 0;//term says the expression is wrong
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
	printf("\n(DATATYPE,VALUE)\n1=DIGIT\n3=PLUS\n4=MINUS\n5=MULTIPLY\n6=DIVIDE");
	for(int i=0;i<token_cnt;i++){
		printf("\n (%d,%c)",exp_info[i].d_type,exp_info[i].value);
	}
	
	int success=expr(exp_info,token_cnt);
	if(success)
		printf("\nFORMAT MATCHES");
	else
		printf("\nFORMAT DOSEN'T MATCHES");
	
}
