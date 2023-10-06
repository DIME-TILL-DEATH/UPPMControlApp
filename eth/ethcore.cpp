#include <QNetworkDatagram>

#include "uppm.h"
#include "ethcore.h"

EthCore::EthCore(QObject *parent)
    : QObject{parent}
{
    udpSocket = new QUdpSocket(this);

    connect(udpSocket, &QUdpSocket::readyRead, this, &EthCore::readPendingDatagrams);
}

void EthCore::senRawCommFrame(UPPM_Raw_Command_Frame frameData)
{
    targetPPM.setIpAddr(m_dstAddress);

    writeData(targetPPM, UPPM::formRawCommFrame(frameData));
}

qint64 EthCore::writeData(const UPPM& targetUPPM, QByteArray msg)
{
    qint16 sendedBytes = udpSocket->writeDatagram(msg, targetUPPM.ipAddr(), targetUPPM.controlPort);

    qDebug() << "Udp sended bytes:" << sendedBytes << " target Ip: " << targetUPPM.ipAddr();
    return sendedBytes;
}

void EthCore::setHostAddress(QHostAddress ipAddr)
{
    udpSocket->close();
    bool result = udpSocket->bind(ipAddr, UPPM::ackPort);

    emit sgItfConnected(result);
}

void EthCore::setDstIp(QHostAddress ipAddr)
{
    m_dstAddress = ipAddr;
}

void EthCore::setDstPort(quint16 dstPort)
{
    m_dstPort = dstPort;
}

void EthCore::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();

        FrameHeader frameHeader;
        memcpy(frameHeader.rawData, datagram.data().data(), FRAME_HEADER_SIZE);

        if(frameHeader.structData.TK == UPPM_RAW_ACK_COMM_FRAME) emit sgAckRecieved();
    }
}
