/**************************************************************************//**
 * @file Doxygen-test.c
 * @brief شبیه ساز پردازنده - پروژه نهایی مبانی کامپیوتر
 * 
 * @version: V1.3.1
 * @date: 21. january. 2023
 * @author: Mh.Shabaniraad
 * @note
 * Before use app see manual of functions
 * @warning
 * Becarful in proccess system can crash
 *
 * \mainpage This is my final project in fundemental programming
 * in KNTU
 *
 ******************************************************************************/

/***********
 * Include Files
 * @brife includes
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 

#define INT_MAX	2147483647
#define INT_MIN	-2147483648

/********************************************//**
 *  ... Read input file and copy in buf array each line
 ***********************************************/

void read_f(FILE *stream, char buf[][100]);
int count_line(char buf[][100]);


int count1s(int N);
int add(int* S,int indexF, int index1, int index2);
int sub(int* S,int indexF, int index1, int index2);
int and(int* S,int indexF, int index1, int index2);
int xor(int* S,int indexF, int index1, int index2);
int or(int* S,int indexF, int index1, int index2);

int addi(int* S,int indexF, int index1, int number);
int subi(int* S,int indexF, int index1, int number);
int andi(int* S,int indexF, int index1, int number);
int xori(int* S,int indexF, int index1, int number);
int ori(int* S,int indexF, int index1, int number);

void swp(int* S,int index1, int index2);
void dump_regs(int* S, int* SR);
void dump_regs_f(int* S, int* SR);
void input(int*S);
void output(int*S);

void update_reg(int*SR , int var);

int main()
{
    int S[32];
    int SR[8];
    int stack[100];
    int last_stack = -1;
    char buf[100][100];
    char file_name[100];
    printf("plead enter your file name then press enter :");
    scanf("%s",file_name);
    FILE *stream = fopen(file_name, "r");
    read_f(stream, buf);
    
    int max_line = count_line(buf);
    if (max_line == 0)
    {
        printf("ERROR : File is emity ! \n");
        return 1;
    }
    
    for (int i = 0; buf[i][0] != '\0'; i++)
    {
        int a,b,d;
        char cmd[100];
        char temp[100];
        sscanf(buf[i], "%s", cmd);

        
        if (strcmp(cmd, "ADD") == 0 || strcmp(cmd, "SUB") == 0 || strcmp(cmd, "AND") == 0 || strcmp(cmd, "XOR") == 0 || strcmp(cmd, "OR") == 0)
        {
            
            int check = sscanf(buf[i],"%s S%d, S%d, S%d%s",cmd,&a,&b,&d,temp);
            if (check != 4)
            {
                printf("Line %d : Erro use this cmd like this: %s S1, S2, S3\n",i+1,cmd);
            }
            else if (a < 0 || b < 0 || d < 0 || a > 31 || b > 31 || d > 31)
            {
                printf("Line %d : Erro Register are/is out of range (must between 0-31)\n",i+1);
            }
            
            else
            {
                
                if (strcmp(cmd, "AND") == 0)
                {
                    and(S,a,b,d);
                    update_reg(SR,S[a]);
                }
                if (strcmp(cmd, "SUB") == 0)
                {
                    int overf = sub(S,a,b,d);
                    update_reg(SR,S[a]);
                    if (overf == 1)
                        SR[5] = 1;
                    else
                        SR[5] = 0;
                }
                if (strcmp(cmd, "ADD") == 0)
                {
                    int overf = add(S,a,b,d);
                    update_reg(SR,S[a]);
                    if (overf == 1)
                        SR[5] = 1;
                    else
                        SR[5] = 0;
                }
                if (strcmp(cmd, "XOR") == 0)
                {
                    xor(S,a,b,d);
                    update_reg(SR,S[a]);
                }
                if (strcmp(cmd, "OR") == 0)
                {
                    or(S,a,b,d);
                    update_reg(SR,S[a]);
                }
            }
        }
        else if (strcmp(cmd, "ADDI") == 0 || strcmp(cmd, "SUBI") == 0 || strcmp(cmd, "ANDI") == 0 || strcmp(cmd, "XORI") == 0 || strcmp(cmd, "ORI") == 0)
        {
            
            int check = sscanf(buf[i],"%s S%d, S%d, %d%s",cmd,&a,&b,&d,temp);
            if (check != 4)
            {
                printf("Line %d : Erro use this cmd like this: %s S1, S2, S3\n",i+1,cmd);
            }
            else if (a < 0 || b < 0 || a > 31 || b > 31 )
            {
                printf("Line %d : Erro Register are/is out of range (must between 0-31)\n",i+1);
            }
            else
            {
                if (strcmp(cmd, "ANDI") == 0)
                {
                    andi(S,a,b,d);
                    update_reg(SR,S[a]);
                }
                if (strcmp(cmd, "SUBI") == 0)
                {
                    int overf = subi(S,a,b,d);
                    update_reg(SR,S[a]);
                    if (overf == 1)
                        SR[5] = 1;
                    else
                        SR[5] = 0;
                }
                if (strcmp(cmd, "ADDI") == 0)
                {
                    int overf = addi(S,a,b,d);
                    update_reg(SR,S[a]);
                    if (overf == 1)
                        SR[5] = 1;
                    else
                        SR[5] = 0;
                }
                if (strcmp(cmd, "XORI") == 0)
                {
                    xori(S,a,b,d);
                    update_reg(SR,S[a]);
                }
                if (strcmp(cmd, "ORI") == 0)
                {
                    ori(S,a,b,d);
                    update_reg(SR,S[a]);
                }
            }
        }
        else if (strcmp(cmd, "SWP") == 0 )
        {
            
            int check = sscanf(buf[i],"%s S%d, S%d%s",cmd,&a,&b,temp);
            if (check != 3)
            {
                printf("Line %d : Erro use this cmd like this: %s S1, S2\n",i+1,cmd);
            }
            else if (a < 0 || b < 0 || a > 31 || b > 31)
            {
                printf("Line %d : Erro Register are/is out of range (must between 0-31)\n",i+1);
            }
            else
            {
                swp(S,a,b);
            }
        }
        else if (strcmp(cmd, "SKIE") == 0 )
        {
            
            int check = sscanf(buf[i],"%s S%d, S%d%s",cmd,&a,&b,temp);
            if (check != 3)
            {
                printf("Line %d : Erro use this cmd like this: %s S1, S2\n",i+1,cmd);
            }
            else if (a < 0 || b < 0 || a > 31 || b > 31)
            {
                printf("Line %d : Erro Register are/is out of range (must between 0-31)\n",i+1);
            }
            else
            {
                if (S[a] == S[b])
                {
                    i++;
                }
                
            }
        }
        else if (strcmp(cmd, "PUSH") == 0 )
        {
            
            int check = sscanf(buf[i],"%s S%d%s",cmd,&a,temp);
            if (check != 2)
            {
                printf("Line %d : Erro use this cmd like this: %s S1\n",i+1,cmd);
            }
            else if (a < 0 || a > 31 )
            {
                printf("Line %d : Erro Register are/is out of range (must between 0-31)\n",i+1);
            }
            else
            {
                
                if (last_stack == 99)
                {
                    printf("ERROR : Stack is FULL Cant PUSH it\n");
                }
                else
                {
                    last_stack++;
                    stack[last_stack] = S[a];
                }
                
                
                
            }
        }
        else if (strcmp(cmd, "POP") == 0 )
        {
            
            int check = sscanf(buf[i],"%s S%d%s",cmd,&a,temp);
            if (check != 2)
            {
                printf("Line %d : Erro use this cmd like this: %s S1\n",i+1,cmd);
            }
            else if (a < 0 || a > 31 )
            {
                printf("Line %d : Erro Register are/is out of range (must between 0-31)\n",i+1);
            }
            else
            {
                if (last_stack < 0)
                {
                    printf("ERROR STack is empity\n");
                }
                else
                {
                    S[a] = stack[last_stack];
                    last_stack--;
                
                }
                
                
                
            }
        }
        else if (strcmp(cmd, "MOV") == 0 )
        {
            
            int check = sscanf(buf[i],"%s S%d, S%d%s",cmd,&a,&b,temp);
            int check2 = sscanf(buf[i],"%s S%d, %d%s",cmd,&a,&b,temp);
            if (check != 3 && check2 !=3)
            {
                
                printf("Line %d : Erro use this cmd like this: %s S1, S2 or S1, 2\n",i+i,cmd);
            }
            else if (a < 0 || a > 31 || ((check == 3) && b < 0 || b > 31))
            {
                printf("Line %d : Erro Register are/is out of range (must between 0-31)\n",i+1);
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
            int check = sscanf(buf[i],"%s %d%s",cmd,&a,temp);
            if (check != 2 )
            {
                
                printf("Line %d : Erro use this cmd like this: %s 2\n",i+1,cmd);
            }
            else if (a < 0 || a > max_line)
            {
                printf("Line %d : JMP Out of range of file !\n",i+1);
            }
            else
            {
                i = a - 2;
            }
            
        }
        else if (strcmp(cmd, "OUTPUT") == 0 || strcmp(cmd, "INPUT") == 0 || strcmp(cmd, "DUMP_REGS") == 0 || strcmp(cmd, "DUMP_REGS_F") == 0)
        {
            int check = sscanf(buf[i],"%s%s",cmd,temp);
            if (check != 1)
            {
                printf("Line %d : Erro use this cmd like this: %s\n",i+1,cmd);
            }
            else {
                if (strcmp(cmd, "OUTPUT") == 0)
                {
                    output(S);
                }
                else if (strcmp(cmd, "INPUT") == 0)
                {
                    input(S);
                }
                else if (strcmp(cmd, "DUMP_REGS") == 0)
                {
                    dump_regs(S,SR);
                }
                else if (strcmp(cmd, "DUMP_REGS_F") == 0)
                {
                    dump_regs_f(S,SR);
                }
            }
                        
        }
        else if (strcmp(cmd, "EXIT") == 0 )
        {
            return 0;
        }
        else
        {
            printf("Line %d : %s comand is not define in this program ! \n",i+1,cmd);
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
int add(int* S,int indexF, int index1, int index2)
{
    S[indexF] = S[index1] + S[index2];
    if ((S[index1] + S[index2] > INT_MAX) || (S[index1] + S[index2] < INT_MIN))
    {
        return 1;
    }
    return 0;
}
int sub(int* S,int indexF, int index1, int index2)
{
    S[indexF] = S[index1] - S[index2];
    if ((S[index1] - S[index2] > INT_MAX) || (S[index1] - S[index2] < INT_MIN))
    {
        return 1;
    }
    return 0;
}
int and(int* S,int indexF, int index1, int index2)
{
    
    S[indexF] = S[index1] & S[index2];
    return 0;
}
int xor(int* S,int indexF, int index1, int index2)
{
    
    S[indexF] = S[index1] ^ S[index2];
    return 0;
}
int or(int* S,int indexF, int index1, int index2)
{
    
    S[indexF] = S[index1] | S[index2];
    return 0;
}

int addi(int* S,int indexF, int index1, int number)
{
    S[indexF] = S[index1] + number;
    if ((S[index1] + number > INT_MAX) || (S[index1] + number < INT_MIN))
    {
        return 1;
    }
    return 0;
}
int subi(int* S,int indexF, int index1, int number)
{
    S[indexF] = S[index1] - number;
    if ((S[index1] - number > INT_MAX) || (S[index1] - number < INT_MIN))
    {
        return 1;
    }
    return 0;
}
int andi(int* S,int indexF, int index1, int number)
{
    
    S[indexF] = S[index1] & number;
    return 0;
}
int xori(int* S,int indexF, int index1, int number)
{
    
    S[indexF] = S[index1] ^ number;
    return 0;
}
int ori(int* S,int indexF, int index1, int number)
{
    
    S[indexF] = S[index1] | number;
    return 0;
}
void swp(int* S,int index1, int index2)
{
    int temp = S[index1];
    S[index1] = S[index2];
    S[index2] = temp;
}
void dump_regs(int* S, int* SR)
{
    printf("Register : \n ");
    for (int i = 0; i < 32; i++)
    {
        printf("%d : %d\n",i, S[i]);
    }
    printf("\nRegister  Status: \n");
    for (int i = 0; i < 8; i++)
    {
        printf("%d : %d | ",i, SR[i]);
    }
    printf("\n");
    
}
void dump_regs_f(int* S, int* SR)
{
    FILE *output;
    output = fopen("regs.txt","w");
    fprintf(output, "Register : \n ");
    for (int i = 0; i < 32; i++)
    {
        fprintf(output, "%d : %d\n",i, S[i]);
    }
    fprintf(output, "\nRegister Status : \n");
    for (int i = 0; i < 32; i++)
    {
        fprintf(output, "%d : %d | ",i, SR[i]);
    }
    fprintf(output,"\n");
    fclose(output);
}
void input(int*S)
{
    printf("Please enter number in size of int to save in register 0 then press ENTER : ");
    scanf("%d",S);
}
void output(int*S)
{
    printf("Register 0 is : %d \n",S[0]);
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

void read_f(FILE *stream, char buf[][100])
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
            if(j == 0)
            {
                while ((c = fgetc(stream)) != EOF && c != '\n')
                {
                    
                }
                j =0;
            }
            else
            {
                while ((c = fgetc(stream)) != EOF && c != '\n')
                {
                    
                }
                j =0;
                i++;
            }
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
int count_line(char buf[][100])
{
    for (int i = 0; i < 100; i++)
    {
        if (buf[i][0] == '\0')
        {
            return i;
        }
        
    }
    return 0;
    
}