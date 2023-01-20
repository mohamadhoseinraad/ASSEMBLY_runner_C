#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 
int main()
{
    char buf[100][100];
    for (int l = 0; l < 100; l++)
    {
        for (int k = 0; k < 100; k++)
        {
            buf[l][k] = '\0';
        }
    }
    
    
    int a,b;
    char c;
    FILE *stream = fopen("in.txt", "r");
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
                buf[i][j] = c;
            
                i++;
                
                j=0;
        }
        else
        {
            buf[i][j] = c;
            j++;
        }
    }
    
    
    return 0;
}