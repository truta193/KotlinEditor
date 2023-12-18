#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

class FileHandler : public QObject
{
    Q_OBJECT
private:
    QString fileName = QString("script.kts");
    QString filePath;
    QString script;
    QFile *file;
public:
    explicit FileHandler(QObject *parent = nullptr);
    bool saveFile(QString& text);
public slots:
    Q_INVOKABLE bool saveFile();
    Q_INVOKABLE void setScript(QString text);

};

#endif // FILEHANDLER_H
