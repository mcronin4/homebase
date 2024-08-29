#include "chatview.h"
#include "ui_chatview.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMap>
#include "map.h"
#include "browseview.h"
#include "mainsystem.h"
#include "loginview.h"
#include "datamanage.h"


ChatView::ChatView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatView)
{
    ui->setupUi(this);

    ui->messageArea->setReadOnly(true);

    // Connect signals to slots
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatView::onSendButtonClicked);
    connect(ui->conversationList, &QListWidget::itemClicked, this, &ChatView::onConversationSelected);
    connect(ui->addLandlordButton, &QPushButton::clicked, this, &ChatView::onAddLandlordClicked);
    connect(ui->logoutBtn,&QPushButton::clicked,this,&ChatView::openLoginWnd);
    connect(ui->closedBtn,&QPushButton::clicked,this,[this]{
        this->close();
    });
    // Assuming there's a button to open LoginView
    connect(ui->backButton_2, &QPushButton::clicked, this, &ChatView::backToMainSystem);
    connect(ui->backButton, &QPushButton::clicked, this, &ChatView::backToMainSystem);

    populateConversationList();
}

ChatView::~ChatView()
{
    delete ui;
}

void ChatView::onSendButtonClicked()
{
    QString message = ui->messageInput->text();
    QString receiver = "Receiver"; // Replace with the actual receiver's identifier
    QString sender = "Sender"; // Replace with the actual sender's identifier

    if (!message.isEmpty()) {
        DataManage::getInstance()->addChatMessage(sender, receiver, message);
        ui->messageArea->append("You: " + message);
        ui->messageInput->clear();
    }
}

void ChatView::populateConversationList()
{
    QStringList sampleNames = {"Alice", "Bob", "Charlie", "Diana", "Eve"};
    for (const QString &name : sampleNames) {
        ui->conversationList->addItem(name);
    }
}

void ChatView::onConversationSelected()
{
    QString selectedName = ui->conversationList->currentItem()->text();
    loadConversation(selectedName);
}

void ChatView::loadConversation(const QString &name)
{
    ui->messageArea->clear();

    // Sample conversations
    static const QMap<QString, QString> sampleConversations = {
        {"Alice", "Alice: Hi there!\nYou: Hello, Alice! How are you?"},
        {"Bob", "Bob: How's it going?\nYou: Pretty good, thanks! And you?"},
        {"Charlie", "Charlie: Did you see that game last night?\nYou: Yes, it was amazing!"},
        {"Diana", "Diana: Are you coming to the meeting tomorrow?\nYou: Certainly, I'll be there."},
        {"Eve", "Eve: Can you help me with this task?\nYou: Sure, what do you need?"}
    };

    QString conversation = sampleConversations.value(name, "No conversation history.");
    ui->messageArea->append(conversation);
}


void ChatView::onAddLandlordClicked()
{
    QString landlordName = ui->sampleNameInput->text().trimmed();
    if (!landlordName.isEmpty()) {
        ui->conversationList->addItem(landlordName);
        ui->messageArea->clear();
    }
    ui->sampleNameInput->clear();
}

void ChatView::backToMainSystem()
{

    MainSystem * mainSystemWnd = new MainSystem;
    mainSystemWnd->show();
    this->close();

}

void ChatView::openLoginWnd()
{
    LoginView* loginWnd = new LoginView;
    loginWnd->show();
    this->close();
}

void ChatView::openBrowseWnd()
{
    BrowseView* browseWnd = new BrowseView;
    browseWnd->show();
    this->close();
}


void ChatView::openMapWnd()
{
    Map* mapWnd = new Map;
    mapWnd->setAttribute(Qt::WA_DeleteOnClose);
    mapWnd->show();
    this->close();

}
