#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class ChatView;
}

class ChatView : public QWidget
{
    Q_OBJECT

public:
    explicit ChatView(QWidget *parent = nullptr);
    ~ChatView();

private slots:
    void onSendButtonClicked();
    void onConversationSelected();
    void onAddLandlordClicked();  // New slot for adding landlord
    void backToMainSystem(); // Slot to handle the button click


private:
    Ui::ChatView *ui;
    QListWidget* conversationList;
    QTextEdit* messageArea;
    QLineEdit* messageInput;
    QPushButton* sendButton;
    QLineEdit* sampleNameInput;
    QPushButton* addLandlordButton; // New button for adding landlord

    void loadConversation(const QString &name); // Declare the method here
    void populateConversationList();
    void loadSampleConversation(const QString &name);

public slots:
    void openLoginWnd();
    void openBrowseWnd();
    void openMapWnd();
};

#endif // CHATVIEW_H
