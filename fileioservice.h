#pragma once

#include <QFile>

class FileIOService
{
private:
    QFile *currentFile;
public:
    FileIOService();
    bool saveFile(QString path, QString name);
};


