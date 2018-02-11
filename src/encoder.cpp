#include "encoder.h"
#include "tstring.h"

namespace twitter
{
namespace encoder
{

inline bool inv_under_url_encode(char c)
{
  return (c >= 0x30 && c <= 0x39) || (c >= 0x41 && c <= 0x5a) || (c >= 0x61 && c <= 0x7a) || c == 0x2d || c == 0x2e || c == 0x5f || c == 0x7e;
}

template<typename T>
url_encode<T>::url_encode()
  : from(NULL), last('\0')
{
}

template<typename T>
url_encode<T>::url_encode(T *from, char last)
  : from(from), last(last)
{
}

template<typename T>
url_encode<T>::url_encode(T *from)
  : from(from), last('\0')
{
}

template<typename T>
url_encode<T>::url_encode(string &from, char last)
  : from((T*)from), last(last)
{
}

template<typename T>
url_encode<T>::url_encode(string &from)
  : from((T*)from), last('\0')
{
}

template<typename T>
url_encode<T>::url_encode(string::iterator &from, char last)
  : from((T*)from), last(last)
{
}

template<typename T>
url_encode<T>::url_encode(string::iterator &from)
  : from((T*)from), last('\0')
{
}

template<typename T>
void url_encode<T>::operator()(string &to)
{
  for (auto it = from; *it != last; ++it) {
    if (inv_under_url_encode(*it))
      to << *it;
    else {
      T f = (*it & 0xf0) >> 4;
      T s = *it & 0x0f;
      T ff = (f + 0x30) + 0x07 * (f > 0x09);
      T ss = (s + 0x30) + 0x07 * (s > 0x09);
      T u[] = {'%', ff, ss, '\0'};
      to << u;
    }
  }
}

template class url_encode<char>;
template class url_encode<const char>;

template<typename T>
base64_encode<T>::base64_encode()
  : from(NULL), last('\0')
{
}

template<typename T>
base64_encode<T>::base64_encode(T *from, char last)
  : from(from), last(last)
{
}

template<typename T>
base64_encode<T>::base64_encode(T *from)
  : from(from), last('\0')
{
}

template<typename T>
base64_encode<T>::base64_encode(string &from, char last)
  : from((T*)from), last(last)
{
}

template<typename T>
base64_encode<T>::base64_encode(string &from)
  : from((T*)from), last('\0')
{
}

template<typename T>
base64_encode<T>::base64_encode(string::iterator &from, char last)
  : from((T*)from), last(last)
{
}

template<typename T>
base64_encode<T>::base64_encode(string::iterator &from)
  : from((T*)from), last('\0')
{
}

template<typename T>
void base64_encode<T>::operator()(string &to)
{
  T *it = from;
  int ri = 1;
  while(*++it != last)
    ++ri;
  int rj = (ri - 1) / 3 + 1;
  it = from;
  for (int i = 0; i < rj; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (ri >= i * 3 + j) {
        char x = BASE64_TABLE[(((unsigned char)(it[j - 1])) << (6 - 2 * j) | ((unsigned char)(it[j])) >> (2 * j + 2)) & 0x3f];
        switch (x) {
          case '+':
            to << "%2B";
            break;
          case '/':
            to << "%2F";
            break;
          case '=':
            to << "%3D";
            break;
          default:
            to << x;
            break;
        }
      } else
        to << "%3D";
    }
    it += 3;
  }
}

template class base64_encode<char>;
template class base64_encode<const char>;

}
}
