#include "libnetaccess.h"
#include "QDebug"
#include "QTextStream"

int debugmsg(string msg)
{
#ifdef DEBUG
    qDebug()<<"> "<<msg.c_str()<<endl;
    return 0;
#endif
}

int debugmsg(char* msg)
{
#ifdef DEBUG
    qDebug()<<"> "<<msg<<endl;
    return 0;
#endif
}

int errorcheck(CURLcode result)
{
#ifdef DEBUG
    if (result != CURLE_OK)
    {
        qDebug()<<"> "<<curl_easy_strerror(result)<<endl;
        return -1;
    }
    return 0;
#endif
}

string params_string(UrlParams const &params)
{
    //http://stackoverflow.com/questions/19978947/libcurl-c-adding-http-get-parameters
    if (params.empty())
        return "";
    UrlParams::const_iterator pb = params.cbegin(), pe= params.cend();
    std::string data= pb-> first+ "="+ pb-> second;
    ++pb;
    if(pb == pe)
        return data;
    for(; pb!= pe; ++ pb)
        data+= "&"+ pb-> first+ "="+ pb-> second;
    return data;
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    return size * nmemb;
}

