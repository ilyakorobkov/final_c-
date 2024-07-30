#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QImage>
#include <QVector>
#include <QPointF>
#include <QTransform>

class Snake : public QWidget {
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);
    ~Snake();

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void loadImages();
    void initGame();
    void locateApple();
    void move();
    void checkCollision();
    void gameOver();

    QImage dot;
    QImage head;
    QImage apple;
    QVector<QPointF> snake;
    QPointF applePosition;
    QTransform movementTransform;
    int timerId;
    bool inGame;
};

#endif // SNAKE_H
