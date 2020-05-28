#ifndef CUSTOMERDIALOG_H
#define CUSTOMERDIALOG_H

#include <QDialog>
#include <functional>
namespace Ui {
class CustomerDialog;
}
enum DialogRes{
    YES=0,
    NO=1,
    SUBMIT=2,
    CANCEL=3,
    YESORNO=4,
    SUBCANCEL=5
};
extern int DResult;//弹窗的返回结构
class CustomerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomerDialog(QWidget *parent = 0,QJsonObject *config=nullptr,int type=YES);
    void uiFormat(int type,QJsonObject config);
    std::function<void(int res)> ResCallBack;
    bool eventFilter(QObject *obj, QEvent *event);
    ~CustomerDialog();
private:
    Ui::CustomerDialog *ui;
    QString titleText="小ai签票";
    QString yesBtnText="是";
    QString noBtnText="否";
    QString submitBtnText="提交";
    QString cancelBtnText="取消";
    QString contentText;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CUSTOMERDIALOG_H
