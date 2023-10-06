#include "ethgui.h"
#include "qvariant.h"

EthGui::EthGui(QObject *parent)
    : QObject{parent}
{

}

QStringList EthGui::itfList()
{
    QStringList namesList;

    QList<QNetworkAddressEntry> addresses;
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    QString itemName;
    QList<QNetworkInterface>::Iterator i;
    QList<QNetworkAddressEntry>::Iterator a;
    for(i=interfaces.begin(); i!=interfaces.end(); i++)
    {
        addresses = (*i).addressEntries();
        for(a=addresses.begin(); a!=addresses.end(); a++)
        {
            if((*a).ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                itemName = (*i).name()+"::"+(*a).ip().toString();
                m_itfList.insert(itemName, (*a).ip());
                namesList.append(itemName);
            }
        }
    }
    return namesList;
}

void EthGui::selectItf(QString itfName)
{
    qDebug() << "Selected itf: " << itfName << " corresponding ip:" << m_itfList.value(itfName);
    emit sgSetHostIP(m_itfList.value(itfName));
}

bool EthGui::setDstIp(QString ip)
{
    QHostAddress targetHostAddress;
    if(targetHostAddress.setAddress(ip))
    {
        emit sgSetDstIP(targetHostAddress);
        return true;
    }
    else
    {
        qDebug() << "Error converting string to ip";
        emit sgErrorMsg(QObject::tr("Неверно задан IP адрес получателя"));
        return false;
    }
}

void EthGui::setDstPort(quint16 port)
{
    emit sgSetDstPort(port);
}

void EthGui::slItfConnected(bool result)
{
    if(result)
    {
        emit sgConnectionOpened();
    }
    else
    {
        emit sgErrorMsg("Не удается подключиться к интерфейсу");
    }
}
