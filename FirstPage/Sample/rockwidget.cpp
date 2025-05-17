#include "rockwidget.h"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QDebug>
#include <QPainter>
#include "secondpage.h"

    RockWidget::RockWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("Game Introduction");
    this->Start();
}

void RockWidget::Start()
{

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 20, 20, 40); // Add some margins

    // Create a container widget for better styling
    QWidget *mainContainer = new QWidget(this);
    mainContainer->setStyleSheet("background-color: rgba(0, 0, 0, 180); border-radius: 15px;");

    QVBoxLayout *containerLayout = new QVBoxLayout(mainContainer);
    containerLayout->setContentsMargins(20, 20, 20, 20);

    // Add drop shadow effect to the container
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setBlurRadius(30);
    shadowEffect->setColor(QColor(0, 0, 0, 160));
    shadowEffect->setOffset(5, 5);
    mainContainer->setGraphicsEffect(shadowEffect);

    // Create label with background image
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setFixedSize(600, 400); // Adjusted size
    QPixmap bg(":/Intro/Intro.jpg");
    if (!bg.isNull()) {
        // Apply rounded corners to the image
        QPixmap rounded(bg.size());
        rounded.fill(Qt::transparent);

        QPainter painter(&rounded);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(bg));
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rounded.rect(), 10, 10);

        imageLabel->setPixmap(rounded.scaled(
            imageLabel->size(),
            Qt::KeepAspectRatioByExpanding,
            Qt::SmoothTransformation
            ));
        imageLabel->setAlignment(Qt::AlignCenter);
    }

    // Game title label
    QLabel *titleLabel = new QLabel("ADVENTURE QUEST", this);
    titleLabel->setStyleSheet(
        "QLabel {"
        "   color: #f8d347;"
        "   font-size: 36px;"
        "   font-weight: bold;"
        "   margin-bottom: 20px;"
        "}"
        );

    // Add text shadow effect
    QGraphicsDropShadowEffect *textShadow = new QGraphicsDropShadowEffect;
    textShadow->setBlurRadius(10);
    textShadow->setColor(QColor(0, 0, 0, 200));
    textShadow->setOffset(3, 3);
    titleLabel->setGraphicsEffect(textShadow);

    // Description label
    QLabel *descLabel = new QLabel("Embark on an epic journey through mysterious lands\nand face challenges that will test your courage!", this);
    descLabel->setStyleSheet(
        "QLabel {"
        "   color: white;"
        "   font-size: 16px;"
        "   margin-bottom: 30px;"
        "}"
        );
    descLabel->setAlignment(Qt::AlignCenter);

    // Start button with hover effects
    QPushButton *button = new QPushButton("START GAME", this);
    button->setFixedSize(200, 60);
    button->setStyleSheet(
        "QPushButton {"
        "   color: white;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ff512f, stop:1 #dd2476);"
        "   border-radius: 10px;"
        "   padding: 10px 20px;"
        "   border: 2px solid #ffffff;"
        // "   margin 100 0 60 10;"
        "}"
        "QPushButton:hover {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #dd2476, stop:1 #ff512f);"
        "}"
        "QPushButton:pressed {"
        "   background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #cc1c66, stop:1 #ee4025);"
        "}"
        );
    button->move(250, 570);
    // Add button animation
    QGraphicsDropShadowEffect *buttonShadow = new QGraphicsDropShadowEffect;
    buttonShadow->setBlurRadius(15);
    buttonShadow->setColor(QColor(221, 36, 118, 150));
    buttonShadow->setOffset(0, 5);
    button->setGraphicsEffect(buttonShadow);

    // Pulse animation for the button
    QPropertyAnimation *pulseAnim = new QPropertyAnimation(button, "geometry");
    pulseAnim->setDuration(1000);
    pulseAnim->setLoopCount(-1); // Infinite loop
    pulseAnim->setKeyValueAt(0, button->geometry());
    pulseAnim->setKeyValueAt(0.5, button->geometry().adjusted(-5, -5, 5, 5));
    pulseAnim->setKeyValueAt(1, button->geometry());
    pulseAnim->start();

    connect(button, SIGNAL(clicked()), this, SLOT(button_clicked()));

    // Add widgets to container layout
    containerLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    containerLayout->addWidget(imageLabel, 0, Qt::AlignHCenter);
    containerLayout->addWidget(descLabel, 0, Qt::AlignHCenter);
    containerLayout->addWidget(button, 0, Qt::AlignHCenter);

    // Add container to main layout
    layout->addWidget(mainContainer);

    // Set a nice background for the main window
    this->setStyleSheet(
        "RockWidget {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1a1a2e, stop:1 #16213e);"
        "}"
        );
}

QSize RockWidget::qsize()
{
    return QSize(800, 700); // Adjusted window size
}

void RockWidget::button_clicked()
{
    // hide();
    // MainWindow w;
    // w.setWindowTitle("Second Page");
    // w.show();
    hide();
    secondPage* s = new secondPage(this);
    s->resize(750,700);
    s->show();
    qDebug() << "Game started!";
}
