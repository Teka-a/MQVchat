#include "authform.h"
#include "client.h"
#include "curve.h"
#include <QApplication>
#include <QStyleFactory>

client * client::p_instance=0;
clientDestroyer client::destroyer;
QTcpSocket * client::mTcpSocket;
Curve * Curve::pInstance=0;
CurveDestroyer Curve::destroyer;
int Curve::a;
int Curve::b;
uint256_t Curve::p;
Point Curve::G;
Point Curve::O;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QPalette darkPalette;
    //darkPalette.setColor(QPalette::Active, QPalette::Window, QColor("#05050a"));
    //darkPalette.setColor(QPalette::Inactive, QPalette::Window, QColor("050815"));
    //darkPalette.setColor(QPalette::Active, QPalette::WindowText, QColor("#ffffff"));
    //darkPalette.setColor(QPalette::Active, QPalette::Base, QColor("#e6e6fa"));
   //darkPalette.setColor(QPalette::Active, QPalette::AlternateBase, QColor("#8884a2"));
    //darkPalette.setColor(QPalette::Active, QPalette::Highlight, QColor("#848cb8"));
    //darkPalette.setColor(QPalette::Active, QPalette::PlaceholderText, QColor("#3f3f3f"));
    //darkPalette.setColor(QPalette::Active, QPalette::Button, QColor("#4d4c72"));
    //darkPalette.setColor(QPalette::Active, QPalette::ButtonText, QColor("#ffffff"));
    client *cl = client::getInstance();
    AuthForm authenticationForm;
    //authenticationForm.setPalette(darkPalette);
    authenticationForm.show();

    return a.exec();
}
