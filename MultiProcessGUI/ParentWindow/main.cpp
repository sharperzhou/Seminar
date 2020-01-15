#include <QApplication>
#include <QWidget>
#include <QLocalSocket>
#include <QLocalServer>
#include <QProcess>
#include <QUuid>
#include <QWindow>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDir>
#include <QIODevice>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    w.show();

    QString uuid = QUuid::createUuid().toString();

    QLocalServer *server = new QLocalServer(&w);
    QObject::connect(server, &QLocalServer::newConnection, [server, &w] {
        QLocalSocket *client = server->nextPendingConnection();
        QObject::connect(client, &QLocalSocket::readyRead, [client, &w] {
            auto winId = client->readAll().toULongLong();
            QWindow *externWindow = QWindow::fromWinId(winId);
            QWidget *widget = QWidget::createWindowContainer(externWindow);
            QVBoxLayout *layout = new QVBoxLayout(&w);
            layout->addWidget(widget);
            w.setLayout(layout);

            QByteArray block;
            QDataStream stream(&block, QIODevice::WriteOnly);
            stream.setVersion(QDataStream::Qt_5_12);
            stream << QStringList{"This is the first line.",
                                  "The second line, yes, it's ok.",
                                  "Haha, what is a pretty way in today."};
            stream.device()->seek(0);
            client->write(block);
            if (client->waitForBytesWritten())
                w.update();
        });
    });
    server->listen(uuid);

    QProcess *process = new QProcess(&w);
    QString program = QApplication::applicationDirPath() + QDir::separator() + "child";

#ifdef Q_OS_WIN32
    program += ".exe";
#endif

    process->start(program, {"--uuid", uuid});

    return a.exec();
}
