#include<stdio.h>
int UnusualGCD( int a, int b)
{
    if(a==b)
        return a;
    else if((a%11 == 0) && (b%11 == 0))
        return 11*UnusualGCD(a/11,b/11);
    else if((a%11 == 0) && (a%2 != 0) && (b%11 != 0))
        return UnusualGCD(a/11, 2*b);
    else if((a%11 == 0) && (a%2 == 0) && (b%11 != 0))
        return UnusualGCD(a/11, a>b?a-b:b-a);
    else if((b%11 == 0) && (b%2 != 0) && (a%11 != 0))
        return UnusualGCD(2*a, b/11);
    else if((b%11 == 0) && (b%2 == 0) && (a%11 != 0))
        return UnusualGCD(a>b?a-b:b-a, b/11);
    else UnusualGCD(a>b?a-b:b-a, a<b?a:b);
}

int CorrectGCD(int x, int y){
  if(y == 0) return x;
  else return CorrectGCD(y, x%y);
}

int main()
{
    int i,j, a, b, range, flag = 0;
    printf("Enter Two Numbers: ");
    scanf("%d%d", &a, &b);
    printf("%d", UnusualGCD(a,b));
    /*printf("\nTo Prove Correctness of the Algorithm, checking the range from 1 to ");
    scanf("%d", &range);
    for(i= 1;i<=range;i++)
    {
        for(j=1; j<= range; j++)
        {
                if (UnusualGCD(i,j) != CorrectGCD(i,j))
                {
                        printf("GCD of %d, %d is %d \n", i, j, UnusualGCD(i,j));
                        flag = 1;
                }
        }  
    }
    if(flag == 0)
        printf("The Algorithm in correct for every pair in range from 1 to %d", range);
    else printf("The Algorithm is correct"); */   
    return 0;
}