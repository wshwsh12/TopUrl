#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>
#include <unordered_map>
#include <queue>
#include <thread>

#include "SDBMHash.h"

using std::pair;
using std::string;
using std::vector;
using std::unordered_map;
using std::priority_queue;

class TopUrl
{
    public:

    TopUrl(int n = 500);

    ~TopUrl();
    //split data to block
    void preprocess();

    //count num for all block
    void count_for_all_block();

    //collect all result
    void collect_all_result();

    //clear temp file
    void clear_temp_file();

    private:
    
    FILE *fin,*fout,*fcount;

    FILE **ftemp;

    char url[101000];
    int countnum;
    int N;

    unordered_map<string,int> hashmap;
    unordered_map<string,int>::iterator it;
    priority_queue<pair<int,string>,vector<pair<int,string>>,std::greater<pair<int,string>>> priqueue;
};