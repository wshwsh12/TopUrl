#include "TopUrl.h"


TopUrl::TopUrl()
{
    ftemp_block = (FILE **)malloc(sizeof(FILE *) * N);
    url   = (char*)malloc(sizeof (char) * 100000);
}

TopUrl::~TopUrl()
{
    free(ftemp_block);
    free(url);
}

//split data to block
void TopUrl::preprocess()
{
    if ((fin = fopen("data.txt","r"))==NULL)
        throw "Open file error.";
    
    for (int i = 0;i < N;i++)
    {
        string filename = std::to_string(i) + ".txt";
        if ((ftemp_block[i] = fopen(filename.c_str(),"w"))==NULL)
            throw "Open file error.";
    }

    //split url to hash(url)%500 th block
    while (fscanf(fin,"%s",url)!=EOF)
    {
        unsigned int m = SDBM_hash(url) % N;
        fprintf(ftemp_block[m],"%s\n",url);
    }
    
    fclose(fin);
    for (int i = 0;i < N;i++)
        fclose(ftemp_block[i]);
};

//count num for all block
void TopUrl::count_for_all_block()
{
    for (int i = 0;i < N;i++)
    {
        string filename = std::to_string(i) + ".txt";
        if ((ftemp_block[i] = fopen(filename.c_str(),"r"))==NULL)
            throw "Open file error.";
    }
    if ((fcollect = fopen("collect.txt","w"))==NULL)
        throw "Open file error.";

    for (int i = 0;i < N;i++)
    {
        hashmap.clear();
        //count num
        while (fscanf(ftemp_block[i],"%s",url)!=EOF)
        {
            string ss = url;
            hashmap[ss]++;
        }

        //heap-sort
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
                fprintf(fcollect,"%d %s\n",temp.first,temp.second.c_str());
            }
    }

    for (int i = 0;i < N;i++)
        fclose(ftemp_block[i]);
    fclose(fcollect);
};

//collect all result
void TopUrl::collect_all_result()
{
    if ((fcollect = fopen("collect.txt","r"))==NULL)
        throw "Open file error.";
    if ((fout = fopen("answer.txt","w"))==NULL)
        throw "Open file error.";
    
    //heap-sort
    while (priqueue.size()) priqueue.pop();
    while (fscanf(fcollect,"%d %s",&countnum,url)!=EOF)
    {
        priqueue.push(std::make_pair(countnum,url));
        if (priqueue.size() > 100)
            priqueue.pop(); 
    }

    //Reverse output
    vector<pair<int,string>> answer;
    while (priqueue.size())
        {
            pair<int,string> temp = priqueue.top();
            priqueue.pop();
            answer.push_back(temp);
        }
    for (int i = answer.size()-1;i >= 0;i--)
        fprintf(fout,"%s %d\n",answer[i].second.c_str(),answer[i].first);

    fclose(fout);
};

//clear temp file
void TopUrl::clear_temp_file()
{
    remove("collect.txt");
    for (int i = 0;i < N;i++)
    {
        fclose(ftemp_block[i]);
        string filename = std::to_string(i) + ".txt";
        remove(filename.c_str());
    }
}