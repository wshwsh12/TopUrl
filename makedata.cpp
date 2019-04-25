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
char save_string[200][10100];

int main(int argc,char** argv)
{
    FILE* fout = fopen("data.txt","w");
    srand(time(0));
    if (argc == 2)
        sscanf(argv[1],"%lf",&G);
    
    //ALL RANDOM
    
    for (int k = 1;k <= M * G;k++)
    for (int i = 1;i <= N;i++)
        {
            for (int j = 0;j < 100;j++)
                s[j]=rand()%26+'a';
            fprintf(fout,"%s\n",s);
        }
    

    // Test 1：
    /*
    int len = rand() % 100 + 50;    
    for (int i = 0;i < len;i++)
        save_string[0][i] = rand() % 26 + 'a';

    for (int k = 1;k <= M * G;k++)
    for (int i = 1;i <= N;i++)
    {
        int p = rand()%100;
        if (p < 70)
            fprintf(fout,"%s\n",save_string[0]);
        else
        {
            len = rand() % 100 + 50;
            for (int j = 0;j < len;j++)
                s[j]=rand()%26+'a';
            s[len] = '\0';
            fprintf(fout,"%s\n",s);
        }
    }*/

    // Test 2:
    /*for (int i = 1;i <= 111;i++)
    {
        int len = rand() % 100 + 50;  
        for (int j = 0;j < len;j++)
            save_string[i][j] = rand() % 26 + 'a';
    }

    int str_num[1010],now = 0;
    memset(str_num,0,sizeof str_num);
    
    for (int i = 1;i <= 1;i++)
    for (int j = 1;j <= 300;j++)
        str_num[++now] = i;
    
    for (int i = 2;i <= 11;i++)
    for (int j = 1;j <= 50;j++)
        str_num[++now] = i;

    for (int i = 12;i <= 111;i++)
    for (int j = 1;j <= 1;j++)
        str_num[++now] = i;

    for (int k = 1;k <= M * G;k++)
    for (int i = 1;i <= N;i++)
    {
        int p = rand()%1000;
        if (str_num[p])
            fprintf(fout,"%s\n",save_string[str_num[p]]);
        else
        {
            int len = rand() % 100 + 50;
            for (int j = 0;j < len;j++)
                s[j]=rand()%26+'a';
            s[len] = '\0';
            fprintf(fout,"%s\n",s);
        }
    }
*/
    return 0;
}