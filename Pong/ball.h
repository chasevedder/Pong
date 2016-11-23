#ifndef BALL_H
#define BALL_H

class Paddle;

class Ball
{
private:
    int x;
    int y;
    int speed;
    int numHits;
    int angle;
public:
    Ball(int x, int y);

    static const int SIZE;

    int getX();
    int getY();
    int getSize();
    int getSpeed();

    void move();
    void launch();
    void updateSpeed();
    bool collidesWithWall();
    bool collidesWithPaddle(Paddle* paddle);
    void bounce();
};

#endif // BALL_H
