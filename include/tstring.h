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
    size_t size();
    template<typename T>
    string &operator<<(T *str);
    template<typename T>
    string &operator<<(T &str);
    string &operator<<(char c);
    string &operator<<(int n);
    string &operator<<(unsigned int n);
    string &operator<<(long n);
    string &operator<<(unsigned long n);
    template<typename T>
    static void encode(EncodeMethod enc, T *from, string &to, char last);
    template<typename T>
    static void encode(EncodeMethod enc, T *from, string &to);
    template<typename T>
    static void encode(EncodeMethod enc, T &from, string &to, char last);
    template<typename T>
    static void encode(EncodeMethod enc, T &from, string &to);
  private:
    char *body;
    size_t len;
    void push_char(char c);
    void push_back(char *str);
    void push_back(const char *str);
    void push_back(string &str);
    template<typename T>
    void push_back(T n);
    static bool inv_under_url_encode(char c);
    template<typename T>
    static void url_encode(T *from, string &to, char last);
    template<typename T>
    static void url_encode(T &from, string &to, char last);
    template<typename T>
    static void base64_encode(T *from, string &to, char last);
    template<typename T>
    static void base64_encode(T &from, string &to, char last);
};

}
#endif
