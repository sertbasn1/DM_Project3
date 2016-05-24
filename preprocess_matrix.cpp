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
vector<string>::const_iterator fit;



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
    string tmp;
    
   
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
    FILE *files = fopen ("outputs/files.txt", "w+" );
    
    unsigned int a;
    
    if ( ptr1 == NULL )
    {   printf("Error opening file to read\n");
        exit(1);
    }
    
    if ( files == NULL )
    {   printf("Error opening file to read\n");
        exit(1);
    }
    
    
    while( fgets ( line, sizeof(line), ptr1 ) != NULL )
        authorqueue.push_back(line);
    
   
    
        for ( it1= allrecords.begin(); it1!= allrecords.end(); ++it1){
            tmp=(*it1).author;
            
            for ( it2= authorqueue.begin(); it2!= authorqueue.end(); ++it2){
                if(tmp==*it2)
                {  for(fit=(*it1).files.begin(); fit!= (*it1).files.end(); ++fit)
                    fprintf(files,"%s",(char*)(*fit).c_str());
                }
            }
    
        }
    
    fclose(ptr1);
    fclose(files);

    return 0;
   
}
