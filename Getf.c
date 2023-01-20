#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 
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

int main()
{
      
    char buf[100][100];
    FILE *stream = fopen("in.txt", "r");
    readF(stream, buf);
    


    for (int i = 0; buf[i][0] != '\0'; i++)
    {
        char cmd[100];
        sscanf(buf[i], "%s", cmd);

        
        if (strcmp(cmd, "ADD") == 0 || strcmp(cmd, "SUB") == 0 || strcmp(cmd, "AND") == 0 || strcmp(cmd, "XOR") == 0 || strcmp(cmd, "OR") == 0)
        {
            int a,b,d;
            int check = sscanf(buf[i],"%s S%d, S%d, S%d",cmd,&a,&b,&d);
            if (check != 4)
            {
                printf("Erro use this cmd like this: %s S1, S2, S3\n",cmd);
            }
            else
            {
                printf("%s %d %d %d\n",cmd,a,b,d);
            }
        }
        else if (strcmp(cmd, "ADDI") == 0 || strcmp(cmd, "SUBI") == 0 || strcmp(cmd, "ANDI") == 0 || strcmp(cmd, "XORI") == 0 || strcmp(cmd, "ORI") == 0)
        {
            int a,b,d;
            int check = sscanf(buf[i],"%s S%d, S%d, %d",cmd,&a,&b,&d);
            if (check != 4)
            {
                printf("Erro use this cmd like this: %s S1, S2, S3\n",cmd);
            }
            else
            {
                printf("%s %d %d %d\n",cmd,a,b,d);
            }
        }
        else if (strcmp(cmd, "SWP") == 0 )
        {
            int a,b;
            int check = sscanf(buf[i],"%s S%d, S%d",cmd,&a,&b);
            if (check != 3)
            {
                printf("Erro use this cmd like this: %s S1, S2\n",cmd);
            }
            else
            {
                printf("%s %d %d\n",cmd,a,b);
            }
        }
        else if (strcmp(cmd, "MOV") == 0 )
        {
            int a,b;
            int check = sscanf(buf[i],"%s S%d, S%d",cmd,&a,&b);
            int check2 = sscanf(buf[i],"%s S%d, %d",cmd,&a,&b);
            if (check != 3 && check2 !=3)
            {
                
                printf("Erro use this cmd like this: %s S1, S2\n",cmd);
            }
            else if(check2 == 3)
            {
                printf("%s %d %d\n",cmd,a,b);
            }
            else
            {
                printf("%s %d S%d\n",cmd,a,b);
            }
            
        }
        else if (strcmp(cmd, "JMP") == 0 || strcmp(cmd, "OUTPUT") == 0 || strcmp(cmd, "INPUT") == 0 || strcmp(cmd, "DUMP_REGS") == 0 || strcmp(cmd, "DUMP_REGS_F") == 0)
        {
            sscanf(buf[i],"%s",cmd);
            printf("%s \n",cmd);
            
        }
        else
        {
            printf("%s comand is not define in this program ! \n",cmd);
        }
        

    }
    

    return 0;
}