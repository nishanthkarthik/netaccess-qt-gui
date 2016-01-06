#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include "curl/curl.h"
#include "cstring"
#include "cstdio"
#include "cstdlib"
#include "vector"
#include "map"
#include "libnetaccess.h"

using namespace std;

bool validateInput(QLineEdit* _qRollNo, QLineEdit* _qPassWd);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton* button = findChild<QPushButton*>("authButton");
    connect(button, SIGNAL (released()),this, SLOT (handleButton()));
}

int MainWindow::handleButton()
{
    QLineEdit* qRollNo = findChild<QLineEdit*>("rollLineEdit");
    QLineEdit* qPassWd = findChild<QLineEdit*>("passLineEdit");
    QPushButton* qAuthButton = findChild<QPushButton*>("authButton");
    if (!validateInput(qRollNo,qPassWd))
    {
        QMessageBox messageBox;
        messageBox.setText("One or more inputs are empty");
        qDebug("Empty QLineEdit");
        messageBox.exec();
        return -1;
    }

    CURL* curl;
    CURLcode result;
    string rollno, password, loginbody, approvebody;

    rollno = string(qRollNo->text().toUtf8());
    password = string(qPassWd->text().toUtf8());

    loginbody = params_string({
                                  {"userLogin", rollno},
                                  {"userPassword", password},
                                  {"submit", ""}
                              });
    approvebody = params_string({
                                    {"duration", "2"},
                                    {"approveBtn", ""}
                                });
    curl = curl_easy_init();

    if (curl)
    {
        //Get initial session state
        curl_easy_setopt(curl, CURLOPT_URL, LOGIN_URL);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "");
        result = curl_easy_perform(curl);
        errorcheck(result);

        //Post login credentials
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, 	loginbody.c_str());
        result = curl_easy_perform(curl);
        errorcheck(result);

        //Check login validity
        char* redirecturl;
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &redirecturl);
        debugmsg("redirected to " + string(redirecturl));
        string redirectstring(redirecturl);

        if (redirectstring.compare(LOGIN_SUCCESS_URL) != 0)
        {
            QMessageBox messageBox;
            messageBox.setText("Invalid credentials");
            qDebug("Invalid credentials");
            messageBox.exec();
        }

        //Post approve data
        curl_easy_setopt(curl, CURLOPT_URL, APPROVE_URL);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, approvebody.c_str());
        debugmsg(string("sending approve request"));
        result = curl_easy_perform(curl);
        if (!errorcheck(result))
        {
            qAuthButton->setText("Approved for 1 day");
            debugmsg(string("approved for 1 day"));
        }
    }
    return 0;
}

bool validateInput(QLineEdit* _qRollNo, QLineEdit* _qPassWd)
{
    QString rollNo = _qRollNo->text();
    QString passWd = _qPassWd->text();
    if (rollNo.length() == 0 || passWd.length() ==0)
        return false;
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}
