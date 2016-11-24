#ifndef BALL_H
#define BALL_H

class Paddle;

class Ball
{
private:
    float x;
    float y;
    int prevX;
    int prevY;
    int speed;
    int numHits;
    float xSpeed;
    float ySpeed;
public:
    Ball(int x, int y);

    static const int SIZE;

    float getX();
    float getY();
    int getSize();
    float getXSpeed();
    float getYSpeed();

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
