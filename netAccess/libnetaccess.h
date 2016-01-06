#ifndef LIBNETACCESS
#define LIBNETACCESS

#include "cstring"
#include "map"
#include "curl/curl.h"
using namespace std;

#define DEBUG
#define LOGIN_URL "https://netaccess.iitm.ac.in/account/login"
#define LOGIN_SUCCESS_URL "https://netaccess.iitm.ac.in/account/index"
#define APPROVE_URL "https://netaccess.iitm.ac.in/account/approve"
#define LOGOUT_URL "https://netaccess.iitm.ac.in/account/approve"
typedef std::map<std::string, std::string> UrlParams;

int debugmsg(string msg);
int debugmsg(char* msg);
int errorcheck(CURLcode result);
string params_string(UrlParams const &params);
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

#endif // LIBNETACCESS

