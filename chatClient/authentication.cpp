#include "authentication.h"

Authentication::Authentication()
{
    Curve *secp256k1 = Curve::getInstance();
    //connect(Client::getInstance(), &Client::receivedMyOpenKey, this, &Authentication::checkSecretKey);
    //connect(Client::getInstance(), &Client::receivedServerShortTermOpenKey, this, &Authentication::shareSecret);

}


Authentication::~Authentication()
{

}

void Authentication::authentication()
{

    if (Client::getInstance()->getServerStatus() == "active"){
        std::string login = "";
        std::string password = "";
        std::string privateKey = "";
        std::string pathDB = "";
        std::string passwordDB = "";

        std::cout << "Login:  ";
        std::getline(std::cin, login);
        Client::getInstance()->setLogin(QString::fromStdString(login));

        char *pass;
        pass = getpass("Password: ");
        int size_arr = sizeof(pass) / sizeof(char);
        for (int x = 0; x < size_arr; x++) {
            password += pass[x];
        }

        pass = getpass("Private Key: ");
        size_arr = sizeof(pass) / sizeof(char);
        for (int x = 0; x < size_arr; x++) {
            privateKey += pass[x];
        }
        Client::getInstance()->setPrivateKey((uint1024_t)privateKey);

        std::cout << "Path to database:  ";
        std::getline(std::cin, pathDB);
        Client::getInstance()->setPathDB(QString::fromStdString(pathDB));

        pass = getpass("Password for db: ");
        size_arr = sizeof(pass) / sizeof(char);
        for (int x = 0; x < size_arr; x++) {
            passwordDB += pass[x];
        }
        Client::getInstance()->setDBPass(QString::fromStdString(passwordDB));

        requestOpenKey(QString::fromStdString(login));
    }
    else
        std::cout << "Sorry, server is not started :(\nTry later!\n";

}

void Authentication::checkSecretKey(Point openKey)
{
    qDebug() << "checkKey";
    //std::cout << "checkSecretKey";
    uint1024_t privateKey = Client::getInstance()->getPrivateKey();

    Point calculatedOpenKey = secp256k1->countComposition(privateKey);

    if(openKey.x != calculatedOpenKey.x || openKey.y != calculatedOpenKey.y){
        std::cout << "Wrong parameter! You'll be disconnected!";
        Client::getInstance()->disconnect();
    }
    else{
        uint1024_t shortTermPrivateKey = generateShortTermPrivateKey();
        Client::getInstance()->setMyServerShortTermPrivateKey(shortTermPrivateKey);
        Point shortTermOpenKey = Curve::getInstance()->countComposition(shortTermPrivateKey);
        sendShortTermOpenKey(shortTermOpenKey);
    }


}

void Authentication::shareSecret(Point longTermOpenKey, Point shortTermOpenKey)
{
    //std::cout << "share secret";
    uint1024_t dA = Client::getInstance()->getPrivateKey();
    uint1024_t kA = Client::getInstance()->getMyServerShortTermPrivateKey();
    Point qA = Curve::getInstance()->countComposition(dA);
    Point rA = Curve::getInstance()->countComposition(kA);
    Point keyPoint = MQV("Server", dA, kA, qA, rA, longTermOpenKey, shortTermOpenKey);
    QString keyStr = QString::fromStdString(keyPoint.x.str()) + QString::fromStdString(keyPoint.y.str());
    //qDebug() << "Key str" << keyStr << " length: " << keyStr.length();
    //qDebug() << keyStr.toUtf8().toHex();
    emit authStatus(1);
}
