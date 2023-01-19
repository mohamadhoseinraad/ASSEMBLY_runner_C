#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 
int main()
{
    char buf[1000];
    char buf2[1000];
    int a,b,c;
    FILE *stream = fopen("in.txt", "r");
    while (fscanf(stream , "%s ", buf) != EOF)
    {
        int j = 0;
        
        while (buf[j]) {
        
        buf[j] = toupper(buf[j]);
        j++;
        }
        
        
        
        if (strcmp(buf, "ADD") == 0 || strcmp(buf, "SUB") == 0 || strcmp(buf, "AND") == 0 || strcmp(buf, "XOR") == 0 || strcmp(buf, "OR") == 0)
        {
            int xx = fscanf(stream , "S%d, S%d, S%d", &a,&b,&c);
            while ((fgetc(stream)) != '\n' || fgetc(stream) != EOF)
            {
                
            }
            if (xx == 3)
            {
                puts(buf);
                printf("%d   %d   %d\n",a,b,c);
            }
            else
            {
                printf("syntax error | use this Cmd  like this: %s S2, S1, S0\n",buf);
            }
            
        }
        else if (strcmp(buf, "ADDI") == 0 || strcmp(buf, "SUBI") == 0 || strcmp(buf, "ANDI") == 0 || strcmp(buf, "XORI") == 0 || strcmp(buf, "ORI") == 0)
        {
            int xx = fscanf(stream , "S%d, S%d, %d", &a,&b,&c);
            while ((fgetc(stream)) != '\n' || fgetc(stream) != EOF)
            {
                
            }
            if (xx == 3)
            {
                puts(buf);
                printf("%d   %d   %d\n",a,b,c);
            }
            else
            {
                printf("syntax error | use this Cmd  like this: %s S2, S1, 0\n",buf);
            }
            
        }
        else if (strcmp(buf, "SWP") == 0 )
        {
            int xx = fscanf(stream , "S%d, S%d", &a,&b);
            while ((fgetc(stream)) != '\n' || fgetc(stream) != EOF)
            {
                
            }
            if (xx == 2)
            {
                puts(buf);
                printf("%d   %d \n",a,b);
            }
            else
            {
                printf("syntax error | use this Cmd  like this: %s S2, S1\n",buf);
            }
            
        }
        else if (strcmp(buf, "MOV") == 0 )
        {
            char movcmd[5];
            int xx = fscanf(stream , "S%d, %d", &a,&b);
            while ((fgetc(stream)) != '\n' || fgetc(stream) != EOF)
            {
                
            }
            if (xx == 2)
            {
                puts(buf);
                printf("%d   %d \n",a,b);
            }
            else
            {
                printf("syntax error | use this Cmd  like this: %s S2, S1\n",buf);
            }
            
            
        }
        else if (strcmp(buf, "OUTPUT") == 0 || strcmp(buf, "INPUT") == 0 || strcmp(buf, "DUMP_REGS") == 0 || strcmp(buf, "DUMP_REGS_F") == 0)
        {
            puts(buf);
        }
        else if (strncmp(buf,"//",2) == 0)
        {
            while ((fgetc(stream)) != '\n' || fgetc(stream) != EOF)
            {
                
            }
            
            printf("this is comnt\n");
        }
        else
        {
            while ((fgetc(stream)) != '\n' || fgetc(stream) != EOF)
            {}
                
            printf("not define\n");
        }
       
        
    }
    
    
    return 0;
}