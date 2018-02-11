#ifndef TWITTER_TSTRING_H
#define TWITTER_TSTRING_H

#include "constants.h"
#include<cstdio>
#include<cstring>
#include<random>
#include<utility>
#include<openssl/hmac.h>

namespace twitter
{

class string
{
  public:
    class iterator;
    string();
    string(unsigned int buf_size);
    ~string();
    iterator begin();
    iterator end();
    size_t size();
    template<typename T>
    explicit operator T() const;
    void print();
    template<typename T>
    string &operator<<(T *str);
    template<typename T>
    string &operator<<(T &str);
    template<typename T>
    string &operator<<(const T &str);
    string &operator<<(char c);
    string &operator<<(int n);
    string &operator<<(unsigned int n);
    string &operator<<(long n);
    string &operator<<(unsigned long n);
    template<typename T, template<typename> class F>
    string &operator<<(F<T> functor);
    class iterator
    {
      public:
        iterator();
        iterator(char *s);
        iterator &operator=(const iterator &that);
        ~iterator();
        explicit operator char*() const;
        explicit operator const char*() const;
        template<typename T>
        iterator operator+(T n);
        template<typename T>
        iterator operator-(T n);
        iterator operator++(int);
        iterator operator--(int);
        iterator &operator++();
        iterator &operator--();
        char &operator*() const noexcept;
        bool operator<(iterator &that);
        bool operator<=(iterator &that);
        bool operator>(iterator &that);
        bool operator>=(iterator &that);
        bool operator==(iterator &that);
        bool operator!=(iterator &that);
      private:
        char *ptr;
    };
  private:
    char *body;
    size_t len;
    void push_char(char c);
    void push_back(char *str);
    void push_back(const char *str);
    void push_back(string &str);
    template<typename T, template<typename> class F>
    void encode(F<T> &functor);
    template<typename T>
    void push_back(T n);
};

}
#endif
