#ifndef SIMULATORDOWNLOADER_H
#define SIMULATORDOWNLOADER_H

#include <QObject>
#include <QProcess>

class SimulatorDownloader : public QObject
{
    Q_OBJECT
public:
    explicit SimulatorDownloader(QObject *parent = 0);

private:
    QProcess process;

public:
    Q_INVOKABLE void startSimulator(QString exePath, QString shipDeclaration,
                                    QString shipScript);

signals:

public slots:
};

#endif // SIMULATORDOWNLOADER_H
