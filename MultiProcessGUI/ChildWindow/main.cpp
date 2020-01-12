#include <QApplication>
#include <QTextEdit>
#include <QLocalSocket>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QMessageBox>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QTextEdit editor("<h1>This is a test for multi-process gui, this edit control is in a child process.</h>");

    QCommandLineOption optUuid("uuid", "Set the uuid as the socket server name", "uuid");
    QCommandLineParser parser;
    parser.addOption(optUuid);
    parser.addHelpOption();
    parser.process(a);
    QString uuid = parser.value(optUuid);

    QLocalSocket *client = new QLocalSocket(&editor);
    QObject::connect(client, &QLocalSocket::connected, [client, &editor] {
        client->write(QByteArray::number(editor.winId()));
        client->waitForBytesWritten();
        QObject::connect(client, &QLocalSocket::readyRead, [client, &editor] {
            QByteArray ret = client->readAll();
            if (ret == "ok")
            {
                editor.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
                editor.show();
            }
        });
    });

    client->connectToServer(uuid);

    return a.exec();
}