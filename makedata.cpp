#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iostream>
using namespace std;

#define G 1
#define M 100
#define N 10000

char alpha[36];
char s[200];
int main()
{
    FILE* fout = fopen("data_100M.txt","w");

    srand(time(0));
    for (int t = 1;t <= G;t++,puts(""))
    for (int k = 1;k <= M;k++)
    for (int i = 1;i <= N;i++)
        {
            for (int j = 0;j < 100;j++)
                s[j]=rand()%26+'a';
            fprintf(fout,"%s\n",s);
        }
    
    cout << clock() << endl;
    system("pause");
    return 0;
}