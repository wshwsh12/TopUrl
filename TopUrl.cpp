#include "TopUrl.h"


TopUrl::TopUrl()
{
    ftemp_block = (FILE **)malloc(sizeof(FILE *) * N);
    ftemp_collect = (FILE **)malloc(sizeof(FILE *) * N);
    url   = (char*)malloc(sizeof (char) * 100000);
}

TopUrl::~TopUrl()
{
    free(ftemp_block);
    free(ftemp_collect);
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
    FastIO *io = new FastIO(fin);
    while (io->rstring(url)!=EOF)
    {
        unsigned int m = SDBM_hash(url) % N;
        fprintf(ftemp_block[m],"%s\n",url);
    }
    delete io;

    fclose(fin);
    for (int i = 0;i < N;i++)
        fclose(ftemp_block[i]);
};

void TopUrl::count_for_one_block(int n,int in_thread_num)
{
    unordered_map<string,int>::iterator it;

    Thread_resource &resource = thread_resource[in_thread_num];
    //init
    resource.hashmap->clear();
    while (resource.priqueue->size())
        resource.priqueue->pop();
    resource.reset(ftemp_block[n]);

    //count num
    while (resource.io->rstring(resource.url)!=EOF) 
    {
        string ss = resource.url;
        (*resource.hashmap)[ss]++;
    }

    //heap-sort
    while (resource.priqueue->size()) resource.priqueue->pop();
    for (it = resource.hashmap->begin();it != resource.hashmap->end();it++)
        {
            resource.priqueue->push(make_pair(it->second,it->first));
            if (resource.priqueue->size() > 100)
                resource.priqueue->pop();
        }
    while (resource.priqueue->size())
        {
            pair<int,string> temp = resource.priqueue->top();
            resource.priqueue->pop();
            fprintf(ftemp_collect[n],"%d %s\n",temp.first,temp.second.c_str());
        }
    
    fclose(ftemp_block[n]);
    fclose(ftemp_collect[n]);

    threads_status[in_thread_num] = false;
    running_threads_num--;

}

//count num for all block
void TopUrl::count_for_all_block()
{
    running_threads_num = 0;

    for (int i = 0;i < N;i++)
    {
        while (running_threads_num >= 5);
        running_threads_num++;

        string filename = std::to_string(i) + ".txt";
        if ((ftemp_block[i] = fopen(filename.c_str(),"r"))==NULL)
            throw "Open file error.";
        
        filename = std::to_string(i) + "-collect.txt";
        if ((ftemp_collect[i] = fopen(filename.c_str(),"w"))==NULL)
            throw "Open file error.";
        
        int in_thread_num = 0;
        while (threads_status[in_thread_num]) in_thread_num++;
        threads_status[in_thread_num] = true;

        running_threads.push_back(thread(&TopUrl::count_for_one_block,this,i,in_thread_num));
    }

    for (int i = 0;i < N;i++)
        running_threads[i].join();
};

//collect all result
void TopUrl::collect_all_result()
{
    if ((fout = fopen("answer.txt","w"))==NULL)
        throw "Open file error.";
    
    priority_queue_pair_int_string *priqueue = new priority_queue_pair_int_string();  
    for (int i = 0;i < N;i++)
    {
        string filename = std::to_string(i) + "-collect.txt";
        if ((ftemp_collect[i] = fopen(filename.c_str(),"r"))==NULL)
            throw "Open file error.";

        //heap-sort
        while (fscanf(ftemp_collect[i],"%d %s",&countnum,url)!=EOF)
        {
            priqueue->push(std::make_pair(countnum,url));
            if (priqueue->size() > 100)
                priqueue->pop(); 
        }

        fclose(ftemp_collect[i]);
    }

    //Reverse output
    vector<pair<int,string>> answer;
    while (priqueue->size())
    {
        pair<int,string> temp = priqueue->top();
        priqueue->pop();
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
        filename = std::to_string(i) + "-collect.txt";
        remove(filename.c_str());
    }
}