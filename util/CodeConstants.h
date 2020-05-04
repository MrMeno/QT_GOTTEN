#define pragma execution_character_set("utf-8")
#ifndef CODEHELPER_H
#define CODEHELPER_H
#define CODE_SUCCESS "000000"
#define CODE_SERVER_ERR "010001"
#define CODE_PSW_OUTDATE "010011"
#define CODE_BILL_FRONT_EXIST "020001"
#define CODE_BILL_BACK_EXIST "020002"
#define CODE_NO_LOGIN "990010"
#define CODE_SYS_ERROR "999999"
#define CODE_SYS_ERROR_MSG "网络异常"
#define CODE_USER_KICK_OUT "010005"
#define CODE_UPLOAD_DUPLICATE "080103"
#define CODE_USER_UN_AUTHORIZED "010003"

#include <QObject>

class CodeHelper:public QObject
{
    Q_OBJECT
public:
    explicit CodeHelper(QObject *parent = nullptr);
    ~CodeHelper();
};

#endif // CODEHELPER_H
