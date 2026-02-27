#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QVector>
#include <QPoint>

class SnakeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SnakeWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void gameTick();
private:
    enum Direction { Up, Down, Left, Right };
    struct Segment {
        int x, y;
    };
    QVector<Segment> snake;
    QPoint food;
    Direction dir;
    Direction nextDir;
    bool gameOver;
    int score;
    int cellSize;
    QTimer *timer;
    void resetGame();
    void generateFood();
    bool collidesWithSnake(int x, int y) const;
};
#endif // SNAKEWIDGET_H
