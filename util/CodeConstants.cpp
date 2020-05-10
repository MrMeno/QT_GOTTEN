#include "CodeConstants.h"

 CodeHelper::CodeHelper(QObject *parent):QObject(parent)
{

}

 QString CodeHelper::API_HEARTBEAT= "/heartbeat";
 QString CodeHelper::API_LOGIN= "/login";
 QString CodeHelper::API_CHANGE_PSW= "/free/change/password";
 QString CodeHelper::API_GET_BANK_DOMAIN= "/free/get/bankdomain";
 QString CodeHelper::API_GET_RECEIOT_BANK_DOMAIN= "/free/get/receipt/bankdomain";
 QString CodeHelper::API_LOGOUT= "/logout";
 QString CodeHelper::API_GET_ORG= "/free/get/orgcode";
 QString CodeHelper::API_BILL_UPLOAD= "/bill/text/upload";
 QString CodeHelper::API_RECEIPT_UPLOAD= "/receipt/text/upload";
 QString CodeHelper::API_BILL_LIST= "/bill/list";
 QString CodeHelper::API_BILL_UPDATE= "/bill/update/{0}/{1}";
 QString CodeHelper::API_BILL_DETAIL= "/bill/view/init/{0}/{1}";
 QString CodeHelper::API_RECEIPT_DETAIL= "/receipt/view/init/{0}/{1}";
 QString CodeHelper::API_BILL_REFUSE= "/bill/edit/rejected/{0}/{1}";
 QString CodeHelper::API_APP_INFO= "/free/get/app/versionAuto";
 QString CodeHelper::API_LIST_PAGE= "/bill/list/page";
 QString CodeHelper::API_LIST_RECIPT= "/receipt/list/page";
 QString CodeHelper::API_POST_EXCEPTION= "/client/exception";
 QString CodeHelper::API_GET_ACCOUNT= "/sign/account/get/account/{0}";
 QString CodeHelper::API_ACCOUNT_UPLOAD= "/sign/account/add/save";
 QString CodeHelper::API_PUBLISH_INIT= "/bill/publish/init";
 QString CodeHelper::API_PUBLISH_UPLOAD= "/bill/publish/push";
 QString CodeHelper::API_PUBLISH_ACCOUNTLIST= "/bill/publish/get/account";
 CodeHelper::~CodeHelper(){
     delete this;
 }


