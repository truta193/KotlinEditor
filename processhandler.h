#pragma once

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QQuickItem>
#include "filehandler.h"

class ProcessHandler : public QObject
{
    Q_OBJECT

private:
    FileHandler *fileHandler;
    QProcess *process;
    QPointer<QQuickItem> outputPane;

public:
    explicit ProcessHandler(QObject *parent = nullptr, FileHandler *fileHandler = nullptr);
    ~ProcessHandler();

public slots:
    void runScript(QString cwd, QString script);

private slots:
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError error);
    void processOutputUpdate();
};