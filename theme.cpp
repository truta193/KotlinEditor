#include "theme.h"

Theme::Theme(QObject *parent)
    : QObject{parent}
{
    m_background= QColor("#282A36");
    m_currentLine = QColor("#44475A");
    m_foreground= QColor("#F8F8F2");
    m_comment= QColor("#6272A4");
    m_cyan= QColor("#8BE9FD");
    m_green= QColor("#50FA7B");
    m_orange= QColor("#FFB86C");
    m_pink= QColor("#FF79C6");
    m_purple= QColor("#BD93F9");
    m_red= QColor("#FF5555");
    m_yellow= QColor("#F1FA8C");
}
QColor Theme::background() { return m_background; }
QColor Theme::currentLine() { return m_currentLine; }
QColor Theme::foreground() { return m_foreground; }
QColor Theme::comment()  { return m_comment; }
QColor Theme::cyan() { return m_cyan; }
QColor Theme::green()  { return m_green; }
QColor Theme::orange()  { return m_orange; }
QColor Theme::pink() { return m_pink; }
QColor Theme::purple()  { return m_purple; }
QColor Theme::red() { return m_red; }
QColor Theme::yellow() { return m_yellow; }
