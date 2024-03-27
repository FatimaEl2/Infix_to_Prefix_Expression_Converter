#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    char exp;
    struct node *next;
} stack;

// This function prints the menu to the user
int menu(void)
{
    int choice;
    printf("\n\t\t\t\t\t\t\t\t***-----welcome-----***\n\t\t\t\t1-Print the expression.\n\t\t\t\t2-Is the infix expression balanced?\n\t\t\t\t3-Reverse the infix expression.\n\t\t\t\t4-Convert the infix to prefix.\n\t\t\t\t5-Quit.\n\t\t\t\tPlease enter your Choice--> ");
    scanf("%d", &choice);
    return choice;
}

// This function allow us to find the size of both the infix array and prefix array
int size_of_array(FILE*infp,int* size_prefix){
  int size_arr,cnt=0,count=0;
  char c;
  fseek(infp,0,0);
  do{
     c=fgetc(infp);
     if(c=='(' || c==')')
     cnt++;
     else
     count++;
  
  }while(c!=EOF);

  size_arr=count+cnt;
  *size_prefix=count;

   return size_arr;
 }

//this function prints to the user the infix expression in the file
void print_infix(FILE *infp)
{
    char *line;
    line = (char *)calloc(100, sizeof(char));
    fseek(infp,0,0);
    fscanf(infp, "%s", line);
    printf("%s\n", line);
}

//This function loads the content of the file into the array(caracter by caracter)
void load_array(FILE *infp, char *arr)
{
  char ch;
    int i = 0;
    fseek(infp,0,0);
    ch=fgetc(infp);
    while(ch != EOF){
        arr[i]=ch;
        ch=fgetc(infp);
        i++;
    }
    arr[i]='\0';
}

//This function pushes the element send to it into the stack
void push(stack *add, stack **top)
{
    if (*top == NULL)
    {
        *top = add;
    }
    else
    {
        add->next = *top;
        *top = add;
    }
}

//This function pops the element from the stack
stack* pop(stack **top)
{
    stack *temp;
    if (*top == NULL)
    {
        return NULL;
    }
    else
    {
        temp = *top;
        *top = (*top)->next; 
    }
    return temp;
}

// This function creates a node and fill its content with the element exist in an array of a spesific index
stack* new_node(char*arr,int i){
    stack* newnode;
    newnode = (stack *)malloc(sizeof(stack));
    newnode->exp = arr[i];
    newnode->next = NULL;
    return newnode;
}

 //This function checks if the expression loaded in the array is balenced or not
int infix_balanced(stack **top, char *arr)
{
    int i = 0,flag=0;
    stack*newnode,*element;
    
    do
    {
        
        if (arr[i] == '(')
        {
          
            newnode = new_node(arr,i);
            push(newnode,top);
            
        }
        else if (arr[i] == ')')
        {
          
            if ((*top)->exp == '(')
            {
                
                element=pop(top);
            }
            else
            {
                flag=1;
                break;
            }
        }
        i++;
    } while (arr[i]!='\0');

    if (*top==NULL && flag==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

 //This function reverses the content of the array using a stack
int reverse_infix(stack**top,char *arr)
{
    stack*newnode,*element=NULL;
    int i=0;
   
    while(arr[i]!='\0'){
        newnode = new_node(arr,i);
        push(newnode,top);
        i++;
    }

   i=0;
    while(*top!=NULL){
        element=pop(top);
        arr[i]=element->exp;
        i++;
    }
  arr[i]='\0';
    return 1;
}

//this function checks the priority 
int priority (char ch){
 if (ch=='*' || ch=='/')
 return(3);
 else if (ch=='+' || ch=='-')
 return(2);
 else if ( ch==')')
 return(1);
else
 return(0);
}

//this function convert an infix expression to a prefix notation using stack
void convert_to_prefix(char* arr, char* prefix,stack** top ){
  int i,j=0;
  stack*ToAdd,*popped;
    for(i=0 ; i<strlen(arr) ; i++){
        if(isalpha(arr[i])!=0)
          prefix[j++]=arr[i];
      
        else if(arr[i]==')'){
           ToAdd= new_node(arr,i);
           push(ToAdd,top);
        }
        else if(arr[i]=='('){
          do{
            popped=pop(top);
            if(popped->exp!=')')
             prefix[j++]=popped->exp;
          } while(popped->exp!=')');
        }
      
        else if(arr[i]=='*' || arr[i]=='/'|| arr[i]=='-' || arr[i]=='+'){
            if(*top!=NULL && priority (arr[i]) >= priority ((*top)->exp)){
             ToAdd= new_node(arr,i);
             push(ToAdd,top);
            }
            else {
              while(*top!=NULL){
                 if(priority (arr[i]) >= priority ((*top)->exp) || (*top)->exp=='(')
                  break;
                 else{
                   popped=pop(top);
                   prefix[j++]=popped->exp;
                 }
              }
              ToAdd= new_node(arr,i);
              push(ToAdd,top);
           }
      }
  }  
      while(*top!=NULL){
           popped=pop(top);
           prefix[j++]=popped->exp;
      }
      prefix[j]='\0';
      reverse_infix(top,prefix); 
}


int main(void)
{
    int choice,size_arr,size_prefix, i = 0,bl=2,rev=2;
    char c;
    stack *top = NULL;
    char *arr,*prefix; 

      

    FILE *infp;
    infp = fopen("infix.txt", "r");
    if(infp==NULL)
      printf("\n Sorry, the file is NOT FOUND!!");
    else{
       size_arr=size_of_array(infp,&size_prefix);
       arr=(char*)calloc(size_arr,sizeof(char));
        prefix=(char*)calloc(size_prefix,sizeof(char));

    do
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            
            print_infix(infp);
            break;
        case 2:
            load_array(infp,arr);
            bl=infix_balanced(&top,arr);
            if(bl==1){
                printf("The expression is balanced.");
            }
            else{
                printf("The expression is not balanced.\nThe program is done.");
                bl=0;
            }
            break;
        case 3:
            if(bl==2){
                printf("Please, make sure to select option 2 before trying option 3."); 
            }
            else if(bl==1){
                rev=reverse_infix(&top,arr);
                printf("%s", arr);
            }
            break;
        case 4:
            if(rev==2){
                printf("Please, make sure to select option 3 before trying option 4.");
            }
            else if(rev==1){
                convert_to_prefix(arr,prefix,&top);
                printf("%s",prefix);
            }
            break;
        case 5:
            printf("\n\t You are DONE!!\n\t***** Thank you :) *****\t\n");
            break;

        default:
            printf("\n\t\t\t\t\t\t/!\\UNVALID CHOICE/!\\\n");
            scanf("%c", &c);
            break;
        }
        scanf("%c", &c);
        if(choice!=5&& bl!=0){
            printf("\nDo you want to continue?(Y/N)");
            scanf("%c", &c);
        }
        else{
            c='N';
        }

    } while (c != 'N');
    fclose(infp);
    }
    return 0;
}