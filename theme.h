#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QColor>

class Theme : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor background READ background CONSTANT)
    Q_PROPERTY(QColor currentLine READ currentLine CONSTANT)
    Q_PROPERTY(QColor foreground READ foreground CONSTANT)
    Q_PROPERTY(QColor comment READ comment CONSTANT)
    Q_PROPERTY(QColor cyan READ cyan CONSTANT)
    Q_PROPERTY(QColor green READ green CONSTANT)
    Q_PROPERTY(QColor orange READ orange CONSTANT)
    Q_PROPERTY(QColor pink READ pink CONSTANT)
    Q_PROPERTY(QColor purple READ purple CONSTANT)
    Q_PROPERTY(QColor red READ red CONSTANT)
    Q_PROPERTY(QColor yellow READ yellow CONSTANT)
public:
    explicit Theme(QObject *parent = nullptr);
    QColor background();
    QColor currentLine();
    QColor foreground();
    QColor comment();
    QColor cyan();
    QColor green();
    QColor orange();
    QColor pink();
    QColor purple();
    QColor red();
    QColor yellow();

private:
    QColor m_background;
    QColor m_currentLine;
    QColor m_foreground;
    QColor m_comment;
    QColor m_cyan;
    QColor m_green;
    QColor m_orange;
    QColor m_pink;
    QColor m_purple;
    QColor m_red;
    QColor m_yellow;
};

#endif // THEME_H
