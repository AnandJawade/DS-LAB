#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

int main()
{
    FILE *f1,*f2,*f3,*f4,*f5;
    int value1,value2,value3,value4,value5;
    srand(time(0));
    f1 = fopen("file1.txt","w");
    f2 = fopen("file2.txt","w");
    f3 = fopen("file3.txt","w");
    f4 = fopen("file4.txt","w");
    f5 = fopen("file5.txt","w");

    int t = 10000;
    while(t--)
    {
        value1 = rand()%1000;
        value2 = rand()%2000;
        value3 = rand()%3000;
        value4 = rand()%4000;
        value5 = rand()%5000;
        fprintf(f1,"%d\n",value1);
        fprintf(f2,"%d\n",value2);
        fprintf(f3,"%d\n",value3);
        fprintf(f4,"%d\n",value4);
        fprintf(f5,"%d\n",value5);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f4);
    return 0;
}
