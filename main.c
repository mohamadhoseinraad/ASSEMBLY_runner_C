#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 

#define INT_MAX	2147483647
#define INT_MIN	-2147483648

void readF(FILE *stream, char buf[][100]);


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
void DUMP_REGS(int* S, int* SR);
void DUMP_REGS_F(int* S, int* SR);
void INPUT(int*S);
void OUTPUT(int*S);

void update_reg(int*SR , int var);

int main()
{
    int S[32];
    int SR[8];
    char buf[100][100];
    FILE *stream = fopen("in.txt", "r");
    readF(stream, buf);
    

    for (int i = 0; buf[i][0] != '\0'; i++)
    {
        int a,b,d;
        char cmd[100];
        sscanf(buf[i], "%s", cmd);

        
        if (strcmp(cmd, "ADD") == 0 || strcmp(cmd, "SUB") == 0 || strcmp(cmd, "AND") == 0 || strcmp(cmd, "XOR") == 0 || strcmp(cmd, "OR") == 0)
        {
            
            int check = sscanf(buf[i],"%s S%d, S%d, S%d",cmd,&a,&b,&d);
            if (check != 4)
            {
                printf("Erro use this cmd like this: %s S1, S2, S3\n",cmd);
            }
            else
            {
                if (strcmp(cmd, "AND") == 0)
                {
                    AND(S,a,b,d);
                    update_reg(SR,S[a]);
                }
                if (strcmp(cmd, "SUB") == 0)
                {
                    int overf = SUB(S,a,b,d);
                    update_reg(SR,S[a]);
                    if (overf == 1)
                        SR[5] = 1;
                    else
                        SR[5] = 0;
                }
                if (strcmp(cmd, "ADD") == 0)
                {
                    int overf = ADD(S,a,b,d);
                    update_reg(SR,S[a]);
                    if (overf == 1)
                        SR[5] = 1;
                    else
                        SR[5] = 0;
                }
                if (strcmp(cmd, "XOR") == 0)
                {
                    XOR(S,a,b,d);
                    update_reg(SR,S[a]);
                }
                if (strcmp(cmd, "OR") == 0)
                {
                    OR(S,a,b,d);
                    update_reg(SR,S[a]);
                }
            }
        }
        else if (strcmp(cmd, "ADDI") == 0 || strcmp(cmd, "SUBI") == 0 || strcmp(cmd, "ANDI") == 0 || strcmp(cmd, "XORI") == 0 || strcmp(cmd, "ORI") == 0)
        {
            
            int check = sscanf(buf[i],"%s S%d, S%d, %d",cmd,&a,&b,&d);
            if (check != 4)
            {
                printf("Erro use this cmd like this: %s S1, S2, S3\n",cmd);
            }
            else
            {
                if (strcmp(cmd, "ANDI") == 0)
                {
                    ANDI(S,a,b,d);
                    update_reg(SR,S[a]);
                }
                if (strcmp(cmd, "SUBI") == 0)
                {
                    int overf = SUBI(S,a,b,d);
                    update_reg(SR,S[a]);
                    if (overf == 1)
                        SR[5] = 1;
                    else
                        SR[5] = 0;
                }
                if (strcmp(cmd, "ADDI") == 0)
                {
                    int overf = ADDI(S,a,b,d);
                    update_reg(SR,S[a]);
                    if (overf == 1)
                        SR[5] = 1;
                    else
                        SR[5] = 0;
                }
                if (strcmp(cmd, "XORI") == 0)
                {
                    XORI(S,a,b,d);
                    update_reg(SR,S[a]);
                }
                if (strcmp(cmd, "ORI") == 0)
                {
                    ORI(S,a,b,d);
                    update_reg(SR,S[a]);
                }
            }
        }
        else if (strcmp(cmd, "SWP") == 0 )
        {
            
            int check = sscanf(buf[i],"%s S%d, S%d",cmd,&a,&b);
            if (check != 3)
            {
                printf("Erro use this cmd like this: %s S1, S2\n",cmd);
            }
            else
            {
                SWP(S,a,b);
            }
        }
        else if (strcmp(cmd, "MOV") == 0 )
        {
            
            int check = sscanf(buf[i],"%s S%d, S%d",cmd,&a,&b);
            int check2 = sscanf(buf[i],"%s S%d, %d",cmd,&a,&b);
            if (check != 3 && check2 !=3)
            {
                
                printf("Erro use this cmd like this: %s S1, S2\n",cmd);
            }
            else if(check2 == 3)
            {
                S[a] = b;
            }
            else
            {
                S[a] = S[b];
            }
            
        }
        else if (strcmp(cmd, "JMP") == 0 )
        {
            int check = sscanf(buf[i],"%s %d",cmd,&a);
            if (check != 2 )
            {
                
                printf("Erro use this cmd like this: %s 2\n",cmd);
            }
            else
            {
                i = a - 2;
            }
            
        }
        else if (strcmp(cmd, "OUTPUT") == 0 || strcmp(cmd, "INPUT") == 0 || strcmp(cmd, "DUMP_REGS") == 0 || strcmp(cmd, "DUMP_REGS_F") == 0)
        {
            sscanf(buf[i],"%s",cmd);
            if (strcmp(cmd, "OUTPUT") == 0)
            {
                OUTPUT(S);
            }
            else if (strcmp(cmd, "INPUT") == 0)
            {
                INPUT(S);
            }
            else if (strcmp(cmd, "DUMP_REGS") == 0)
            {
                DUMP_REGS(S,SR);
            }
            else if (strcmp(cmd, "DUMP_REGS_F") == 0)
            {
                DUMP_REGS_F(S,SR);
            }
                        
        }
        else if (strcmp(cmd, "EXIT") == 0 )
        {
            return 0;
        }
        else
        {
            printf("%s comand is not define in this program ! \n",cmd);
        }
        

    }

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
void DUMP_REGS(int* S, int* SR)
{
    printf("Register : \n ");
    for (int i = 0; i < 32; i++)
    {
        printf(" | %d : %d | ",i, *(S+i));
    }
    printf("\nRegister  Status: \n ");
    for (int i = 0; i < 8; i++)
    {
        printf(" | %d : %d | ",i, *(SR+i));
    }
    
}
void DUMP_REGS_F(int* S, int* SR)
{
    FILE *output;
    output = fopen("regs.txt","w");
    fprintf(output, "Register : \n ");
    for (int i = 0; i < 32; i++)
    {
        fprintf(output, " | %d : %d | ",i, *(S+i));
    }
    fprintf(output, "\nRegister Status : \n ");
    for (int i = 0; i < 32; i++)
    {
        fprintf(output, " | %d : %d | ",i, *(SR+i));
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

void readF(FILE *stream, char buf[][100])
{
    for (int l = 0; l < 100; l++)
    {
        for (int k = 0; k < 100; k++)
        {
            buf[l][k] = '\0';
        }
    }
    char c;
    int i =0,j=0;
    while ((c = fgetc(stream)) != EOF)
    {
        if (c == '/' && (c = fgetc(stream)) == '/')
        {
            while ((c = fgetc(stream)) != EOF && c != '\n')
            {
                
            }
            j =0;
            
        }
        
        else if (c == '\n')
        {
            if(j!=0)
            {
                buf[i][j] = c;
                i++;
                j=0;
            }
            else
            {
                j=0;
            }
            
            
        }
        else
        {
            buf[i][j] = toupper(c);
            j++;
        }
    }
}

