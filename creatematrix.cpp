#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>


using namespace std;

struct record{
    vector<string> files;
    string author;
};

vector <string> authorqueue;
vector <string> filequeue;

vector<record>::const_iterator it1;
vector<string>::const_iterator it2;

int findcolnum(string name){
    int x=0;
    int flag=0;
    for (unsigned i=0; i<authorqueue.size(); i++){
        if( authorqueue.at(i)==name)
             {flag=1;break;}
    x++;
    }
    
    if(flag==1)
    return x;
    else
    return -1;
}

int findrownum(string name){
    int x=0;
    int flag=0;
    for (unsigned i=0; i<filequeue.size(); i++){
        if( filequeue.at(i)==name)
        {flag=1;break;}
    x++;
    }
   
    if(flag==1)
    return x;
    else
    return -1;
}




int main( int argc, char *argv[])
{
    FILE *ptr = fopen (argv[1], "r" );
    
    if ( ptr == NULL )
    {   printf("Error opening file to read\n");
        exit(1);
    }
    
    int m,n,i,j;
    char line [128];
    vector<record> allrecords;
    struct record tmprecord;

   
    while( fgets ( line, sizeof(line), ptr ) != NULL ){
        if(line[0]=='*'&& line[1]!='*'){
            fgets ( line, sizeof(line), ptr );
            tmprecord.author=" ";
            tmprecord.files.erase (tmprecord.files.begin(),tmprecord.files.end());
            tmprecord.author=line;
            
            
            //** görene kadar dosya
            fgets ( line, sizeof(line), ptr );
            while(line[0]!='*'&& line[1]!='*'){
                tmprecord.files.push_back(line);
            if(line[0]==' ')    fgets ( line, sizeof(line), ptr );
            fgets ( line, sizeof(line), ptr );
            }
        allrecords.push_back(tmprecord);
        }
    }

    
    fclose(ptr);
    
    FILE *ptr1 = fopen ("outputs/topdevelopernames.txt", "r" );
   
    
    if ( ptr1 == NULL )
    {   printf("Error opening file to read\n");
        exit(1);
    }
    
    while( fgets ( line, sizeof(line), ptr1 ) != NULL )
        authorqueue.push_back(line);
    
   
    
    FILE * ptr2 = fopen ("outputs/uniqfiles.txt", "r" );
    

    if ( ptr2 == NULL )
    {   printf("Error opening file to read\n");
        exit(1);
    }
    
    while( fgets ( line, sizeof(line), ptr2 ) != NULL )
        filequeue.push_back(line);
    
    fclose(ptr1);
    fclose(ptr2);
    
    /////////////////
    m=filequeue.size();
    n=authorqueue.size();
    int matrix[m][n];
    
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            matrix[i][j]=0;
        }
    }
    
    int col;
    int row;
    string tmp;
    
        for ( it1= allrecords.begin(); it1!= allrecords.end(); ++it1){
            //cout<<(*it1).author<<endl;
            tmp=(*it1).author;
            col=findcolnum(tmp);
            for ( it2= (*it1).files.begin(); it2 != (*it1).files.end(); ++it2){
                row=findrownum(*(it2));
                matrix[row][col]=1;
            }
    
        }
    
//   
//    for(i=0;i<m;i++){
//        for(j=0;j<n;j++){
//            cout<<matrix[i][j];
//        }
//        cout<<endl;
//    }
    
    
//    printf("%d",findcolnum("Alan\n"));
//    printf("\n%d",findrownum(".gitignore\n"));
//    printf("\n%d",findrownum("COPYING\n"));
    
//    
    FILE *pmtrx = fopen ("outputs/matrix.txt", "w+" );
    
    
    if ( pmtrx == NULL )
    {   printf("Error opening file to read\n");
        exit(1);
    }
    
       fprintf(pmtrx,"%d\n",m);
       fprintf(pmtrx,"%d\n",n);
    
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            fprintf(pmtrx,"%d",matrix[i][j]);
        }
        fprintf(pmtrx,"%s","\n");
    }
    
    printf("Result is saved into matrix.txt under outputs directory\n\n");


    return 0;
   
}
