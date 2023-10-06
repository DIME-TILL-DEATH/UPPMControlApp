#ifndef ETHCORE_H
#define ETHCORE_H

#include <QObject>
#include <QUdpSocket>

#include "uppm.h"

class EthCore : public QObject
{
    Q_OBJECT
public:
    explicit EthCore(QObject *parent = nullptr);

    void senRawCommFrame(UPPM_Raw_Command_Frame frameData);
    qint64 writeData(const UPPM& targetUPPM, QByteArray msg);

    void setHostAddress(QHostAddress ipAddr);
    void setDstIp(QHostAddress ipAddr);
    void setDstPort(quint16 dstPort);

signals:
    void sgItfConnected(bool result);
    void sgAckRecieved();

private:
    QUdpSocket* udpSocket;
    UPPM targetPPM;

    void readPendingDatagrams();

    QHostAddress m_dstAddress;
    quint16 m_dstPort;
};

#endif // ETHCORE_H
