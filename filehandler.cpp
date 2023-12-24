#include "filehandler.h"
#include <processhandler.h>
FileHandler::FileHandler(QObject *parent)
    : QObject{parent}
{
    QString folder = QStandardPaths::locate(QStandardPaths::TempLocation, "KotlinEditor", QStandardPaths::LocateDirectory);
    if (folder.isEmpty())
    {
        QDir tempDir = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
        tempDir.mkdir(QString("KotlinEditor"));
    }

    filePath = QStandardPaths::locate(QStandardPaths::TempLocation, "KotlinEditor", QStandardPaths::LocateDirectory);
    QDir tempDir = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
    tempDir.cd(QString("KotlinEditor"));
    file = new QFile(tempDir.filePath(fileName));
    qInfo() << filePath;
}

bool FileHandler::saveFile()
{
    file->resize(0);
    file->open(QIODeviceBase::ReadWrite);
    int err = file->write(m_script.toUtf8());
    file->close();
    if (err == -1)
    {
        return false;
    }
    ProcessHandler *ph = new ProcessHandler(nullptr, this);
    ph->runScript(filePath, filePath + "/" + fileName);
    return true;
}

void FileHandler::setOutput(QString &text)
{
    m_output = text;
    emit outputChanged();

}

QString FileHandler::getOutput()
{
    return m_output;
}

void FileHandler::appendOutput(QString text)
{
    m_output += text;
    emit outputChanged();
}

bool FileHandler::getIsBusy()
{
    return m_isBusy;
}

void FileHandler::setIsBusy(bool busy)
{
    if (busy != m_isBusy)
    {
        m_isBusy = busy;
        emit isBusyChanged();
    }
}

QString FileHandler::getScript()
{
    return this->m_script;
}

void FileHandler::setScript(QString text)
{
    if (m_script != text)
    {
        this->m_script = text;
        emit scriptChanged();
    }
}
