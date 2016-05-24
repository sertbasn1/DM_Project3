#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main( int argc, char *argv[])
{
    FILE *ptr = fopen ( argv[1], "r" );
    
    if ( ptr == NULL )
    {
        printf("Error opening file to read\n");
        exit(1);
    }
    
    char line [ 128 ];
    char *token;
    int counter=0;
    
    while ( fgets ( line, sizeof(line), ptr ) != NULL )
        counter++;
    
    fseek(ptr, SEEK_SET,0);
          
    char authors[counter][50];
    int commits[counter];
    int i=0;
    
    while( fgets ( line, sizeof(line), ptr ) != NULL ){
        token = strtok(line,"(");
        strcpy(authors[i],token);
       // printf("%s",token);
        token = strtok(NULL, ")");
        commits[i]=atoi(token);
        i++;
    }
    
    fclose (ptr);
    int sum=0;
    for(i=0;i<counter;i++)
        sum=sum+commits[i];
    
    
//    for(i=0;i<counter;i++){
//        printf("%30s\t%5d/%d\t%10f\n",authors[i],commits[i],sum,(float)(100*commits[i])/sum);
//    }
    
    //write to file
    
    char  filename1[100];
    char  filename2[100];
    int len=strlen(argv[1]);
    strncat(filename1,argv[1],len-4);
    strcat(filename1,"_c1.txt");
    strncat(filename2,argv[1],len-4);
    strcat(filename2,"_c2.txt");
    
    FILE *f1 = fopen(filename1, "w");
    if (f1 == NULL)
    {
        printf("Error opening file to write\n");
        exit(1);
    }
    
    
    for(i=0;i<counter;i++){
        fprintf(f1,"%f:%s\n",(float)(100*commits[i])/sum,authors[i]);
    }
    
    
    
    FILE *f2 = fopen(filename2, "w");
    if (f2 == NULL)
    {
        printf("Error opening file to write\n");
        exit(1);
    }
    fprintf(f2,"%d\n",counter);
    
    for(i=0;i<counter;i++){
        fprintf(f2,"%d:%s\n",commits[i],authors[i]);
    }
    
    printf("Result is saved into %s and %s\n\n",filename1, filename2);
    
    
    fclose(f1);
    fclose(f2);
    return 0;
   
}
