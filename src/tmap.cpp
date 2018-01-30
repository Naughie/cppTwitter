#include "tstring.h"
#include "tmap.h"

namespace twitter
{

map::map()
  : body(new string(BUFSIZE)), size(0)
{
}

map::map(string *str, size_t new_size)
  :  body(str), size(new_size)
{
}

map::~map()
{
  delete body;
}

}
