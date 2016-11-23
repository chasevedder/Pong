#ifndef PADDLE_H
#define PADDLE_H

class Ball;

class Paddle
{
private:
    int x;
    int y;
    int pred;
public:
    Paddle(int x, int y);

    static const int WIDTH;
    static const int HEIGHT;

    int getX();
    int getY();
    bool collided;
    void setPred(int pred);
    void setY(int y);
    void move(int dy);
    void AI(Ball* ball);
    int predict(Ball* ball);
};

#endif // PADDLE_H
