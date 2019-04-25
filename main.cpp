#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <ctime>

#include "TopUrl.h"

int main()
{
    try{
    
    TopUrl *topurl = new TopUrl();
    topurl->preprocess();
    topurl->count_for_all_block();
    topurl->collect_all_result();
    topurl->clear_temp_file();
    delete topurl;

    }catch (const char* err_message)
    {
        std::cerr << err_message << std::endl;
        exit(1);
    }
    return 0;
}