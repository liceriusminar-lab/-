#include "SnakeWidget.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QMessageBox>

SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget(parent),
    dir(Right),
    nextDir(Right),
    gameOver(false),
    score(0),
    cellSize(20)
{
    setFocusPolicy(Qt::StrongFocus);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SnakeWidget::gameTick);
    resetGame();
    timer->start(140);          // скорость — чем меньше число, тем быстрее
}
void SnakeWidget::resetGame()
{
    snake.clear();
    snake.append({10, 10});
    snake.append({9,  10});
    snake.append({8,  10});
    dir = Right;
    nextDir = Right;
    score = 0;
    gameOver = false;
    generateFood();
    update();
}
void SnakeWidget::generateFood()
{
    int cols = width()  / cellSize;
    int rows = height() / cellSize;
    do {
        food.setX(QRandomGenerator::global()->bounded(0, cols));
        food.setY(QRandomGenerator::global()->bounded(0, rows));
    } while (collidesWithSnake(food.x(), food.y()));
}
bool SnakeWidget::collidesWithSnake(int x, int y) const
{
    for (const auto &seg : snake)
        if (seg.x == x && seg.y == y)
            return true;
    return false;
}
void SnakeWidget::gameTick()
{
    if (gameOver) return;
    dir = nextDir;
    Segment head = snake.first();
    switch (dir) {
    case Up:    head.y--; break;
    case Down:  head.y++; break;
    case Left:  head.x--; break;
    case Right: head.x++; break;
    }
    //границы
    int cols = width()  / cellSize;
    int rows = height() / cellSize;
    if (head.x < 0 || head.x >= cols ||
        head.y < 0 || head.y >= rows ||
        collidesWithSnake(head.x, head.y))
    {
        gameOver = true;
        timer->stop();
        QMessageBox::information(this, "Игра окончена",
                                 QString("Счёт: %1\n\nНажми Ок\nдля новой игры").arg(score));
        resetGame();
        timer->start(140);
        return;
    }
    snake.prepend(head);
    // Съел
    if (head.x == food.x() && head.y == food.y())
    {
        score += 1;
        generateFood();
    }
    else
    {
        snake.removeLast();
    }
    update();
}
void SnakeWidget::keyPressEvent(QKeyEvent *event)
{
    if (gameOver) {
        resetGame();
        timer->start(140);
        return;
    }
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        if (dir != Down)  nextDir = Up;
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        if (dir != Up)    nextDir = Down;
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        if (dir != Right) nextDir = Left;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        if (dir != Left)  nextDir = Right;
        break;
    case Qt::Key_Escape:
        close();
        break;
    }
}
void SnakeWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    int w = width();
    int h = height();
    // Фон
    p.fillRect(0, 0, w, h, Qt::black);
    // Сетка
    p.setPen(QPen(QColor(40, 40, 40), 1));
    for (int x = 0; x <= w; x += cellSize)
        p.drawLine(x, 0, x, h);
    for (int y = 0; y <= h; y += cellSize)
        p.drawLine(0, y, w, y);
    // Еда
    p.setBrush(QColor(220, 30, 30));
    p.setPen(Qt::NoPen);
    p.drawEllipse(food.x() * cellSize + 3,
                  food.y() * cellSize + 3,
                  cellSize - 6, cellSize - 6);
    // Змей
    QColor pinkHead(255, 105, 180);
    QColor pinkBody(255, 182, 193);
    for (int i = 0; i < snake.size(); ++i)
    {
        int x = snake[i].x * cellSize;
        int y = snake[i].y * cellSize;
        if (i == 0) // голова
            p.setBrush(pinkHead);
        else
            p.setBrush(pinkBody);
        p.setPen(QPen(Qt::white, 2));
        p.drawRoundedRect(x + 2, y + 2, cellSize - 4, cellSize - 4, 8, 8);
    }
    // Счёт
    p.setPen(Qt::white);
    p.setFont(QFont("Arial", 14, QFont::Bold));
    p.drawText(10, 25, QString("Счёт: %1").arg(score));
}
