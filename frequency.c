#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// computes developers' commit frequencies


struct developer{
    int commit;
    char name[50];
    int initialcommit;
    int lastcommit;
    float freq;
};


int convert(char *line){
    int daycount=0;
    char *token;
    strtok(line,":");
    
    token = strtok(NULL, " ");
    daycount+=atoi(token);
    //printf("%s\n",token);
    
    token = strtok(NULL, " ");
    int md;
    
    if(!strcmp(token,"Jan"))   md=0;
    else if(!strcmp(token,"Feb")) md=31;
    else if(!strcmp(token,"Mar")) md=31+28;
    else if(!strcmp(token,"Apr")) md=31+28+31;
    else if(!strcmp(token,"May")) md=31+28+31+30;
    else if(!strcmp(token,"Jun")) md=31+28+31+30+31;
    else if(!strcmp(token,"Jul")) md=31+28+31+30+31+30;
    else if(!strcmp(token,"Aug")) md=31+28+31+30+31+30+31;
    else if(!strcmp(token,"Sept"))md=31+28+31+30+31+30+31+31;
    else if(!strcmp(token,"Oct")) md=31+28+31+30+31+30+31+31+30;
    else if(!strcmp(token,"Nov")) md=31+28+31+30+31+30+31+31+30+31;
    else if(!strcmp(token,"Dec")) md=31+28+31+30+31+30+31+31+30+31+30;
    
    daycount+=md;
    return daycount;
    
}


int main()
{
    FILE *ptr1 = fopen ("outputs/commitcountandauthors1.log", "r" );
    
    if ( ptr1 == NULL )
    {
        printf("Error opening file to read\n");
        exit(1);
    }
    
    char line [ 128 ];
    char *token;
    int counter=0;


    
    while ( fgets ( line, sizeof(line), ptr1 ) != NULL )
        counter++;
    
    fseek(ptr1, SEEK_SET,0);
    
    struct developer mydevelopers[counter];
    char authors[counter][100];
    int commits;
    char arr[counter][10];
    int i=0;
    int m;
    int tmp;
    struct developer tmpdev;
    
    while( fgets ( line, sizeof(line), ptr1 ) != NULL ){
        for(m=0;m<6;m++)
            arr[i][m] = line[m];
        mydevelopers[i].commit=atoi(arr[i]);
        
        m=7;
        while (line[m]!='\n') {
            authors[i][m-7] = line[m];
            m++;
        }
        authors[i][m-7]='\0';
        strcpy(mydevelopers[i].name,authors[i]);
        i++;
    }
    

    fclose (ptr1);


    
    FILE *ptr2 = fopen ("outputs/commitdateandauthor.log", "r" );
    if ( ptr2 == NULL )
    {
        printf("Error opening file to read\n");
        exit(1);
    }
  
    i=0;
    while(fgets ( line, sizeof(line), ptr2 )!=NULL){
        if(line[0]!=' ')//isimse
            {fgets(line, sizeof(line), ptr2 );
                mydevelopers[i].initialcommit=convert(line);
                i++;
             }
    }
    
   
    fseek(ptr2,0,SEEK_SET);
    
    FILE *ptrt = fopen ("outputs/lastcommitdates.txt", "w+" );
    if ( ptrt == NULL )
    {
        printf("Error opening file to read\n");
        exit(1);
    }
    
    char mline[128];
    i=-1;
    while(fgets(line, sizeof(line), ptr2 )!=NULL){
        if(line[0]!=' ')//isimse
        {   fprintf(ptrt,"%s",mline);
            fgets(line, sizeof(line), ptr2 );
            
            i++;
        }
        
        strcpy(mline,line);
       
    }
    fprintf(ptrt,"%s",mline);

    
    fclose(ptr2);
    fclose(ptrt);

    
    
    
    ptr2 = fopen ("outputs/lastcommitdates.txt", "r" );
    if ( ptr2 == NULL )
    {
        printf("Error opening file to read\n");
        exit(1);
    }
    
    i=0;
    while(fgets ( line, sizeof(line), ptr2 )!=NULL){
        mydevelopers[i].lastcommit=convert(line);
        i++;
       
    }

    fclose(ptr2);
    
    
    FILE * son = fopen ("outputs/commitfrequencyofdevelopers.txt", "w+" );
    if ( son == NULL )
    {
        printf("Error opening file to read\n");
        exit(1);
    }

    
    int range=0;
    fprintf(son,"%d\n",counter);
    for(i=0;i<counter;i++){
        range=abs(mydevelopers[i].initialcommit-mydevelopers[i].lastcommit);
        if(range==0)
            mydevelopers[i].freq=(float)1/(float)mydevelopers[i].commit;
        else
            mydevelopers[i].freq=(float)range/(float)mydevelopers[i].commit;

         fprintf(son,"%.2f:%s\n",mydevelopers[i].freq,mydevelopers[i].name);
       
//       printf("%s\t%d\t%d-%d\t%.2f\n",mydevelopers[i].name,mydevelopers[i].commit,mydevelopers[i].initialcommit,mydevelopers[i].lastcommit, mydevelopers[i].freq);
    }
    
    fclose(son);
    printf("Result is saved into commitfrequencyofdevelopers.txt under outputs directory\n\n");

    return 0;
   
}
