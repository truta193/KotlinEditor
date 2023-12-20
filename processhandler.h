#ifndef PROCESSHANDLER_H
#define PROCESSHANDLER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QQuickItem>
#include "filehandler.h"

class ProcessHandler : public QObject
{
    Q_OBJECT
public:
    explicit ProcessHandler(QObject *parent = nullptr, FileHandler *fileHandler = nullptr);
    ~ProcessHandler();
signals:
    void resultReady(const QString &result);
public slots:
    void runScript(QString cwd, QString script);

private slots:
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError error);
    void processOutputUpdate();

private:
    FileHandler *fileHandler;
    QProcess *process;
    QPointer<QQuickItem> outputPane;
};

#endif // PROCESSHANDLER_H
