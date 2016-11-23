#ifndef BALL_H
#define BALL_H

class Paddle;

class Ball
{
private:
    int x;
    int y;
    int prevX;
    int prevY;
    int speed;
    int numHits;
    int xSpeed;
    int ySpeed;
public:
    Ball(int x, int y);

    static const int SIZE;

    int getX();
    int getY();
    int getSize();
    int getXSpeed();
    int getYSpeed();

    void move();
    void launch();
    void reset();
    bool collidesWithWall();
    bool collidesWithPaddle(Paddle* paddle);
    void bounce(Paddle* paddle);
    void bounce();
    float slope();
};

#endif // BALL_H
