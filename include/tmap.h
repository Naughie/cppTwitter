#ifndef TWITTER_TMAP_H
#define TWITTER_TMAP_H

#include "constants.h"
#include "tstring.h"
#include<map>

namespace twitter
{

using mapstring = std::map<string::iterator, string::iterator>;

class map
{
  public:
    map();
    map(string *str);
    ~map();
  private:
    string *body;
    mapstring pairs;
};

}
#endif
