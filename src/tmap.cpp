#include "tstring.h"
#include "tmap.h"

namespace twitter
{

map::map()
  : body(new string(BUFSIZE)), pairs()
{
}

map::map(string *str)
  :  body(str), pairs()
{
}

map::~map()
{
  delete body;
}

}
