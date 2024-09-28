#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include "sys_mg/cm_mg.h"
#include "QsLog/include/QsLog.h"

#define VERSION "软件版本2.22"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //w.setWindowTitle(QString(VERSION) + "从机IP:" +SLAVE_IP);
    w.setWindowTitle(QString(VERSION) + " room-1 IP(" +SLAVE_IP + ") " + " room-2 IP(" +SLAVE_IP_2 + ")");

    w.show();


    //abort();

    using namespace QsLogging;
    // 1. init the logging mechanism
    Logger& logger = Logger::instance();
    //logger.setLoggingLevel(QsLogging::TraceLevel);
    logger.setLoggingLevel(QsLogging::DebugLevel);
    //const QString sLogPath(QDir(a.applicationDirPath()).filePath("log.txt"));//文件路径
    const QString sLogPath(QDir(a.applicationDirPath()).filePath("./log_doc/log.txt"));
    // 2. add two destinations  //文件最大限制100M
    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
                                    sLogPath, EnableLogRotation, MaxSizeBytes(0x6400000), MaxOldLogCount(2)));
    //DestinationPtr debugDestination(DestinationFactory::MakeDebugOutputDestination());
    DestinationPtr objectDestination(DestinationFactory::MakeFunctorDestination(&w, SLOT(onm_write_inf(QString))));
    logger.addDestination(objectDestination);
    //DestinationPtr functorDestination(DestinationFactory::MakeFunctorDestination(&logFunction));
    //logger.addDestination(debugDestination);
    logger.addDestination(fileDestination);
    //logger.addDestination(objectDestination);

    return a.exec();
}
