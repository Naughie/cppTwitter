#include<cstdio>
#include "client.h"

using namespace twitter;

int main(int argc, char const* argv[])
{
  string s;
  s << encoder::base64_encode<const char>("askba,..casbka"); // YXNrYmEsLi5jYXNia2E=
  s.print();
  printf("\n");
  string t;
  t << encoder::url_encode<char>(s);
  t.print();
  printf("\n");
  return 0;
}
