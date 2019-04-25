#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

class FastIO {

    public:
    FastIO();
    FastIO(FILE* _fin);
    ~FastIO();

    // read interface
    int rchar();
    int rint();
    int rstring(char *s);

    //reuse
    void reset(FILE *fin);

    private:
    static const int BufSize = 1e7;
    FILE *fin;
    int r_len,r_pos;
    char *rbuf;
};