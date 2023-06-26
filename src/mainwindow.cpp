
#include "mainwindow.h"

using namespace oclero;

MainWindow::MainWindow(QWidget *parent)
    : qlementine::FramelessWindow(parent)
    , m_isConnected(false)
    , m_baseWindowTitle("WebsocketsClient")
{
    setWindowTitle(m_baseWindowTitle);
    resize(500, 300);
    m_rootLay = new QGridLayout;
    m_rootWidget = new QWidget(this);
    m_rootWidget->setLayout(m_rootLay);
    setContentWidget(m_rootWidget);

    m_urlEdit = new qlementine::LineEdit(this);
    m_connectBtn = new QPushButton("Connect", this);
    m_disconnectBtn = new QPushButton("Disconnect", this);
    m_sendBtn = new QPushButton("Send", this);
    m_dataToSendTextEdit = new QPlainTextEdit(this);
    m_responseTextEdit = new QPlainTextEdit(this);

    m_rootLay->addWidget(m_urlEdit, 0, 0, 1, 3);
    m_rootLay->addWidget(m_connectBtn, 1, 0);
    m_rootLay->addWidget(m_disconnectBtn, 1, 1);
    m_rootLay->addWidget(m_sendBtn, 1, 2);
    m_rootLay->addWidget(m_dataToSendTextEdit, 2, 0, 1, 3);
    m_rootLay->addWidget(m_responseTextEdit, 3, 0, 1, 3);

    /**/
    m_urlEdit->setPlaceholderText("ws://");
    m_urlEdit->setClearButtonEnabled(true);
    m_disconnectBtn->setEnabled(false);
    m_sendBtn->setEnabled(false);
    m_dataToSendTextEdit->setPlaceholderText("Request");
    m_responseTextEdit->setPlaceholderText("Response");

    /* Connections */
    connect(&m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &MainWindow::onDisconnected);
    connect(&m_webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &MainWindow::onError);
    connect(m_connectBtn, &QPushButton::clicked, this, [this]()
            {
                QString url = m_urlEdit->text();
                if (url.mid(0, 2) == QString("ws"))
                    m_url = url;
                else
                    m_url = "ws://" + url;
                m_webSocket.open(m_url);
            });
    connect(m_disconnectBtn, &QPushButton::clicked, this, [this]()
            {
                m_webSocket.close();
            });
    connect(m_sendBtn, &QPushButton::clicked, this, [this]()
            {
                m_responseTextEdit->clear();
                QString text = m_dataToSendTextEdit->toPlainText();
                if (text.isEmpty())
                    return;
                m_webSocket.sendTextMessage(text);
            });
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_webSocket.close();
    qlementine::FramelessWindow::closeEvent(event);
}

void MainWindow::onConnected()
{
    m_isConnected = true;
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &MainWindow::onMessageReceived);
    m_urlEdit->setStatus(qlementine::Status::Success);
    m_disconnectBtn->setEnabled(true);
    m_sendBtn->setEnabled(true);
    setWindowTitle(m_baseWindowTitle + " [" + m_url.toDisplayString() + "]");
}

void MainWindow::onMessageReceived(QString text)
{
    m_responseTextEdit->setPlainText(text);
}

void MainWindow::onDisconnected()
{
    m_isConnected = false;
    m_urlEdit->setStatus(qlementine::Status::Default);
    m_disconnectBtn->setEnabled(false);
    m_sendBtn->setEnabled(false);
    setWindowTitle(m_baseWindowTitle);
}

void MainWindow::onError(QAbstractSocket::SocketError error)
{
    m_urlEdit->setStatus(qlementine::Status::Error);
    m_sendBtn->setEnabled(false);
}


