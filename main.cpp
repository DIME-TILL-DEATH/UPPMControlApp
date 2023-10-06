#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ethcore.h"
#include "ethgui.h"
#include "controlgui.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    EthCore ethCore;

    EthGui ethGui;
    ControlGui ctrlGui;

    EthCore::connect(&ethGui, &EthGui::sgSetHostIP, &ethCore, &EthCore::setHostAddress);
    EthCore::connect(&ethGui, &EthGui::sgSetDstIP, &ethCore, &EthCore::setDstIp);
    EthCore::connect(&ethGui, &EthGui::sgSetDstPort, &ethCore, &EthCore::setDstPort);

    EthCore::connect(&ethCore, &EthCore::sgItfConnected, &ethGui, &EthGui::slItfConnected);
    EthCore::connect(&ethCore, &EthCore::sgAckRecieved, &ctrlGui, &ControlGui::sgAckRecieved);

    ControlGui::connect(&ctrlGui, &ControlGui::sgSenRawCommFrame, &ethCore, &EthCore::senRawCommFrame);

    qmlRegisterSingletonInstance("CppObjects", 1, 0, "EthGui", &ethGui);
    qmlRegisterSingletonInstance("CppObjects", 1, 0, "CtrlGui", &ctrlGui);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/UPPMControlApp/qml/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
