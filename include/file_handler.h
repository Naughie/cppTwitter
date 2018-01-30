#ifndef TWITTER_FILE_HANDLER_H
#define TWITTER_FILE_HANDLER_H

#include "constants.h"
#include "tstring.h"
#include<cstdlib>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<unistd.h>

namespace twitter
{

class file_handler
{
  public:
    file_handler();
    file_handler(char *outputter, char *logger);
    file_handler(char *outputter, char *logger, char *ids_store);
    ~file_handler();
  private:
    file_descriptor files[3];
};

static constexpr int DIR_MODE    = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH;
static constexpr int OPEN_MODE   = O_RDWR  | O_APPEND | O_CREAT;
static constexpr int CREATE_MOED = S_IREAD | S_IWRITE;

}
#endif
