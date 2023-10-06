#include "controlgui.h"

ControlGui::ControlGui(QObject *parent)
    : QObject{parent}
{

}

void ControlGui::setPhaseShifter(QList<quint8> cbValues)
{
    m_phaseCode =  cbValues.at(0) |
               cbValues.at(1) << 1 |
               cbValues.at(2) << 2 |
               cbValues.at(3) << 3 |
               cbValues.at(4) << 4 |
               cbValues.at(5) << 5 ;

    emit phaseCodeChanged();
}

void ControlGui::sendFrame()
{
    UPPM_Raw_Command_Frame frame{0};

    frame.filter = m_filterCode;
    frame.phaseShifter = m_phaseCode;

    emit sgSenRawCommFrame(frame);
}
