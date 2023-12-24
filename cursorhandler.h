#pragma once
#include <QObject>
#include <QQuickItem>

class CursorHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int position READ getPosition WRITE setPosition NOTIFY positionChanged)
private:
    QPointer<QQuickItem> inputPane = nullptr;
    QPointer<QQuickItem> outputPane = nullptr;
    int m_position = 0;
public:
    explicit CursorHandler(QObject *parent = nullptr);
    Q_INVOKABLE void setInput(QQuickItem* inputPane);
    Q_INVOKABLE void setOutput(QQuickItem* outputPane);
    bool validClick();
    void moveCursor();

public slots:
    int getPosition();
    void setPosition(int pos);

private slots:
    void onPositionChanged();

signals:
    void positionChanged();
};

