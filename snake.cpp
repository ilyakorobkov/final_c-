#include "snake.h"
#include <QPainter>
#include <QTime>

Snake::Snake(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: black;");
    setWindowTitle("Snake");
    resize(400, 400);
    loadImages();
    initGame();
}

Snake::~Snake() {
}

void Snake::loadImages() {
    dot.load("images/dot.png");
    head.load("images/head.png");
    apple.load("images/apple.png");
}

void Snake::initGame() {
    snake.clear();
    snake.append(QPointF(50, 50));
    snake.append(QPointF(40, 50));
    snake.append(QPointF(30, 50));

    movementTransform.reset();
    movementTransform.translate(10, 0);

    locateApple();

    inGame = true;
    timerId = startTimer(140);
}

void Snake::locateApple() {
    int randX = (rand() % 40) * 10;
    int randY = (rand() % 40) * 10;
    applePosition = QPointF(randX, randY);
}

void Snake::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter qp(this);

    if (inGame) {
        qp.drawImage(applePosition, apple);

        for (int i = 0; i < snake.size(); ++i) {
            if (i == 0)
                qp.drawImage(snake[i], head);
            else
                qp.drawImage(snake[i], dot);
        }
    } else {
        gameOver();
    }
}

void Snake::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);

    if (inGame) {
        checkCollision();
        move();
        repaint();
    }
}

void Snake::keyPressEvent(QKeyEvent *event) {
    int key = event->key();

    QTransform rotationTransform;
    switch (key) {
        case Qt::Key_Left:
            rotationTransform.rotate(-90);
            movementTransform = rotationTransform * movementTransform;
            break;
        case Qt::Key_Right:
            rotationTransform.rotate(90);
            movementTransform = rotationTransform * movementTransform;
            break;
        case Qt::Key_Up:
            rotationTransform.rotate(0);
            movementTransform = rotationTransform * movementTransform;
            break;
        case Qt::Key_Down:
            rotationTransform.rotate(180);
            movementTransform = rotationTransform * movementTransform;
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void Snake::move() {
    QPointF headPos = snake[0] + movementTransform.map(QPointF(1, 0));
    snake.insert(0, headPos);
    if (headPos == applePosition) {
        locateApple();
    } else {
        snake.pop_back();
    }
}

void Snake::checkCollision() {
    QPointF headPos = snake[0];

    if (headPos.x() < 0 || headPos.x() >= 400 || headPos.y() < 0 || headPos.y() >= 400) {
        inGame = false;
    }

    for (int i = 1; i < snake.size(); ++i) {
        if (headPos == snake[i]) {
            inGame = false;
        }
    }

    if (!inGame) {
        killTimer(timerId);
    }
}

void Snake::gameOver() {
    QMessageBox msgBox;
    msgBox.setText("Game Over");
    msgBox.exec();
}
