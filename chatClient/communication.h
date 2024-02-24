#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QString>
#include "client.h"

void requestOpenKey(QString userLogin);
void sendShortTermOpenKey(Point shortTermOpenKey, QString to = "Server");

#endif // COMMUNICATION_H
