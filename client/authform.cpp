#include "authform.h"
#include "ui_authform.h"

AuthForm::AuthForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthForm)
{
    ui->setupUi(this);
}

AuthForm::~AuthForm()
{
    delete ui;
}



void AuthForm::on_enterButton_clicked()
{
    QString login = ui->login->text();
    QString pass = ui->password->text();
    QString key = ui->secretKey->text();
    qDebug() << login;
    qDebug() << pass;
    qDebug() << key;
}

