#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

struct Stack1
{
    char op;
    struct Stack1 *next;
};

struct Stack2
{
    int val;
    struct Stack2 *next;
};

//Stack1 for operators
void Push(struct Stack1 **Head,char ch)
{
    struct Stack1 *newn=NULL;
    newn=(struct Stack1 *)malloc(sizeof(struct Stack1));

    newn->op=ch;
    newn->next=NULL;

    if(*Head==NULL)
    {
        *Head=newn;
    }
    else
    {
        newn->next=*Head;
        *Head=newn;
    }
}

char Pop(struct Stack1 **Head)
{
    struct Stack1 *temp=*Head;
    char cValue='\0';
    if(*Head==NULL)//if Stack1 is empty
    {
        return -1;
    }
    
    else
    {   
        cValue=(*Head)->op;
        *Head=(*Head)->next;
        free(temp);
    }
    return cValue;
}

/*----------------------------------------------------------------------------------------------*/
//Stack2 for Operands
void PushNum(struct Stack2 **Head,int No)
{
    struct Stack2 *newn=NULL;
    newn=(struct Stack2 *)malloc(sizeof(struct Stack2));

    newn->val=No;
    newn->next=NULL;

    if(*Head==NULL)
    {
        *Head=newn;
    }
    else
    {
        newn->next=*Head;
        *Head=newn;
    }
    
}

int PopNum(struct Stack2 **Head)
{
    struct Stack2 *temp=*Head;
    int iValue=0;
    if(*Head==NULL)//if Stack2 is empty
    {
        return -1;
    }
    
    else
    {   
        iValue=(*Head)->val;
        *Head=(*Head)->next;
        free(temp);
    }
    return iValue;
}


/*----------------------------------------------------------------------------------------------*/
//Display for Operators
void Display(struct Stack1 *show)
{
    while(show!=NULL)
    {
        //printf("| %c | -> ",show->op);
        show=show->next;
    }
    //printf("NULL");
}

/*----------------------------------------------------------------------------------------------*/

//Display for Operands
void DisplayNum(struct Stack2 *show)
{
    
    while(show!=NULL)
    {
        //printf("| %d | -> ",show->val);
        show=show->next;
    }
    //printf("NULL");
    printf("\n\n");
}


int getPrecedence(char op)
{
    int precedence=0;
    if(op=='+' || op=='-')
    {
        precedence=1;
    }
    if(op=='*' || op=='/')
    {
        precedence=2;
    }
    return precedence;
}

bool CheckPrecedence(struct Stack1 *Sign,char ch)
{
    int get=getPrecedence(ch);
    if(Sign==NULL )
    {
        return true;
    }
    else if(get>=getPrecedence(Sign->op))
    {
        return true;
    }
    else
    {
        return false;
    }

}


void PerformPrecedenceOperation(struct Stack1 **Sign,struct Stack2 **Num)
{
    //printf("\nEntered this function\n");
    int iNo1=0,iNo2=0,iResult=0;
    char ch='\0';
    while((*Sign)!=NULL && (*Sign)->op!='(')
    {
        iNo1=PopNum(Num);
        iNo2=PopNum(Num);
        ch=Pop(Sign);
        if(ch=='(')
        {
            break;
        }

        switch (ch)
        {
            case '+':
                iResult=iNo1+iNo2;
                break;
            case '-':
                iResult=iNo2-iNo1;
                break;
            case '*':
                iResult=iNo2*iNo1;
                break;
            case '/':
                iResult=iNo2/iNo1;
                break;
        
            default:
                break;
        }
        PushNum(Num,iResult);
    }
    //printf("\nResult is %d\n",iResult);
}

void ProcessCommand(char *str,struct Stack1 **Sign,struct Stack2 **Num)
{
    int data=0,iNo=0,iCnt=0,iLen=0;
    iLen=strlen(str);
    bool bCheck=false;
    char ch='\0';
    for(iCnt=0;iCnt<iLen;iCnt++)
    {
        int iNo=0;
        if((*str)>='0' && (*str)<='9')
        {
            while((*str)>='0' && (*str)<='9')
            {
                data=(*str)-'0';
                iNo=(iNo*10)+data;
                str++;
            }
            PushNum(Num,iNo);
        }

        if(((*str)=='+') ||  ((*str)=='-') || ((*str)=='*') || ((*str)=='/'))
        {
            ch=(*str);
            bCheck=CheckPrecedence(*Sign,ch);
            if(bCheck==true)
            {
                Push(Sign,ch);
            } 
            else
            {
                PerformPrecedenceOperation(Sign,Num);
                Push(Sign,ch);
            }
        }
        if((*str)=='(')
        {
            Push(Sign,'(');
        }
        if((*str)==')')
        {
            while((*Sign)!=NULL && (*Sign)->op!='(')
            {
                PerformPrecedenceOperation(Sign,Num);
            }
            Pop(Sign);
        }

        if(iCnt<iLen-1)
        {
            str++;
        }
          
    }
}

int PerformFinal(struct Stack1 **Sign,struct Stack2 **Num)
{
    char ch='\0';
    int iNo1=0,iNo2=0,iResult=0;

    while((*Sign)!=NULL)
    {
        iNo1=PopNum(Num);
        iNo2=PopNum(Num);
        ch=Pop(Sign);

       switch (ch)
       {
        case '+':
                iResult=iNo2+iNo1;
            break;
        case '-':
                iResult=iNo2-iNo1;
            break;
        case '*':
                iResult=iNo2*iNo1;
            break;
        case '/':
                iResult=iNo2/iNo1;
            break;
        
        default:
            break;
       }
        PushNum(Num,iResult);
    }
    return iResult;

}

int main()
{
    struct Stack1 *Operator=NULL;
    struct Stack2 *Operand=NULL;

    char calc[100];
    int iRet=0;
    printf("\nEnter a calculation:  ");
    scanf("%[^'\n']s",calc);


    ProcessCommand(calc,&Operator,&Operand);
    Display(Operator);
    printf("\n\n");
    DisplayNum(Operand);

    iRet=PerformFinal(&Operator,&Operand);

    printf("\nThe result is %d",iRet);

    return 0;
}