#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>
#include <unordered_map>
#include <queue>

#include "SDBMHash.h"
#include "FastIO.h"

using std::pair;
using std::string;
using std::vector;
using std::unordered_map;
using std::priority_queue;

class TopUrl
{
    public:

    TopUrl();

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
    
    FILE *fin,*fout,*fcollect;

    FILE **ftemp_block;

    char* url;
    int countnum;
    const int N = 500;

    unordered_map<string,int> hashmap;
    unordered_map<string,int>::iterator it;
    priority_queue<pair<int,string>,vector<pair<int,string>>,std::greater<pair<int,string>>> priqueue;
};