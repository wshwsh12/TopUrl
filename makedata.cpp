#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iostream>
using namespace std;

double G = 1;
#define M 1000
#define N 10000
char s[10000];
int main(int argc,char** argv)
{
    FILE* fout = fopen("data.txt","w");
    if (argc == 2)
        sscanf(argv[1],"%lf",&G);
    srand(time(0));
    for (int k = 1;k <= M * G;k++)
    for (int i = 1;i <= N;i++)
        {
            for (int j = 0;j < 100;j++)
                s[j]=rand()%26+'a';
            fprintf(fout,"%s\n",s);
        }
    
    return 0;
}