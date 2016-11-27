#ifndef PADDLE_H
#define PADDLE_H

class Ball;

class Paddle
{
private:
    float x;
    float y;
    int pred;
public:
    Paddle(float x, float y);

    static const int WIDTH;
    static const int HEIGHT;

    float getX();
    float getY();
    bool collided;
    void setPred(int pred);
    void setY(float y);
    void move(float dy);
    void AI(Ball* ball, float deltaTime);
    int predict(Ball* ball);
};

#endif // PADDLE_H
