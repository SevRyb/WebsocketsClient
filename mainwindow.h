
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <oclero/qlementine/widgets/FramelessWindow.hpp>
#include <oclero/qlementine/widgets/LineEdit.hpp>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

#include <QWebSocket>

using namespace oclero;

class MainWindow : public qlementine::FramelessWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnected();
    void onMessageReceived(QString text);
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
private:
    QWidget *m_rootWidget;
    QGridLayout *m_rootLay;
    qlementine::LineEdit *m_urlEdit;
    QPushButton *m_connectBtn;
    QPushButton *m_disconnectBtn;
    QPushButton *m_sendBtn;
    QTextEdit *m_dataToSendTextEdit;
    QTextEdit *m_responseTextEdit;

    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_isConnected;
};

#endif // MAINWINDOW_H
