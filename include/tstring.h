#ifndef TWITTER_TSTRING_H
#define TWITTER_TSTRING_H

#include "constants.h"
#include<random>
#include<utility>
#include<openssl/hmac.h>

namespace twitter
{

class map;

class string
{
  public:
    string();
    string(unsigned int buf_size);
    ~string();
    char *begin();
    char *end();
    template<typename T>
    string &operator<<(T *str);
    template<typename T>
    string &operator<<(T &str);
    string &operator<<(char c);
  private:
    char *body;
    size_t size;
    void push_back(char c);
    void push_back(char *str);
    void push_back(const char *str);
};

}
#endif
