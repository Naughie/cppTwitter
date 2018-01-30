#include "tstring.h"
#include "tmap.h"

namespace twitter
{

string::string()
  : body(new char[BUFSIZE]), len(0)
{
}

string::string(unsigned int buf_size)
  : body(new char[buf_size]), len(0)
{
}

string::~string()
{
  delete [] body;
}

inline char *string::begin()
{
  return body;
}

inline char *string::end()
{
  return body + size();
}

inline size_t string::size()
{
  return len;
}

template<typename T>
string &string::operator<<(T *str)
{
  push_back(str);
  return *this;
}

template string &string::operator<<(char *str);
template string &string::operator<<(const char *str);

template<typename T>
string &string::operator<<(T &str)
{
  push_back(str);
  return *this;
}

template string &string::operator<<(string &str);

string &string::operator<<(char c)
{
  *(body + len++) = c;
  return *this;
}

string &string::operator<<(int n)
{
  push_back<int>(n);
  return *this;
}

string &string::operator<<(unsigned int n)
{
  push_back<unsigned int>(n);
  return *this;
}

string &string::operator<<(long n)
{
  push_back<long>(n);
  return *this;
}

string &string::operator<<(unsigned long n)
{
  push_back<unsigned long>(n);
  return *this;
}

template<typename T>
void string::encode(EncodeMethod enc, T *from, string &to)
{
  switch (enc) {
    case URL_ENCODE:
      url_encode(from, to);
      break;
    case BASE64_ENCODE:
      base64_encode(from, to);
      break;
    default:
      break;
  }
}

template<typename T>
void string::encode(EncodeMethod enc, T &from, string &to)
{
  switch (enc) {
    case URL_ENCODE:
      url_encode(from, to);
      break;
    case BASE64_ENCODE:
      base64_encode(from, to);
      break;
    default:
      break;
  }
}

void string::push_back(char *str)
{
  int size = strlen(str);
  memcpy(end(), str, size);
  len += size;
}

void string::push_back(const char *str)
{
  int size = strlen(str);
  memcpy(end(), str, size);
  len += size;
}

void string::push_back(string &str)
{
  memcpy(end(), str.begin(), str.size());
  len += str.size();
}

template<typename T>
void string::push_back(T n)
{
  char m[20];
  m[19] = 0x30 + n % 10;
  int i = 19;
  while (n /= 10)
    m[--i] = 0x30 + n % 10;
  memcpy(end(), m + i, 20 - i);
  len += 20 - i;
}

template<typename T>
void string::url_encode(T *from, string &to)
{
}

template<typename T>
void string::url_encode(T &from, string &to)
{
}

template<typename T>
void string::base64_encode(T *from, string &to)
{
}

template<typename T>
void string::base64_encode(T &from, string &to)
{
}

}
