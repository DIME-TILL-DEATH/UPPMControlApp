#ifndef UPPM_H
#define UPPM_H

#include <stdint.h>
#include <QHostAddress>

#include "uppm_raw_comm_frame.h"

class UPPM
{
public:
    UPPM();

    static constexpr uint16_t controlPort = 40003;                                       //destination ports
    static constexpr uint16_t fdkPort = 40002;                                        //source port
    static constexpr uint16_t ackPort = 40005;

    QHostAddress ipAddr() const;

    static QByteArray formRawCommFrame(UPPM_Raw_Command_Frame& data);

    void setIpAddr(const QHostAddress &newIpAddr);

private:
    QHostAddress m_ipAddr;
};

#endif // UPPM_H
