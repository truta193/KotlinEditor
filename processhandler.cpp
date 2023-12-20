#include "processhandler.h"
#include <QQmlContext>
#include <QQmlEngine>
ProcessHandler::ProcessHandler(QObject *parent, FileHandler *fileHandler)
    : QObject{parent}, process(new QProcess(this))
{
    //connect(process, &QProcess::finished, this, &ProcessHandler::processFinished);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &ProcessHandler::processFinished);
    connect(process, &QProcess::errorOccurred, this, &ProcessHandler::processError);
    connect(process, &QProcess::readyReadStandardOutput, this, &ProcessHandler::processOutputUpdate);
    this->fileHandler = fileHandler;
}

ProcessHandler::~ProcessHandler()
{
    process->kill();
}


void ProcessHandler::runScript(QString cwd, QString script)
{
    fileHandler->setIsBusy(true);
    QString temp = QString("");
    fileHandler->setOutput(temp);
    process->setWorkingDirectory(cwd);
    fileHandler->appendOutput("Running " + script + "\n");
    process->start("cmd", QStringList() << "/c" << "kotlinc -script " + script);
    process->waitForStarted();
}

void ProcessHandler::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitCode != 0 || exitStatus == QProcess::CrashExit) {
        fileHandler->appendOutput(process->readAllStandardError());
    }
    fileHandler->appendOutput("Process finished with exit code: " + QString::number(exitCode) + "\n");
    fileHandler->setIsBusy(false);
    // QString output = process->readAllStandardOutput();
    // fileHandler->appendOutput(output);
    //emit resultReady(output);
}

void ProcessHandler::processError(QProcess::ProcessError error)
{
    //fileHandler->appendOutput("\n" + process->errorString() + "\n");
    //emit resultReady("Error occurred: " + process->errorString());
}

void ProcessHandler::processOutputUpdate() {
    QString output = process->readAllStandardOutput();
    qInfo() << "updateeee";
    fileHandler->appendOutput(output);
}
