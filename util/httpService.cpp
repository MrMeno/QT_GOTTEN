#include "httpService.h"
httpService::httpService(QObject *parent):QObject(parent)
{
   http=new HttpUtil();
}

void httpService::login(QJsonObject *LoginDTO,std::function<void(QByteArray json)> call){
    http->put(QUrl(CodeHelper::API_LOGIN), LoginDTO, call);
}
void httpService::getBillList(QJsonObject *param,std::function<void(QByteArray json)> call){
    http->get(QUrl(CodeHelper::API_LIST_PAGE),param, call);
}
