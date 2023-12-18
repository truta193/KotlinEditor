#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QFile>

class FileHandler : public QObject
{
    Q_OBJECT
private:

public:
    explicit FileHandler(QObject *parent = nullptr);

};

#endif // FILEHANDLER_H
