#include "tstring.h"
#include "tmap.h"
#include "encoder.h"

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

template<typename T>
string::operator T() const
{
  return (T)(this->body);
}

template string::operator char*() const;
template string::operator const char*() const;

void string::print()
{
  for (const auto &it : *this)
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

template<typename T>
string &string::operator<<(const T &str)
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

template<typename T, template<typename> class F>
string &string::operator<<(F<T> functor)
{
  encode(functor);
  return *this;
}

template string &string::operator<<<const char, encoder::url_encode>(encoder::url_encode<const char>);
template string &string::operator<<<const char, encoder::base64_encode>(encoder::base64_encode<const char>);
template string &string::operator<<<char, encoder::url_encode>(encoder::url_encode<char>);
template string &string::operator<<<char, encoder::base64_encode>(encoder::base64_encode<char>);

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

template<typename T, template<typename> class F>
void string::encode(F<T> &functor)
{
  functor(*this);
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

string::iterator::operator char*() const
{
  return ptr;
}

string::iterator::operator const char*() const
{
  return (const char*)ptr;
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
