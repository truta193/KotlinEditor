#include "filehandler.h"

FileHandler::FileHandler(QObject *parent)
    : QObject{parent}
{
    QString folder = QStandardPaths::locate(QStandardPaths::TempLocation, "KotlinEditor", QStandardPaths::LocateDirectory);
    if (folder.isEmpty()) {
        QDir tempDir = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
        tempDir.mkdir(QString("KotlinEditor"));
    }

    filePath = QStandardPaths::locate(QStandardPaths::TempLocation, "KotlinEditor", QStandardPaths::LocateDirectory);
    QDir tempDir = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
    tempDir.cd(QString("KotlinEditor"));
    file = new QFile(tempDir.filePath(fileName));
    qInfo() << filePath;
}

bool FileHandler::saveFile(QString &text) {
    file->resize(0);
    file->open(QIODeviceBase::ReadWrite);
    int err = file->write(text.toUtf8());
    file->close();
    if (err == -1) {
        return false;
    }
    return true;
}

bool FileHandler::saveFile() {
    file->resize(0);
    file->open(QIODeviceBase::ReadWrite);
    int err = file->write(script.toUtf8());
    file->close();
    if (err == -1) {
        return false;
    }
    return true;
}

void FileHandler::setScript(QString text) {
    this->script = text;
    qInfo() << text;
}
