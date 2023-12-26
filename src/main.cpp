#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "include/cursorhandler.h"
#include "include/filehandler.h"
#include "include/highlighter.h"
#include "include/processhandler.h"
#include "include/syntaxhandler.h"
#include "include/theme.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SyntaxHandler *syntaxHandler = new SyntaxHandler();
    Theme *theme = new Theme();
    FileHandler *fileHandler = new FileHandler();
    ProcessHandler *processHandler = new ProcessHandler();
    CursorHandler *cursorHandler = new CursorHandler();

    qmlRegisterType<Highlighter>("Highlighter", 1, 0, "Highlighter");
    qmlRegisterType<Theme>("Theme", 1, 0, "Theme");
    qmlRegisterType<FileHandler>("FileHandler", 1, 0, "FileHandler");
    qmlRegisterType<ProcessHandler>("ProcessHandler", 1, 0, "ProcessHandler");
    qmlRegisterType<CursorHandler>("CursorHandler", 1, 0, "CursorHandler");

    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("syntaxHandler", syntaxHandler);
    rootContext->setContextProperty("theme", theme);
    rootContext->setContextProperty("fileHandler", fileHandler);
    rootContext->setContextProperty("cursorHandler", cursorHandler);
    rootContext->setContextProperty("processHandler", processHandler);

    const QUrl url(u"qrc:/KotlinEditor/App.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);


    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-Regular.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-Bold.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-BoldItalic.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-ExtraBold.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-ExtraBoldItalic.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-ExtraLight.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-ExtraLightItalic.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-Italic.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-Light.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-LightItalic.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-Medium.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-MediumItalic.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-SemiBold.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-SemiBoldItalic.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-Thin.ttf"));
    QFontDatabase::addApplicationFont(QString(":/fonts/assets/JetBrainsMono-ThinItalic.ttf"));
    return app.exec();
}
