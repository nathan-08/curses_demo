#include "networking.h"

size_t write_callback( char *ptr, size_t size, size_t nmemb, void *readBuffer ) {
  size_t realsize = size * nmemb;
  ((std::string*)readBuffer)->append( (char*)ptr, realsize );
  return realsize;
}

std::string Networking::get_string() {
  return "test_001 test_001 test_001 test_001 test_001";
}

std::string Networking::get_message_from_server() {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if( curl ) {
    std::string readBuffer;
    curl_easy_setopt( curl, CURLOPT_URL, "http://localhost:1337" );
    curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_callback );
    curl_easy_setopt( curl, CURLOPT_WRITEDATA, &readBuffer );

    res = curl_easy_perform( curl );
    curl_easy_cleanup( curl );
    
    if ( res == CURLE_OK ) 
      return readBuffer;
  }
  return "{\"message\":\"Failed to contact server.\"}";
}
