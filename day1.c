#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

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

struct info_about_tokens stack[10];
int top=-1;

void push(struct info_about_tokens *ptr){

	top++;	
	stack[top].d_type=ptr->d_type;
	stack[top].value=ptr->value;
	
}
struct info_about_tokens* pop(){
	struct info_about_tokens *temp;
	temp=&stack[top];
	top--;
	return temp;
}

struct node{
	int d_type;
	char value;
	struct node* left;
	struct node* right;	
};
struct node *pointer_stack[10];
int AST_top=-1;

void push_AST(struct node *holding_ptr){
	AST_top++;
	pointer_stack[AST_top]=holding_ptr;
}

struct node* pop_AST(){
		struct node *p=pointer_stack[AST_top];		
		AST_top--;
	return p;
}
struct info_about_tokens new_postfixed[10];//conntains the postfixed array
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
void print_info_struct(struct info_about_tokens *loopptr,int token_cnt){
	for(int i=0;i<token_cnt;i++){
		printf("\n(%d %c)",loopptr->d_type,loopptr->value);
		loopptr++;
	}
}
void print_postfix(struct info_about_tokens *loopptr,int token_cnt){
	for(int i=0;i<token_cnt;i++){
		printf("%c",loopptr->value);
		loopptr++;
	}
}
int isoperand(int data_type){
	if(data_type==DIGIT)
		return 1;
	else
		return 0;
}

int isoperator(int data_type){
	if((data_type==PLUS)||(data_type==MINUS)||(data_type==MULTIPLY)||(data_type==DIVIDE))
		return 1;
	else
		return 0;
}
int check_precedence(int operator_val){
	return 1;	//heres a bug need to fix
}



struct info_about_tokens* postfix(struct info_about_tokens *postfix_ptr,int token_cnt){
	struct info_about_tokens *temp_ptr;
	
	//need to create another structure to hold the postfixed value	
	
	temp_ptr=new_postfixed;
	int new_index=0;
	for(int i=0;i<token_cnt;i++){	
		if(isoperand(postfix_ptr->d_type)){			
			new_postfixed[new_index].d_type=postfix_ptr->d_type;		
			new_postfixed[new_index].value=postfix_ptr->value;
			new_index++;
		}
		else if(isoperator(postfix_ptr->d_type)){
			printf("\nisoperator");
			int ok_to_push=check_precedence(postfix_ptr->value);//ret 1 if greater precedence
			if(ok_to_push){
				push(postfix_ptr);
			}
			else{
		/*		while((ok_to_push=check_precedence(postfix_ptr->value))!=1){
					struct info_about_token *hold=pop();
					new_postfixed[new_index].d_type=hold->d_type;
					new_postfixed[new_index].value=hold->value;
					new_index++;
				}
		*/	
			printf("\tout of scope");
			}
		}
		postfix_ptr++;	
	}
	while(top>=0){//why >= as need also the value of 0 location of stack
		struct info_about_tokens *hold=pop();
		
		new_postfixed[new_index].d_type=hold->d_type;
		new_postfixed[new_index].value=hold->value;
		new_index++;
	}	

	return temp_ptr;
}

struct node* AST(struct info_about_tokens *ptr_struct,int token_cnt){

	ptr_struct=postfix(ptr_struct,token_cnt);
	printf("\v\v\t\tPOSTFIX EXPRESSION IS:");
	print_postfix(ptr_struct,token_cnt);

	struct info_about_tokens *loopptr=ptr_struct;
	
	
	for(int i=0;i<token_cnt;i++){
		if(isoperator(loopptr->d_type)){	
			//CREATE A STRUCTURE ,FILL THE VALUES
			struct node *ptr_to_node;
			ptr_to_node=malloc(sizeof(struct node));		
			ptr_to_node->d_type=loopptr->d_type;
			ptr_to_node->value=loopptr->value;//note=the values are in character,while eval. convert to integer
	
			//POP FROM AST ASSIGN TO LEFT AND RIGHT
			ptr_to_node->right=pop_AST();
			ptr_to_node->left=pop_AST();

			push_AST(ptr_to_node);//pass the pointer POINTING TO '+' 
			
		}
		else{
			printf("\n\n\nfoo");
			struct node *ptr_to_node;
			ptr_to_node=malloc(sizeof(struct node));
		
			ptr_to_node->d_type=loopptr->d_type;
			ptr_to_node->value=loopptr->value;//note=the values are in character,while eval. convert to integer
			ptr_to_node->left=NULL;
			ptr_to_node->right=NULL;
		
//			ptr_to_node=&new_node;	//points the pointer to newly created node
			push_AST(ptr_to_node);//pass the pointer to push
		}
	loopptr++;
	}
	
	
	
	struct node *ROOT;
	ROOT=pop_AST();
	return ROOT;
}
void inorder(struct node *alias_root){
	if(alias_root==NULL)
		return ;
	
	inorder(alias_root->left);

	printf("\n%c",alias_root->value);
	
	inorder(alias_root->right);

}
int main(void){
	
	char input_expression[30];
	struct info_about_tokens exp_info[10];
	struct node *root;//pointer to the printing structure
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
	if(success){
		printf("\nFORMAT MATCHES");
		root=AST(exp_info,token_cnt);			
		inorder(root);
				
	}
	else
		printf("\nFORMAT DOSEN'T MATCHES");
	
}
