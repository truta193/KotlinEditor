#ifndef CURSORHANDLER_H
#define CURSORHANDLER_H

#include <QObject>

class CursorHandler : public QObject
{
    Q_OBJECT
public:
    explicit CursorHandler(QObject *parent = nullptr);

signals:
};

#endif // CURSORHANDLER_H
