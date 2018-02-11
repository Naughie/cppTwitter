#ifndef TWITTER_ENCODE_H
#define TWITTER_ENCODE_H

#include "constants.h"
#include "tstring.h"
#include "tmap.h"
#include<cstdio>

namespace twitter
{

namespace encoder
{

bool inv_under_url_encode(char c);

template<typename T>
class url_encode
{
  public:
    url_encode();
    url_encode(T *from, char last);
    url_encode(T *from);
    url_encode(string &from, char last);
    url_encode(string &from);
    url_encode(string::iterator &from, char last);
    url_encode(string::iterator &from);
    void operator()(string &to);
  private:
    T *from;
    char last;
};

template<typename T>
class base64_encode
{
  public:
    base64_encode();
    base64_encode(T *from, char last);
    base64_encode(T *from);
    base64_encode(string &from, char last);
    base64_encode(string &from);
    base64_encode(string::iterator &from, char last);
    base64_encode(string::iterator &from);
    void operator()(string &to);
  private:
    T *from;
    char last;
};

}
}
#endif
