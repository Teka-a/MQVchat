#include "application.h"

Application::Application()
{
    Curve *secp256k1 = Curve::getInstance();
    connect(Client::getInstance(), &Client::receivedMyOpenKey, this, &Application::checkSecretKey);
    connect(Client::getInstance(), &Client::receivedServerShortTermOpenKey, this, &Application::shareSecret);

    //qDebug() << QCoreApplication::instance();
}

Application::~Application()
{

}

void Application::formString30(std::string &option){
    while (option.length() < 31) {
        option += " ";
    }
}

void Application::authentication()
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
        qDebug() << " ";
        qDebug() << "Authentication...";
        qDebug() << "Welcome user1!";
        requestOpenKey(QString::fromStdString(login));
    }
    else
        std::cout << "Sorry, server is not started :(\nTry later!\n";

}

void Application::checkSecretKey(Point openKey)
{
    //qDebug() << "checkKey";
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

void Application::shareSecret(Point longTermOpenKey, Point shortTermOpenKey)
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
    getUserOption();
}



void Application::showHelp()
{
    std::cout << "GENERAL" << std::endl;
    std::string option = "";

    option = "\thelp";
    formString30(option);
    std::cout << option;
    std::cout << "Show this message" << std::endl;

    option = "\tauth";
    formString30(option);
    std::cout << option;
    std::cout << "Log in to your account" << std::endl;

    option = "\tstatus";
    formString30(option);
    std::cout << option;
    std::cout << "Check account and connection information" << std::endl;

    option = "\tnews";
    formString30(option);
    std::cout << option;
    std::cout << "Check for new messages and chat requests" << std::endl;

    std::cout << "CHAT" << std::endl;

    option = "\tlist chats";
    formString30(option);
    std::cout << option;
    std::cout << "List all chats" << std::endl;

    option = "\tchat [chat_name]";
    formString30(option);
    std::cout << option;
    std::cout << "Enter selected chat" << std::endl;

    option = "\tlist requests";
    formString30(option);
    std::cout << option;
    std::cout << "List all requests" << std::endl;

    option = "\taccept request [login]";
    formString30(option);
    std::cout << option;
    std::cout << "Accept request from selected user" << std::endl;

    option = "\tsend m [chat_name]";
    formString30(option);
    std::cout << option;
    std::cout << "Send message to selected chat" << std::endl;


    std::cout << "To exit press Ctrl+C" << std::endl;
    getUserOption();
}

void Application::getUserOption()
{
    std::cout << "secretChat> ";
    std::string input = "";
    getline(std::cin, input);
    if (input == "help") {
        showHelp();
    }
    else if (input == "auth") {
        authentication();
    }
    else if (input == "encrypt") {
        std::string plaintext = "1122334455667700ffeeddccbbaa998800112233445566778899aabbcceeff0a112233445566778899aabbcceeff0a002233445566778899aabbcceeff0a0011";
        std::string key = "8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef";
        std::string IV = "1234567890abcef0a1b2c3d4e5f0011223344556677889901213141516171819";

        std::cout << "Enter string to encrypt: ";
        getline(std::cin, plaintext);
        //std::cout << "Enter key: ";
        //getline(std::cin, key);
        //std::cout << "Enter IV: ";
        //getline(std::cin, IV);
        QString m = encryptKuznechikOFB(QString::fromStdString(plaintext).toUtf8().toHex(), QString::fromStdString(key), QString::fromStdString(IV));
        QString p = decryptKuznechikOFB(m, QString::fromStdString(key), QString::fromStdString(IV));
        QByteArray hex = QByteArray::fromHex(p.toUtf8());
        qDebug() << hex.data();
        QString str = QString::fromUtf8(hex);

        getUserOption();
    }
    else {
        getUserOption();
    }
}
