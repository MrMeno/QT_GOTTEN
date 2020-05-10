#include "httpService.h"
httpService::httpService(QObject *parent):QObject(parent)
{
   http=new HttpUtil();
}

void httpService::login(QJsonObject *LoginDTO,std::function<void(QJsonObject json)> call){
    http->put(QUrl("/login"), LoginDTO, call);
}
