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

string::iterator string::begin()
{
  return string::iterator(body);
}

string::iterator string::end()
{
  return string::iterator(body + size());
}

inline size_t string::size()
{
  return len;
}

void string::print()
{
  for (auto &it : *this)
    printf("%c", it);
}

template<typename T>
string &string::operator<<(T *str)
{
  push_back(str);
  return *this;
}

template string &string::operator<<(char*);
template string &string::operator<<(const char*);

template<typename T>
string &string::operator<<(T &str)
{
  push_back(str);
  return *this;
}

template string &string::operator<<(string&);

string &string::operator<<(char c)
{
  push_char(c);
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
void string::encode(EncodeMethod enc, T *from, string &to, char last)
{
  switch (enc) {
    case URL_ENCODE:
      url_encode(from, to, last);
      break;
    case BASE64_ENCODE:
      base64_encode(from, to, last);
      break;
    default:
      break;
  }
}

template<typename T>
void string::encode(EncodeMethod enc, T *from, string &to)
{
  switch (enc) {
    case URL_ENCODE:
      url_encode(from, to, '\0');
      break;
    case BASE64_ENCODE:
      base64_encode(from, to, '\0');
      break;
    default:
      break;
  }
}

template void string::encode(EncodeMethod, char*, string&, char);
template void string::encode(EncodeMethod, const char*, string&, char);
template void string::encode(EncodeMethod, char*, string&);
template void string::encode(EncodeMethod, const char*, string&);

template<typename T>
void string::encode(EncodeMethod enc, T &from, string &to, char last)
{
  switch (enc) {
    case URL_ENCODE:
      url_encode(from, to, last);
      break;
    case BASE64_ENCODE:
      base64_encode(from, to, last);
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
      url_encode(from, to, '\0');
      break;
    case BASE64_ENCODE:
      base64_encode(from, to, '\0');
      break;
    default:
      break;
  }
}

template void string::encode(EncodeMethod, string&, string&, char);
template void string::encode(EncodeMethod, string&, string&);

inline void string::push_char(char c)
{
  *(body + len++) = c;
}

void string::push_back(char *str)
{
  int size = strlen(str);
  memcpy(body + len, str, size);
  len += size;
}

void string::push_back(const char *str)
{
  int size = strlen(str);
  memcpy(body + len, str, size);
  len += size;
}

void string::push_back(string &str)
{
  memcpy(body + len, str.body, str.size());
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
  memcpy(body + len, m + i, 20 - i);
  len += 20 - i;
}

inline bool string::inv_under_url_encode(char c)
{
  return (c >= 0x30 && c <= 0x39) || (c >= 0x41 && c <= 0x5a) || (c >= 0x61 && c <= 0x7a) || c == 0x2d || c == 0x2e || c == 0x5f || c == 0x7e;
}

template<typename T>
void string::url_encode(T *from, string &to, char last)
{
  for (auto it = from; *it != last; ++it)
    if (inv_under_url_encode(*it))
      to.push_char(*it);
    else {
      T f = (*it & 0xf0) >> 4;
      T s = *it & 0x0f;
      T ff = (f + 0x30) + 0x07 * (f > 0x09);
      T ss = (s + 0x30) + 0x07 * (s > 0x09);
      T u[] = {'%', ff, ss, '\0'};
      to.push_back(u);
    }
}

template<typename T>
void string::url_encode(T &from, string &to, char last)
{
}

template<typename T>
void string::base64_encode(T *from, string &to, char last)
{
  T *it = from;
  int ri = 1;
  while(*++it != last)
    ++ri;
  ri = (ri - 1) / 3 + 1;
  it = from;
  for (int i = 0; i < ri; i++) {
    for (int j = 0; j < 4; j++) {
      if (ri >= i * 3 + j) {
        char x = BASE64_TABLE[((unsigned char)it[j - 1] << (6 - 2 * j) | (unsigned char)it[j] >> (2 * j + 2)) & 0x3f];
        switch (x) {
          case '+':
            to.push_back("%2B");
            break;
          case '/':
            to.push_back("%2F");
            break;
          case '=':
            to.push_back("%3D");
            break;
          default:
            to.push_back(x);
            break;
        }
      } else
        to.push_back("%3D");
    }
  }
}

template<typename T>
void string::base64_encode(T &from, string &to, char last)
{
}

string::iterator::iterator()
  : ptr()
{
}

string::iterator::iterator(char *s)
  : ptr(s)
{
}

string::iterator &string::iterator::operator=(const string::iterator &that)
{
  ptr = that.ptr;
  return *this;
}

string::iterator::~iterator()
{
}

template<typename T>
string::iterator string::iterator::operator+(T n)
{
  return string::iterator(ptr + n);
}

template<typename T>
string::iterator string::iterator::operator-(T n)
{
  return string::iterator(ptr - n);
}

string::iterator string::iterator::operator++(int)
{
  auto before = *this;
  ++ptr;
  return before;
}

string::iterator string::iterator::operator--(int)
{
  auto before = *this;
  --ptr;
  return before;
}

string::iterator &string::iterator::operator++()
{
  ++ptr;
  return *this;
}

string::iterator &string::iterator::operator--()
{
  --ptr;
  return *this;
}

char &string::iterator::operator*() const noexcept
{
  return *ptr;
}

bool string::iterator::operator<(string::iterator &that)
{
  return strcmp(ptr, that.ptr) < 0;
}

bool string::iterator::operator<=(string::iterator &that)
{
  return strcmp(ptr, that.ptr) <= 0;
}

bool string::iterator::operator>(string::iterator &that)
{
  return strcmp(ptr, that.ptr) > 0;
}

bool string::iterator::operator>=(string::iterator &that)
{
  return strcmp(ptr, that.ptr) >= 0;
}

bool string::iterator::operator==(string::iterator &that)
{
  return strcmp(ptr, that.ptr) == 0;
}

bool string::iterator::operator!=(string::iterator &that)
{
  return ptr != that.ptr;
}

}
