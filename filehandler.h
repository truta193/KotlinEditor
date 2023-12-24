#pragma once

#include <QObject>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

class FileHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString output READ getOutput WRITE setOutput NOTIFY outputChanged)
    Q_PROPERTY(bool isBusy READ getIsBusy WRITE setIsBusy NOTIFY isBusyChanged)
    Q_PROPERTY(QString script READ getScript WRITE setScript NOTIFY scriptChanged)

private:
    QString fileName = QString("script.kts");
    QString filePath;
    QString m_script = "";
    QString m_output = "";
    bool m_isBusy = false;
    QFile *file;

public:
    explicit FileHandler(QObject *parent = nullptr);
    Q_INVOKABLE bool saveFile();

public slots:
    void setOutput(QString &text);
    QString getOutput();
    void appendOutput(QString text);

    void setIsBusy(bool busy);
    bool getIsBusy();

    void setScript(QString text);
    QString getScript();

signals:
    void outputChanged();
    void isBusyChanged();
    void scriptChanged();
    void inputChanged(QString text);
};

