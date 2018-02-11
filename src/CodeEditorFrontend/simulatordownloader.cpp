#include "simulatordownloader.h"
#include <QGuiApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

SimulatorDownloader::SimulatorDownloader(QObject *parent) : QObject(parent)
{

}
void SimulatorDownloader::startSimulator(QString exePath, QString shipDeclaration,
                                         QString shipScript){
    QString shipDeclarationFilePath = QGuiApplication::applicationDirPath() +
            "/../../bin/resources/construction/Ship1.txt";
    QFile file( shipDeclarationFilePath );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << shipDeclaration;
    }
    file.close();
    QString shipScriptFilePath = QGuiApplication::applicationDirPath() +
            "/../../bin/resources/scripts/Ship1.lua";

    QFile file( shipScriptFilePath );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << shipScript;
    }
    file.close();

    this->process.start(QGuiApplication::applicationDirPath() + exePath);
}
