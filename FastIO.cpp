#include "FastIO.h"

FastIO::FastIO()
{
    r_len = 0, r_pos = 0;
    rbuf = (char*)calloc(sizeof(char) , BufSize);
    fin = stdin;
}

FastIO::FastIO(FILE* _fin):fin(_fin)
{
    r_len = 0, r_pos = 0;
    rbuf = (char*)calloc(sizeof(char) , BufSize);
}
int FastIO::rchar() {
    if (r_pos == r_len)
        r_pos = 0, r_len = fread(rbuf, 1, BufSize, fin);
    if (r_pos == r_len) return EOF;
    return rbuf[r_pos++];
}

int FastIO::rint()
{
    int s = 1, c = rchar(), x = 0;
    while (c <= 32) c = rchar();
    if (c == '-') s = -1, c = rchar();
    for (; '0' <= c && c <= '9'; c = rchar()) x = x * 10 + c - '0';
    return x * s;
}
int FastIO::rstring(char *s)
{
    int c = rchar(); if (c == EOF) return EOF;
    while (c <= 32) c = rchar();
    for (; c > 32; c = rchar()) * s++ = c;
    *s = 0;
    return 0;
}

FastIO::~FastIO()
{
    free(rbuf);
}