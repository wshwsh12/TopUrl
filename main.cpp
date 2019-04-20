#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

#include "TopUrl.h"

int main()
{
    TopUrl *topurl = new TopUrl(500);
    topurl->preprocess();
    topurl->count_for_all_block();
    topurl->collect_all_result();
    topurl->clear_temp_file();
    delete topurl;
    return 0;
}