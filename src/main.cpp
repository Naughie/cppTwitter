#include<cstdio>
#include "client.h"

using namespace twitter;

int main(int argc, char const* argv[])
{
  string s;
  s << encoder::base64_encode<const char>("ankbaakbtsbc.a", '\0');
  s.print();
  return 0;
}
