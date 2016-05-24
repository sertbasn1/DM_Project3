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
          
    char authors[counter][100];
    int commits[counter];
    char arr[counter][10];
    int i=0;
    int m;
    int tmp;
    
    while( fgets ( line, sizeof(line), ptr ) != NULL ){
        
        for(m=0;m<6;m++)
              arr[i][m] = line[m];
        
        commits[i]=atoi(arr[i]);
        
        m=7;
        while (line[m]!='\n') {
            authors[i][m-7] = line[m];
            m++;
        }
         authors[i][m-7]='\0';
        i++;
    }
    
    fclose (ptr);
    
//    
//    for(i=0;i<counter;i++)
//        printf("%s\n",authors[i]);
//    
//    for(i=0;i<counter;i++)
//        printf("%d\n",commits[i]);
    
    
    
    int sum=0;
    for(i=0;i<counter;i++)
        sum=sum+commits[i];
    
    int x=0;
    int topcount=sum*0.8;
    int tmpsum=0;
    printf("Note: Top developer num of commits should be more than %d out of %d commits\n",topcount,sum);
    char  filename1[100];
    strcpy(filename1,"outputs/topdevelopers.txt");
    
    
    FILE *f1 = fopen(filename1, "w");
    if (f1 == NULL)
    {
        printf("Error opening file to write\n");
        exit(1);
    }
    
    char  filename2[100];
    strcpy(filename2,"outputs/topdevelopernames.txt");
    FILE *f2 = fopen(filename2, "w");
    if (f2 == NULL)
    {
        printf("Error opening file to write\n");
        exit(1);
    }
    
    
 
    i=0;
    while(tmpsum<topcount){
        tmpsum=tmpsum+commits[i];
       // printf("%d commits by %s\n",commits[i],authors[i]);
        i++;
    }
    
    if(i==0)
        printf("There is no authors who satisfies the condition\n");
    

    fprintf(f1,"%d\n",i);
    printf("There are %d top developer\n",i);
    
    tmpsum=0;
    i=0;
    while(tmpsum<topcount){
        tmpsum=tmpsum+commits[i];
        fprintf(f1,"%d:%s\n",commits[i],authors[i]);
        fprintf(f2,"%s\n",authors[i]);
        i++;
    }
  
   
    
    printf("Top developers are found and written into topdevelopernames.txt under outputs directory\n\n");

    fclose(f1);
    return 0;
   
}
