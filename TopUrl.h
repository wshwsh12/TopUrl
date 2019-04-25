#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>
#include <unordered_map>
#include <queue>

#include <thread>
#include <atomic>
#include <mutex>

#include "SDBMHash.h"
#include "FastIO.h"

using std::pair;
using std::string;
using std::vector;
using std::unordered_map;
using std::priority_queue;

using std::thread;
using std::atomic;
using std::mutex;

class TopUrl
{
    public:
    typedef priority_queue<pair<int,string>,vector<pair<int,string>>,std::greater<pair<int,string>>> priority_queue_pair_int_string;
    
    TopUrl();

    ~TopUrl();
    //split data to block
    void preprocess();

    //count num for n-th block
    void count_for_one_block(int n,int in_thread_num);

    //count num for all block
    void count_for_all_block();

    //collect all result
    void collect_all_result();

    //clear temp file
    void clear_temp_file();

    private:
    FILE *fin,*fout;

    FILE **ftemp_block,**ftemp_collect;

    char* url;
    int countnum;
    const int N = 500;


    //thread
    #define thread_num 5
    struct Thread_resource
    {
        FastIO *io;
        char *url;
        
        unordered_map<string,int> *hashmap;
        priority_queue_pair_int_string *priqueue;

        Thread_resource() 
        {
            io = new FastIO(stdin);
            url = (char *)malloc(sizeof(char) * 100000);

            hashmap = new unordered_map<string,int>();
            priqueue = new priority_queue_pair_int_string();

        }
        ~Thread_resource()
        {
            delete io;
            free(url);

            delete hashmap;
            delete priqueue;
        }
        void reset(FILE *fin)
        {
            io->reset(fin);
        }
    }thread_resource[thread_num];

    vector<thread> running_threads;
    atomic<int> running_threads_num;
    bool threads_status[thread_num];
};