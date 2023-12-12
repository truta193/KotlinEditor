#include "fileioservice.h"
#include <QStandardPaths>
#include <QTextStream>
FileIOService::FileIOService() {
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    currentFile = new QFile(filePath + "current.kt");
}

bool FileIOService::saveFile(QString path, QString name) {
    currentFile->close();
    bool res = QFile::copy(currentFile->fileName(), name + "/" + path);
    currentFile->open(QIODevice::ReadWrite);
    return res;
}
