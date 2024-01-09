// #include<stdio.h>
// #include<stdbool.h>
#include<iostream>
using namespace std;

int RandomGen(int iNumber)
{
    int iNo=iNumber;
    int iCopy=iNo;

    int iDigit=0,iCnt=0;

    while(iCopy!=0)
    {
        iDigit=iCopy%2;
        iCopy=iCopy/2;
        iCnt++;
     
    }
    //printf("Number of bits are: %d\n",iCnt);
    
    int iTemp=iNo;
    int iRes1=0;
    int iRes2=0;
    int iMask1=0X00000001;
    int iMask2=0X00000001;
    int iShift=0X00000001;

    iMask2=iMask2<<iCnt-1;

    iRes1=iNo&iMask1;
    iRes2=iNo&iMask2;

    if(iRes1==iMask1)
    {
        iRes1=1;
    }
    else
    {
        iRes1=0;
    }

    if(iRes2==iMask2)
    {
        iRes2=1;
    }
    else
    {
        iRes2=0;
    }

    int exor=iRes1^iRes2;

    exor=exor<<iCnt-1;
    
    iTemp=iTemp>>1;

    iTemp=iTemp^exor;
    
    return iTemp;
}

int main()
{

    printf("\n\tWelcome to random Number guessing game:\t\n ");
        int iValue=0;
        int iRange=0;
        int iRet=0,iGuess=0,iPress=0;
        bool bCont=false;
        char cOption='\0';
    do{
        
        // printf("\nSelect a Range for number: \n");
        // printf("\n1. 0 to 100\n2. 0 to 500 \n3. 0 to 1000\n4. 0 to 100000\n");
        // scanf("%d",&iRange);

        // switch (iRange)
        // {
        // case 1:
        //     /* code */
        //     printf("Enter a number between range to start the game: ");
        //     scanf("%d",&iValue);
        //     break;
        // case 2:
        //     /* code */
        //     printf("Enter a number between range to start the game: ");
        //     scanf("%d",&iValue);
        //     break;
        // case 3:
        //     /* code */
        //     printf("Enter a number between range to start the game: ");
        //     scanf("%d",&iValue);
        //     break;
        // case 4:
        //     /* code */
        //     printf("Enter a number between range to start the game: ");
        //     scanf("%d",&iValue);
        //     break;
        
        // default:
        //     printf("ERROR! Select a valid range: ");
        //     break;
        // }
        printf("Enter a number  to start the game: ");
        scanf("%d",&iValue);
         iRet=RandomGen(iValue);

           //printf("New number is: %d",iRet);

        do{
            printf("\nMake a guess \n");
            scanf("%d",&iGuess);
            if(iRet==iGuess)
            {
                printf("\nCorrect Guess!!!\n");
                printf("\nDo you wish to continue? y/n \n");
                scanf(" %c",&cOption);
                if(cOption=='y')
                {
                    bCont=true;
                   
                }
                else
                {
                    bCont=false;
                }

            }
            else
            {
                printf("\nTry Again\n");
                printf("\nDo you wish to continue? y/n \n");
                scanf(" %c",&cOption);
                if(cOption=='n')
                {
                    iGuess=iRet;
                    bCont=false;
                }
            }
        }while(iRet!=iGuess);

    }while(bCont==true);


    return 0;
}