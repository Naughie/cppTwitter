#ifndef TWITTER_TMAP_H
#define TWITTER_TMAP_H

#include "constants.h"
#include "tstring.h"

namespace twitter
{

class map
{
  public:
    map();
    map(string *str, size_t new_size);
    ~map();
  private:
    string *body;
    size_t size;
};

}
#endif
