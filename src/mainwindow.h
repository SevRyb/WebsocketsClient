
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <oclero/qlementine/widgets/FramelessWindow.hpp>
#include <oclero/qlementine/widgets/LineEdit.hpp>
#include <oclero/qlementine/widgets/Switch.hpp>
#include <QGridLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>

#include <QWebSocket>

using namespace oclero;

class MainWindow : public qlementine::FramelessWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void onConnected();
    void onMessageReceived(QString text);
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);
private:
    QWidget *m_rootWidget;
    QGridLayout *m_rootLay;
    qlementine::LineEdit *m_urlEdit;
    qlementine::Switch *m_autoclearSwitch;
    QPushButton *m_connectBtn;
    QPushButton *m_disconnectBtn;
    QPushButton *m_sendBtn;
    QPlainTextEdit *m_dataToSendTextEdit;
    QPlainTextEdit *m_responseTextEdit;

    QString m_baseWindowTitle;

    QWebSocket m_webSocket;
    QUrl m_url;
};

#endif // MAINWINDOW_H
