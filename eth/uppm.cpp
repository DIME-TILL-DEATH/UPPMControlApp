#include "uppm.h"

#include <QtEndian>

UPPM::UPPM()
{
    m_ipAddr.setAddress("10.0.0.151");
}

QHostAddress UPPM::ipAddr() const
{
    return m_ipAddr;
}

QByteArray UPPM::formRawCommFrame(UPPM_Raw_Command_Frame &data)
{
    QByteArray rawFrame;

    FrameHeader frameHeader{0};
//    memset(frameHeader.rawData, 0, FRAME_HEADER_SIZE);

    uint16_t outDataLen = 80;

    frameHeader.structData.signature = qToBigEndian<quint16>(FRAME_SIGNATURE);
    frameHeader.structData.RTK = 0;
    frameHeader.structData.TK = UPPM_RAW_COMMAND_FRAME;
    frameHeader.structData.RK = qToBigEndian(outDataLen);
    frameHeader.structData.RF128 = qToBigEndian(outDataLen/16);
    frameHeader.structData.PF = 1;
    frameHeader.structData.SCH = 0;
    frameHeader.structData.NF = 0;

    rawFrame.append((const char*)&(frameHeader.rawData[0]), FRAME_HEADER_SIZE);

    DatagramHeader datagramHeader{0};
//    memset(datagramHeader.rawData, 0, DATAGRAM_HEADER_SIZE);

    datagramHeader.structData.LAYOUT = 4;
    datagramHeader.structData.LAYOUT_SIZE128 = 3;
    datagramHeader.structData.RTK = 0;
    datagramHeader.structData.TK = UPPM_RAW_COMMAND_FRAME;
    datagramHeader.structData.RK = qToBigEndian(outDataLen - FRAME_HEADER_SIZE);

    datagramHeader.structData.CTRL_OFFSET128 = qToBigEndian(UPPM_RAW_COMM_FRAME_CTRL_OFFSET128);
    datagramHeader.structData.CTRL_SIZE128 = qToBigEndian(UPPM_RAW_COMM_FRAME_CTRL_SIZE128);
    datagramHeader.structData.SYNC_OFFSET128 = qToBigEndian(UPPM_RAW_COMM_FRAME_SYNC_OFFSET128);
    datagramHeader.structData.SYNC_SIZE128 = qToBigEndian(UPPM_RAW_COMM_FRAME_SYNC_SIZE128);;
    datagramHeader.structData.HEAD_AUX_OFFSET128 = qToBigEndian(UPPM_RAW_COMM_FRAME_AUX_DATA_OFFSET128);
    datagramHeader.structData.HEAD_AUX_SIZE128 = qToBigEndian(UPPM_RAW_COMM_FRAME_AUX_DATA_SIZE128);
    datagramHeader.structData.SIGNAL_OFFSET128 = qToBigEndian(UPPM_RAW_COMM_FRAME_SIGNAL_OFFSET128);
    datagramHeader.structData.SIGNAL_SIZE128 =  qToBigEndian(UPPM_RAW_COMM_FRAME_SIGNAL_SIZE128);

    rawFrame.append((const char*)&(datagramHeader.rawData[0]), DATAGRAM_HEADER_SIZE);

    UPPM_Raw_Command_Frame_union unionFrame;

    unionFrame.structData = data;

    rawFrame.append((const char*)&(unionFrame.rawData[0]), UPPM_RAW_COMM_FRAME_SIZE);

    return rawFrame;
}

void UPPM::setIpAddr(const QHostAddress &newIpAddr)
{
    m_ipAddr = newIpAddr;
}
