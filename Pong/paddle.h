#ifndef PADDLE_H
#define PADDLE_H


class Paddle
{
private:
    int x;
    int y;
public:
    Paddle(int x, int y);

    static const int WIDTH;
    static const int HEIGHT;

    int getX();
    int getY();

    void setY(int y);
    void move(int dy);
};

#endif // PADDLE_H
