#include <stdio.h>
#include <string.h>

#define INT_MAX	2147483647
#define INT_MIN	-2147483648

int count1s(int N);
int ADD(int* S,int indexF, int index1, int index2);
int SUB(int* S,int indexF, int index1, int index2);
int AND(int* S,int indexF, int index1, int index2);
int XOR(int* S,int indexF, int index1, int index2);
int OR(int* S,int indexF, int index1, int index2);

int ADDI(int* S,int indexF, int index1, int number);
int SUBI(int* S,int indexF, int index1, int number);
int ANDI(int* S,int indexF, int index1, int number);
int XORI(int* S,int indexF, int index1, int number);
int ORI(int* S,int indexF, int index1, int number);

void SWP(int* S,int index1, int index2);
void DUMP_REGS(int* S);
void DUMP_REGS_F(int* S);
void INPUT(int*S);
void OUTPUT(int*S);


void update_reg(int*SR , int var)
{
    if (var < 0)
        SR[2] = 1;
    else
        SR[2] = 0;
    if(var == 0)
        SR[1] = 1;
    else
        SR[1] = 0;
    if(count1s(var)%2 == 0)
        SR[0] = 0;
    else
        SR[0] = 1;
}
int main()
{
    return 0;
}

int count1s(int N)
{
    int count1 = 0;
 
     while (N > 0) {
 
        if (N & 1) {
            count1++;
        }
        // remove one binary from right 
        N = N >> 1;
    }
    return count1;
}
int ADD(int* S,int indexF, int index1, int index2)
{
    if (((*(S+index1) + *(S+index2)) > INT_MAX) || ((*(S+index1) + *(S+index2)) < INT_MIN))
    {
        return 1;
    }
    *(S+indexF) = *(S+index1) + *(S+index2);
    return 0;
}
int SUB(int* S,int indexF, int index1, int index2)
{
    if (((*(S+index1) - *(S+index2)) > INT_MAX) || ((*(S+index1) - *(S+index2)) < INT_MIN))
    {
        return 1;
    }
    *(S+indexF) = *(S+index1) - *(S+index2);
    return 0;
}
int AND(int* S,int indexF, int index1, int index2)
{
    if (((*(S+index1) & *(S+index2)) > INT_MAX) || ((*(S+index1) & *(S+index2)) < INT_MIN))
    {
        return 1;
    }
    *(S+indexF) = *(S+index1) & *(S+index2);
    return 0;
}
int XOR(int* S,int indexF, int index1, int index2)
{
    if (((*(S+index1) ^ *(S+index2)) > INT_MAX) || ((*(S+index1) ^ *(S+index2)) < INT_MIN))
    {
        return 1;
    }
    *(S+indexF) = *(S+index1) ^ *(S+index2);
    return 0;
}
int OR(int* S,int indexF, int index1, int index2)
{
    if (((*(S+index1) | *(S+index2)) > INT_MAX) || ((*(S+index1) | *(S+index2)) < INT_MIN))
    {
        return 1;
    }
    *(S+indexF) = *(S+index1) | *(S+index2);
    return 0;
}

int ADDI(int* S,int indexF, int index1, int number)
{
    if (((*(S+index1) + number) > INT_MAX) || ((*(S+index1) + number) < INT_MIN))
    {
        return 1;
    }
    *(S+indexF) = *(S+index1) + number;
    return 0;
}
int SUBI(int* S,int indexF, int index1, int number)
{
    if (((*(S+index1) - number) > INT_MAX) || ((*(S+index1) - number) < INT_MIN))
    {
        return 1;
    }
    *(S+indexF) = *(S+index1) - number;
    return 0;
}
int ANDI(int* S,int indexF, int index1, int number)
{
    if (((*(S+index1) & number) > INT_MAX) || ((*(S+index1) & number) < INT_MIN))
    {
        return 1;
    }
    *(S+indexF) = *(S+index1) & number;
    return 0;
}
int XORI(int* S,int indexF, int index1, int number)
{
    if (((*(S+index1) ^ number) > INT_MAX) || ((*(S+index1) ^ number) < INT_MIN))
    {
        return 1;
    }
    *(S+indexF) = *(S+index1) ^ number;
    return 0;
}
int ORI(int* S,int indexF, int index1, int number)
{
    if (((*(S+index1) | number) > INT_MAX) || ((*(S+index1) | number) < INT_MIN))
    {
        return 1;
    }
    *(S+indexF) = *(S+index1) | number;
    return 0;
}
void SWP(int* S,int index1, int index2)
{
    int temp = *(S+index1);
    *(S+index1) = *(S+index2);
    *(S+index2) = temp;
}
void DUMP_REGS(int* S)
{
    printf("Register : \n ");
    for (int i = 0; i < 32; i++)
    {
        printf(" | %d : %d | ",i, *(S+i));
    }
    
}
void DUMP_REGS_F(int* S)
{
    FILE *output;
    output = fopen("regs.txt","w");
    fprintf(output, "Register : \n ");
    for (int i = 0; i < 32; i++)
    {
        fprintf(output, " | %d : %d | ",i, *(S+i));
    }
    fclose(output);
}
void INPUT(int*S)
{
    printf("Please enter number in size of int to save in register 0 then press ENTER : ");
    scanf("%d",S);
}
void OUTPUT(int*S)
{
    printf("Register 0 is : %d \n",*(S));
}