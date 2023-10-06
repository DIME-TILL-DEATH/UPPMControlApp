#ifndef CONTROLGUI_H
#define CONTROLGUI_H

#include <QObject>
#include <QDebug>

#include "uppm.h"

class ControlGui : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 phaseCode READ phaseCode WRITE setPhaseCode NOTIFY phaseCodeChanged FINAL)
    Q_PROPERTY(quint8 filterCode READ filterCode WRITE setFilterCode NOTIFY filterCodeChanged FINAL)
public:
    explicit ControlGui(QObject *parent = nullptr);

    Q_INVOKABLE void setPhaseShifter(QList<quint8> cbValues);

    Q_INVOKABLE void sendFrame();

    quint8 phaseCode() {return m_phaseCode;}
    quint8 filterCode() {return m_filterCode;}
    void setPhaseCode(quint8 phaseCode) {m_phaseCode = phaseCode;}
    void setFilterCode(quint8 filterCode) {m_filterCode = filterCode;}


signals:
    void phaseCodeChanged();
    void filterCodeChanged();

    void sgSenRawCommFrame(UPPM_Raw_Command_Frame frameData);
    void sgAckRecieved();

private:
    quint8 m_phaseCode{0};
    quint8 m_filterCode{0};
};

#endif // CONTROLGUI_H
