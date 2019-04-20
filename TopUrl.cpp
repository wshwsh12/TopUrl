#include "TopUrl.h"


TopUrl::TopUrl(int n):N(n)
{
    ftemp = (FILE **)malloc(sizeof(FILE *) * N);
}

TopUrl::~TopUrl()
{
    free(ftemp);
}

//split data to block
void TopUrl::preprocess()
{
    fin = fopen("data.txt","r");
    for (int i = 0;i < N;i++)
    {
        string filename = std::to_string(i) + ".txt";
        ftemp[i] = fopen(filename.c_str(),"w");
    }
    while (fscanf(fin,"%s",url)!=EOF)
    {
        unsigned int m = SDBM_hash(url) % N;
        fprintf(ftemp[m],"%s\n",url);
    }
    fclose(fin);
    for (int i = 0;i < N;i++)
        fclose(ftemp[i]);
};

//count num for all block
void TopUrl::count_for_all_block()
{
    for (int i = 0;i < N;i++)
    {
        string filename = std::to_string(i) + ".txt";
        ftemp[i] = fopen(filename.c_str(),"r");
    }
    fcount = fopen("count.txt","w");

    for (int i = 0;i < N;i++)
    {
        hashmap.clear();
        while (fscanf(ftemp[i],"%s",url)!=EOF)
        {
            string ss = url;
            hashmap[ss]++;
        }

        while (priqueue.size()) priqueue.pop();

        for (it = hashmap.begin();it != hashmap.end();it++)
            {
                priqueue.push(make_pair(it->second,it->first));
                if (priqueue.size() > 100)
                    priqueue.pop();
            }
        
        while (priqueue.size())
            {
                pair<int,string> temp = priqueue.top();
                priqueue.pop();
                fprintf(fcount,"%d %s\n",temp.first,temp.second.c_str());
            }
    }
    for (int i = 0;i < N;i++)
        fclose(ftemp[i]);
    fclose(fcount);
};

//collect all result
void TopUrl::collect_all_result()
{
    fcount = fopen("count.txt","r");
    fout = fopen("answer.txt","w");
    while (priqueue.size()) priqueue.pop();
    while (fscanf(fcount,"%d %s",&countnum,url)!=EOF)
    {
        priqueue.push(std::make_pair(countnum,url));
        if (priqueue.size() > 100)
            priqueue.pop(); 
    }
    while (priqueue.size())
        {
            pair<int,string> temp = priqueue.top();
            priqueue.pop();
            fprintf(fout,"%d %s\n",temp.first,temp.second.c_str());
        }
    fclose(fout);
};

//clear temp file
void TopUrl::clear_temp_file()
{
    for (int i = 0;i < N;i++)
    {
        fclose(ftemp[i]);
        string filename = std::to_string(i) + ".txt";
        remove(filename.c_str());
    }
}