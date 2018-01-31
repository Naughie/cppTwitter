#ifndef TWITTER_CONSTANTS_H
#define TWITTER_CONSTANTS_H

namespace twitter
{

#define PATH_TO_(do_sth) PATH_##do_sth

typedef enum Protocol_t
{
  HTTP,
  HTTPS
} Protocol;

typedef enum HttpMethod_t
{
  GET,
  POST
} HttpMethod;

typedef enum ResponseType_t
{
  TWEET,
  TWEETS,
  USER,
  USERS,
  NONE
} ResponseType;

typedef enum FileType_t
{
  OUT,
  LOG,
  IDS
} FileType;

typedef enum EncodeMethod_t
{
  BASE64_ENCODE,
  URL_ENCODE,
  DOUBLE_URL_ENCODE
} EncodeMethod;

static constexpr unsigned int BUFSIZE = 1024;
static constexpr unsigned int BUFSIZE_L = 524288;

using file_descriptor = int;
static constexpr file_descriptor STDIN  = 0;
static constexpr file_descriptor STDOUT = 1;
static constexpr file_descriptor STDERR = 2;

static const char TMP_DIR[]          = "/tmp/twitter_cpp";
static const char TMP_LOG[]          = "/tmp/twitter_cpp/request_log";
static const char TMP_TWEET_IDS[]    = "/tmp/twitter_cpp/tweet_ids";
static const char TMP_HOMETIMELINE[] = "/tmp/twitter_cpp/home_timeline";

static const char PATH_GET_HOME_TIMELINE[] = "/1.1/statuses/home_timeline.json";
static const char PATH_POST_TWEET[]        = "/1.1/statuses/update.json";

static const char BASE64_TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

}
#endif
