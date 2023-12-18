#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>
#include "highlighter.h"
#include "shhandler.h"
#include "theme.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SHHandler *handler = new SHHandler();
    Theme *theme = new Theme();

    qmlRegisterType<Highlighter>("Highlighter", 1, 0, "Highlighter");
    qmlRegisterType<Theme>("Theme", 1, 0, "Theme");

    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("shHandler", handler);
    rootContext->setContextProperty("theme", theme);

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
