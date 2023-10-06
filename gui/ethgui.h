#ifndef ETHGUI_H
#define ETHGUI_H

#include <QObject>
#include <QNetworkInterface>

class EthGui : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList itfList READ itfList NOTIFY itfListChanged FINAL)
public:
    explicit EthGui(QObject *parent = nullptr);

    QStringList itfList();

    Q_INVOKABLE void selectItf(QString itfName);
    Q_INVOKABLE bool setDstIp(QString ip);
    Q_INVOKABLE void setDstPort(quint16 port);

signals:
    void itfListChanged();

    void sgSetHostIP(QHostAddress addr);
    void sgSetDstIP(QHostAddress addr);
    void sgSetDstPort(quint16 port);

    void sgErrorMsg(QString msg);
    void sgConnectionOpened();

public slots:
    void slItfConnected(bool result);

private:
    QMap<QString, QHostAddress> m_itfList;
};

#endif // ETHGUI_H
