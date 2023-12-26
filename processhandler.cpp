#include "processhandler.h"
#include <QQmlContext>
#include <QQmlEngine>
ProcessHandler::ProcessHandler(QObject *parent, FileHandler *fileHandler)
    : QObject{parent}, process(new QProcess(this))
{
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &ProcessHandler::processFinished);
    connect(process, &QProcess::errorOccurred, this, &ProcessHandler::processError);
    connect(process, &QProcess::readyReadStandardOutput, this, &ProcessHandler::processOutputUpdate);
    this->fileHandler = fileHandler;
    connect(fileHandler, &FileHandler::inputChanged, this, &ProcessHandler::writeOut);
    connect(this, &ProcessHandler::processDone, fileHandler, &FileHandler::terminateProcess);
    connect(fileHandler, &FileHandler::terminate, this, &ProcessHandler::terminateEarly);
}

ProcessHandler::~ProcessHandler()
{
    process->closeWriteChannel();
    process->kill();
    fileHandler->setIsBusy(false);
    disconnect(fileHandler, &FileHandler::inputChanged, this, &ProcessHandler::writeOut);
}


void ProcessHandler::runScript(QString cwd, QString script)
{
    fileHandler->setIsBusy(true);
    QString temp = QString("");
    fileHandler->setOutput(temp);
    process->setWorkingDirectory(cwd);
    fileHandler->appendOutput("Running " + script + "\n");
    process->start("cmd", QStringList() << "/c" << "kotlinc -script " + script);
    process->waitForStarted(5000);
}

void ProcessHandler::writeOut(QString text) {
    process->write(text.toUtf8());
    fileHandler->appendOutput(text);
}

void ProcessHandler::terminateEarly()
{
    fileHandler->appendOutput("Process terminated by user!\n");
    emit processDone(this);
}

void ProcessHandler::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitCode != 0 || exitStatus == QProcess::CrashExit)
    {
        fileHandler->appendOutput(process->readAllStandardError());
    }
    fileHandler->appendOutput("Process finished with exit code: " + QString::number(exitCode) + "\n");

    emit processDone(this);
}

void ProcessHandler::processError(QProcess::ProcessError error)
{
    fileHandler->appendOutput("A process error occured: " + process->errorString() + "\n");
    emit processDone(this);
}

void ProcessHandler::processOutputUpdate()
{
    QString output = process->readAllStandardOutput();
    fileHandler->appendOutput(output);
}
