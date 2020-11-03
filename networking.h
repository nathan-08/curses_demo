#pragma once
#include <string>
#include <curl/curl.h>

class Networking {
  public:
    static std::string get_string();
    static std::string get_message_from_server();
};

