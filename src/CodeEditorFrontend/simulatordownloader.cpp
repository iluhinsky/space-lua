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
    if ( file.open(QIODevice::WriteOnly) )
    {
        QTextStream stream( &file );
        stream << shipDeclaration;
    }
    file.close();
    QString shipScriptFilePath = QGuiApplication::applicationDirPath() +
            "/../../bin/resources/scripts/Ship1.lua";

    QFile file1( shipScriptFilePath );
    if ( file1.open(QIODevice::WriteOnly) )
    {
        QTextStream stream( &file1 );
        stream << shipScript;
    }
    file1.close();

    this->process.setWorkingDirectory(QGuiApplication::applicationDirPath() +
                                      '/../../bin/');
    this->process.start(QGuiApplication::applicationDirPath() + exePath);
}
