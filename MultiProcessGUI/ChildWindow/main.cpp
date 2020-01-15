#include <QApplication>
#include <QTextEdit>
#include <QLocalSocket>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    QTextEdit editor("<h1>This is a test for multi-process gui, this edit control is in a child process.</h>");

    QCommandLineOption optUuid("uuid", "Set the uuid as the socket server name", "uuid");
    QCommandLineParser parser;
    parser.addOption(optUuid);
    parser.process(a);

    // Async processing
    // QLocalSocket *client = new QLocalSocket(&editor);
    // QObject::connect(client, &QLocalSocket::connected, [client, &editor] {
    //     client->write(QByteArray::number(editor.winId()));
    //     client->waitForBytesWritten();
    //     QObject::connect(client, &QLocalSocket::readyRead, [client, &editor] {
    //         QByteArray ret = client->readAll();
    //         if (ret == "ok")
    //         {
    //             editor.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    //             editor.show();
    //         }
    //     });
    // });
    // client->connectToServer(uuid);

    // Synchronize processing
    do
    {
        if (!parser.isSet(optUuid))
        {
            qDebug() << "no server to connect.";
            break;
        }

        QString uuid = parser.value(optUuid);

        QLocalSocket *client = new QLocalSocket(&editor);
        client->connectToServer(uuid);
        if (!client->waitForConnected())
        {
            qDebug() << "connect to server timeout, server:" << uuid;
            QMessageBox::information(nullptr, "", "connect to server timeout, server: " + uuid);
            break;
        }
        client->write(QByteArray::number(editor.winId()));
        if (!client->waitForBytesWritten())
        {
            qDebug() << "write winId to socket timeout.";
            QMessageBox::information(nullptr, "", "write winId to socket timeout.");
            break;
        }
        editor.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
        
        QObject::connect(client, &QLocalSocket::readyRead, [client, &editor]
        {
            QDataStream stream(client);
            stream.setVersion(QDataStream::Qt_5_12);
            QStringList lines;
            stream >> lines;
            for (const auto& line : lines)
                editor.append(line);
        });

    } while (false);

    editor.show();

    return a.exec();
}