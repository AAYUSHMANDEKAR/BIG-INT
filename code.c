#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum{MINUS,PLUS} sign;
typedef struct BigInt_type
{
    int *arr;//pointer to array consisting of digits
    int length;
    int sign;
}BigInt;

int compareNum(BigInt num1 , BigInt num2);
BigInt Add(BigInt num1 , BigInt num2);
BigInt Sub(BigInt num1 , BigInt num2);
BigInt Mul(BigInt num1,BigInt num2);
void Print(BigInt num);
BigInt GetInt();

int main()
{
    BigInt num1,num2,num3,num4,num5;
    num1 = GetInt();
    Print(num1);
    num2 = GetInt();
    Print(num2);
    printf("ADDITION IS ->");
    num3 = Add(num1,num2);
    Print(num3);
    num4 = Sub(num1,num2);
    printf("SUBTRACTION IS ->");
    Print(num4);
    printf("MUL IS ->");
    num5 = Mul(num1,num2);
    Print(num5);
}

BigInt GetInt()
{
    BigInt num;
    char *str;
    str = (char*)malloc(sizeof(char)*310);
    num.sign = PLUS;
    
    printf("Enter number\n");
    gets(str);
    if(str[0] == '-')
    {
        num.sign = MINUS;
    }
    int n = strlen(str);
    
    if(num.sign == PLUS)
    {   
        int *a = (int *)malloc(sizeof(int)*n);
        for(int i = 0; i < n ; i++)
        {
            a[i] = str[n-i-1] - '0';//storing values in array
        }
        num.arr = a;
        num.length = n;
    }   
    else
    {
        int *a = (int *)malloc(sizeof(int)*(n-1));
        for(int i = 0; i < n-1 ; i++)
        {
            a[i] = str[n-i-1] - '0';
        }
        num.length = n-1;
        num.arr = a;
    } 
    return num;
}

//returns 0 if same,<0 if num1 is less
//>0 if num1 is greater
int compareNum(BigInt num1 , BigInt num2)
{
    int ret_val;
    if(num1.length > num2.length)
    {
        ret_val = 1;
    }
    else if(num1.length < num2.length)
    {
        ret_val = -1;
    }
    else
    {
        int i = num1.length - 1;// or num2.length -1 i.e same
        while(i >= 0 && num1.arr[i] == num2.arr[i] )
        {
            i--;
        }
        if(i >= 0 && num1.arr[i] > num2.arr[i])
        {
            ret_val = 1;
        }
        else if(i >= 0 && num1.arr[i] < num2.arr[i])
        {
            ret_val = -1;
        }
        else
        {
            ret_val = 0;
        }
    }
    return ret_val;
}

BigInt Add(BigInt num1 , BigInt num2)
{
    BigInt num3;
    int n = num1.length ;
    int m = num2.length ;
    int i = 0;
    if(n > m)
    {
        num3.arr = (int *)malloc(sizeof(int)*(n+1));
        num3.length = n+1;
    }
    else
    {
        num3.arr = (int *)malloc(sizeof(int)*(m+1));
        num3.length = m+1;
    }
    while(i < num3.length)
    {
        num3.arr[i] = 0;
        i++;
    }
    i = 0;
    if(num1.sign == num2.sign)
    { 
        int carry = 0;
        int sum;
        num3.sign = num1.sign;
        while( i < m && i < n )
        {
            sum = num1.arr[i] + num2.arr[i] + carry;
            num3.arr[i] += sum%10;
            carry = sum/10;
            if(i == num3.length - 1 && carry > 0)
            {
                printf("LIMIT EXCEEDED\n");
            }
            //printf(" in add %d\n",num3.arr[i]);
            i++;
        }
        while(i < m)
        {
            sum = carry + num2.arr[i];
            carry = sum/10;
            num3.arr[i] = sum % 10;   
            //printf(" in add %d\n",num3.arr[i]);
            i++;
        }
        while(i < n)
        {
            sum = carry + num1.arr[i];
            carry = sum/10;
            num3.arr[i] = sum %10;
            //printf(" 2.in add %d\n",num3.arr[i]);
            i++;
        }
    }
    else
    {
        int cmp = compareNum(num1,num2);
        num2.sign = num1.sign;
        num3 = Sub(num1,num2);
        if(cmp >= 0)
        {
            num3.sign = num1.sign;
        }
        else
        {
            if(num1.sign == PLUS)
            {
                num3.sign = MINUS;
            }
            else
            {
                num3.sign = PLUS;
            }
        }
    }    
    return num3;
}

// always larger no will be sent first as parameter in size
BigInt Sub(BigInt num1 , BigInt num2)
{
    BigInt num3;
    if(num1.sign == num2.sign)
    {
        int n = num1.length ;
        int m = num2.length ;
        int i = 0;
        int *a;
        if(n > m)
        {
            a = (int *)malloc(sizeof(int)*n);
            num3.length = n;
        }
        else
        {
            a = (int *)malloc(sizeof(int)*m);
            num3.length = m;
        }
        num3.arr = a;
        while(i < num3.length)
        {
            num3.arr[i] = 0;
            i++;
        }
        int cmp = compareNum(num1,num2);
        i = 0;
        if(cmp > 0)
        {
            while(i < n && i < m) 
            {
                if(num1.arr[i] >= num2.arr[i] )
                {
                    num3.arr[i] = num1.arr[i] - num2.arr[i];
                }
                else
                {   
                    if(i < n -1)
                    {
                        num1.arr[i+1]--;
                    }
                    num1.arr[i] = num1.arr[i] + 10;
                    num3.arr[i] = num1.arr[i] - num2.arr[i];
                }
                i++;
            }
            while (i < n)
            {
                if(num1.arr[i] >0)
                {
                    num3.arr[i] = num1.arr[i];
                }
                else
                {
                    if( i < n -1)
                    {
                        num1.arr[i+1]--;
                        num1.arr[i] += 10;
                        num3.arr[i] = num1.arr[i];
                    }
                }
                i++;

            }
            num3.sign = num1.sign;
        }
        else if(cmp < 0)
        {
            while(i < n && i < m)
            {
                if(num2.arr[i] >= num1.arr[i])
                {
                    num3.arr[i] = num2.arr[i] - num1.arr[i];
                }
                else
                {
                    num2.arr[i+1]--;
                    num2.arr[i] = num2.arr[i] + 10;
                    num3.arr[i] = num2.arr[i] - num1.arr[i];
                }
                i++;
            }
            while(i < m)
            {
                if(num2.arr[i] > 0)
                {
                    num3.arr[i] = num2.arr[i];
                }
                else
                {
                    if( i < m -1)
                    {
                        num2.arr[i+1]--;
                        num2.arr[i] += 10;
                        num3.arr[i] = num2.arr[i];
                    }
                }
                i++;
            }
            if(num2.sign == PLUS)
            {
                num3.sign = MINUS;
            }
            else
            {
                num3.sign = PLUS;
            }
        }
        else
        {
            num3.length = 1;
        }
    }
    else
    {
        num2.sign = num1.sign;
        num3 = Add(num1,num2);
        num3.sign = num1.sign;
    }
    return num3;
}

void Print(BigInt num)
{
    int i = num.length - 1;
    if(num.length <= 309)
    {
        if(num.sign == MINUS)
        {
            printf("-");
        }
        while(num.arr[i] == 0)
        {
            i--;
        }
        if(i == -1)
        {
            printf("0");
        }
        while(i >= 0)
        {
            printf("%d",num.arr[i]);
            i--;
        }
        printf("\n");
    }
}

BigInt Mul(BigInt num1,BigInt num2)
{
    BigInt num3;
    int *a;
    num3.length = num1.length + num2.length;
    a = (int *)malloc(sizeof(int)*(num3.length));
    num3.arr = a;
    int i = 0,j = 0;
    if(num3.length > 309)
    {
        printf("LIMIT EXCEEDED\n");
    }
    else
    {
        while(i < num3.length)
        {
            num3.arr[i] = 0;
            i++;
        }
        int prod,carry;
        for(i = 0 ; i < num1.length; i++)
        {
            carry = 0;
            for( j = 0 ; j < num2.length; j++)
            {
                prod = num1.arr[i]* num2.arr[j] + carry;
                num3.arr[i + j] += prod%10;
                carry = prod/10;
                if(num3.arr[i+j] > 9)
                {
                    num3.arr[i+j+1] += 1;
                    num3.arr[i+j] = num3.arr[i+j]%10;
                }
            }
            while(carry != 0)
            {
                num3.arr[i+j] += carry%10;
                if(num3.arr[i+j] > 9)
                {
                    num3.arr[i+j+1] += 1;
                    num3.arr[i+j] = num3.arr[i+j]%10;
                }
                carry = carry/10;
                j++;
            }
            
        }  
            if(num1.sign == num2.sign)
            {
                num3.sign = PLUS;
            }  
            else
            {
                num3.sign = MINUS;
            }        
    }
    return num3;
}
