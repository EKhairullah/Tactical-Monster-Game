#include "secondpage.h"
#include "ui_secondpage.h"
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QDebug>
#include "agentpage.h"
#include "propreties.h"


secondPage::secondPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::secondPage)
{
    ui->setupUi(this);
    this->startSecond();
}

void secondPage::startSecond()
{
    // Create central widget
    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // Main layout with some spacing
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(40, 40, 40, 40);  // Reduced margins
    mainLayout->setSpacing(20);

    // Background image label (now takes more space)
    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setAlignment(Qt::AlignCenter);
    QPixmap bg(":/images/secondpageImage.png");
    if (!bg.isNull()) {
        backgroundLabel->setPixmap(bg.scaled(
            600, 300,  // Adjusted size
            Qt::KeepAspectRatioByExpanding,
            Qt::SmoothTransformation
            ));
        qDebug() << "Successfully loaded background image";
    } else {
        backgroundLabel->setText("Background Image");
        qDebug() << "Failed to load background image";
    }
    mainLayout->addWidget(backgroundLabel);

    // Title label
    QLabel *titleLabel = new QLabel("Choose To Start", this);
    titleLabel->setStyleSheet(
        "QLabel {"
        "   color: #f8d347;"
        "   font-size: 36px;"
        "   font-weight: bold;"
        "   margin-bottom: 10px;"
        "}"
        );
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);

    // Button container (black background)
    QWidget *buttonContainer = new QWidget(this);
    buttonContainer->setStyleSheet(
        "QWidget {"
        "   background-color: rgba(0, 0, 0, 150);"
        "   border-radius: 10px;"
        "   padding: 15px;"
        "}"
        );

    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(10, 10, 10, 10);

    QPushButton *agentsButton = new QPushButton("Agents", this);
    styleButton(agentsButton);
    QPushButton *startButton = new QPushButton("Tap To Start", this);
    styleButton(startButton);

    buttonLayout->addWidget(agentsButton);
    buttonLayout->addWidget(startButton);

    mainLayout->addWidget(buttonContainer, 0, Qt::AlignHCenter);

    // Connect signals
    connect(agentsButton, &QPushButton::clicked, this, &secondPage::s_button_clicked);
    connect(startButton, &QPushButton::clicked, this, &secondPage::start_button_clicked);

    // Window styling
    this->setMinimumSize(600, 500);  // More compact size
    this->setStyleSheet(
        "QMainWindow {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1a1a2e, stop:1 #16213e);"
        "}"
        );
}

// Helper function to style buttons consistently
void secondPage::styleButton(QPushButton *button)
{
    button->setFixedSize(180, 50);  // Slightly smaller buttons
    button->setStyleSheet(
        "QPushButton {"
        "   color: white;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ff512f, stop:1 #dd2476);"
        "   border-radius: 8px;"
        "   padding: 5px 10px;"
        "   border: 1px solid #ffffff;"
        "}"
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #dd2476, stop:1 #ff512f);"
        "}"
        "QPushButton:pressed {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #cc1c66, stop:1 #ee4025);"
        "}"
        );

    // Add shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(221, 36, 118, 150));
    shadow->setOffset(0, 3);
    button->setGraphicsEffect(shadow);
}

// Slot for the new button
void secondPage::start_button_clicked()
{

    this->hide();
    Widget *w = new Widget(nullptr);
    w->resize(500,500);
    w->show();
}

secondPage::~secondPage()
{
    delete ui;
}

QSize secondPage::qsize()
{
    return QSize(800,700);
}

void secondPage::s_button_clicked()
{
    hide();
    agentPage * a = new agentPage(nullptr);
    a->setWindowTitle("Agent Window");
    a->resize(700,700);
    a->show();
}
