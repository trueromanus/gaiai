#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

int main(int argc, char *argv[])
{
    qputenv("QML_DISABLE_DISK_CACHE", "1"); // don't make cache on disk (because don't make sense)

    /*
QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
calculateHugeMandelbrot();              // lunch time...
QGuiApplication::restoreOverrideCursor();

 QPixmap cursor_pixmap = QPixmap(":cursor_default");
 QCursor cursor_default = QCursor(cursor_pixmap, 0, 0);
 setCursor(cursor_default);
*/

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.loadFromModule("gaiai", "Main");

    return app.exec();
}
