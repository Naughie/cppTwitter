#include "tstring.h"
#include "tmap.h"

namespace twitter
{

string::string()
  : body(new char[BUFSIZE]), size(0)
{
}

string::string(unsigned int buf_size)
  : body(new char[buf_size]), size(0)
{
}

string::~string()
{
  delete [] body;
}

char *string::begin()
{
  return body;
}

char *string::end()
{
  return body + size;
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

string &string::operator<<(char c)
{
  push_back(c);
  return *this;
}

void string::push_back(char c)
{
  *(body + size++) = c;
}

void string::push_back(char *str)
{
  int len = strlen(str);
  memcpy(body + size, str, len);
  size += len;
}

void string::push_back(const char *str)
{
  int len = strlen(str);
  memcpy(body + size, str, len);
  size += len;
}

}
