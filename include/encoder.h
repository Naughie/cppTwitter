#ifndef TWITTER_ENCODE_H
#define TWITTER_ENCODE_H

#include "constants.h"

namespace twitter
{

class string;
class map;

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
    void operator()(string &to);
  private:
    T *from;
    char last;
};

}
}
#endif
