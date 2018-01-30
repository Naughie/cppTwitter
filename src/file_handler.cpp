#include "file_handler.h"

namespace twitter
{

file_handler::file_handler()
  : files()
{
  mkdir(TMP_DIR, DIR_MODE);
  files[OUT] = STDOUT;
  files[LOG] = STDERR;
  files[IDS] = files[LOG];
}

file_handler::file_handler(char *outputter, char *logger)
  : files()
{
  mkdir(TMP_DIR, DIR_MODE);
  files[OUT] = open(outputter, OPEN_MODE, CREATE_MOED);
  files[LOG] = open(logger   , OPEN_MODE, CREATE_MOED);
  files[IDS] = files[LOG];
}

file_handler::file_handler(char *outputter, char *logger, char *ids_store)
  : files()
{
  mkdir(TMP_DIR, DIR_MODE);
  files[OUT] = open(outputter, OPEN_MODE, CREATE_MOED);
  files[LOG] = open(logger   , OPEN_MODE, CREATE_MOED);
  files[IDS] = open(ids_store, OPEN_MODE, CREATE_MOED);
}

file_handler::~file_handler()
{
  for (int i = 0; i < 3; ++i)
    if (files[i] > 2)
      close(files[i]);
}

}
