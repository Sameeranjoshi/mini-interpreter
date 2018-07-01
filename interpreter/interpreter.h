

#define NONE_OF_THESE 0
#define DIGIT 1
#define PLUS 3
#define MINUS 4
#define MULTIPLY 5
#define DIVIDE 6
#define LPAREN 7
#define RPAREN 8


extern int top;
extern int AST_top;
struct info_about_tokens{
	int d_type;
	char value;		//beaware it's in char when value needed for evaluation parse it!
};

struct info_about_tokens stack[30];



struct node{
	int d_type;
	char value;
	struct node* left;
	struct node* right;	
};
struct node *pointer_stack[30];



struct info_about_tokens new_postfixed[30];//conntains the postfixed array


//------------------------------------------function declarations--------------------------------------------------
extern void push(struct info_about_tokens *ptr);
extern void push_AST(struct node *holding_ptr);
extern void gettoken(char *position,struct info_about_tokens *ptr_to_str);
extern int validate(int data_type,int identifier);
extern int operator(int data_type);
extern int factor(int data_type,int globalindex);
extern int expr(struct info_about_tokens *ptr,int token_cnt,int globalindex);
extern int term(struct info_about_tokens *ptr,int token_cnt,int globalindex);
extern void print_info_struct(struct info_about_tokens *loopptr,int token_cnt);
extern void print_postfix(struct info_about_tokens *loopptr,int cnt_except_paren);
extern int isoperand(int data_type);
extern int isoperator(int data_type);
extern int isparen(int data_type);
extern int check_precedence(char operator_val);
extern struct info_about_tokens* postfix(struct info_about_tokens *postfix_ptr,int token_cnt);
extern struct node* AST(struct info_about_tokens *ptr_struct,int token_cnt,int cnt_except_paren);
extern void inorder(struct node *alias_root,int space);
extern int eval(struct node *alias_root);
