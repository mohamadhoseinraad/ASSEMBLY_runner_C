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
    
    char cmd[100];
    
    sscanf(buf[0], "%s", cmd);
    
    
    

    int a,b,d;
    int check = sscanf(buf[0],"%s S%d, S%d, S%d",cmd,&a,&b,&d);
    if (check != 4)
    {
        printf("Erro\n");
    }
    else
    {
        printf("%s %d %d %d\n",cmd,a,b,d);
    }
    
    
    return 0;
}