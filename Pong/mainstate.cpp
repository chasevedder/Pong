#include "mainstate.h"

#include "gamestatemanager.h"
#include "pausemenu.h"
#include "game.h"
#include <string>

MainState::MainState() {
    player = new Paddle(20, (Game::SCREEN_HEIGHT / 2) - (Paddle::HEIGHT / 2));
    enemy = new Paddle(Game::SCREEN_WIDTH - Paddle::WIDTH - 20, Game::SCREEN_HEIGHT / 2 - Paddle::HEIGHT / 2);
    playerScore = 0;
    enemyScore = 0;

    ball = new Ball((Game::SCREEN_WIDTH / 2) - (Ball::SIZE / 2), (Game::SCREEN_HEIGHT / 2) - (Ball::SIZE / 2));

    //Load font and create texts
    font = TTF_OpenFont("../resources/OpenSans-Regular.ttf", 36);
    white = {255, 255, 255};


}

MainState::~MainState() {

}

void MainState::onEnter(GameStateManager *gsm, SDL_Renderer* renderer) {
    SDL_Surface* surf = TTF_RenderText_Solid(font, std::to_string(playerScore).c_str(), white);
    TTF_SizeText(font, std::to_string(playerScore).c_str(), &playerScoreRect.w, &playerScoreRect.h);
    playerScoreText = SDL_CreateTextureFromSurface(renderer, surf);
    playerScoreRect.x = (Game::SCREEN_WIDTH / 4) - (surf->w / 2);
    playerScoreRect.y = 50;

    surf = TTF_RenderText_Solid(font, std::to_string(enemyScore).c_str(), white);
    TTF_SizeText(font, std::to_string(enemyScore).c_str(), &enemyScoreRect.w, &enemyScoreRect.h);
    enemyScoreText = SDL_CreateTextureFromSurface(renderer, surf);
    enemyScoreRect.x = (3 * Game::SCREEN_WIDTH / 4) - (surf->w / 2);
    enemyScoreRect.y = 50;
}

void MainState::update(GameStateManager *gsm, SDL_Event* event, SDL_Renderer* renderer) {

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) {
        player->move(-4);
    }
    else if (keystate[SDL_SCANCODE_S]) {
        player->move(4);
    }
    if (keystate[SDL_SCANCODE_UP])
        enemy->move(-2);
    else if (keystate[SDL_SCANCODE_DOWN])
        enemy->move(2);

    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_QUIT) {
            gsm->changeState(NULL);
        }
        if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_ESCAPE) {
                gsm->changeState(new PauseMenu());
            }
        }
    }

    ball->move();


    if (ball->getX() < 0) {
        ball->reset();
        enemyScore++;
        SDL_Surface* surf = TTF_RenderText_Solid(font, std::to_string(enemyScore).c_str(), white);
        TTF_SizeText(font, std::to_string(enemyScore).c_str(), &enemyScoreRect.w, &enemyScoreRect.h);
        enemyScoreText = SDL_CreateTextureFromSurface(renderer, surf);
        player->collided = false;
        enemy->collided = false;
    }
    else if (ball->getX() > Game::SCREEN_WIDTH - (Ball::SIZE)) {
        ball->reset();
        playerScore++;
        SDL_Surface* surf = TTF_RenderText_Solid(font, std::to_string(playerScore).c_str(), white);
        TTF_SizeText(font, std::to_string(playerScore).c_str(), &playerScoreRect.w, &playerScoreRect.h);
        playerScoreText = SDL_CreateTextureFromSurface(renderer, surf);
        player->collided = false;
        enemy->collided = false;
    }
    if (player->collided == false && ball->collidesWithPaddle(player)) {
        ball->bounce(player);
        player->collided = true;
        enemy->collided = false;
        //Predict a position for the ball
        int predY = enemy->predict(ball);
        enemy->setPred(predY);
    }
    else if (enemy->collided == false && ball->collidesWithPaddle(enemy)) {
        ball->bounce(enemy);
        enemy->setPred(Game::SCREEN_HEIGHT / 2);
        enemy->collided = true;
        player->collided = false;
    }
    else if (ball->collidesWithWall()) {
        ball->bounce();
    }
    enemy->AI(ball);
}

void MainState::render(SDL_Renderer *renderer, Uint8 dim) {


    //Set color for everything
    SDL_SetRenderDrawColor(renderer, 0xFF - dim, 0xFF - dim, 0xFF - dim, 0xFF);
    SDL_SetTextureAlphaMod(playerScoreText, 0xFF-dim);
    SDL_SetTextureAlphaMod(enemyScoreText, 0xFF-dim);

    //Draw line
    for( int i = 0; i < 480; i += 4 ) {
        SDL_RenderDrawPoint(renderer, 640 / 2, i );
    }

    SDL_RenderCopy(renderer, playerScoreText, NULL, &playerScoreRect);
    SDL_RenderCopy(renderer, enemyScoreText, NULL, &enemyScoreRect);

    //Draw player
    SDL_Rect playerRect = {player->getX(), player->getY(), Paddle::WIDTH, Paddle::HEIGHT};
    SDL_RenderFillRect(renderer, &playerRect);

    //Draw enemy
    SDL_Rect enemyRect = {enemy->getX(), enemy->getY(), Paddle::WIDTH, Paddle::HEIGHT};
    SDL_RenderFillRect(renderer, &enemyRect);

    //Draw ball
    SDL_Rect ballRect = {ball->getX(), ball->getY(), Ball::SIZE, Ball::SIZE};
    SDL_RenderFillRect(renderer, &ballRect);


}

void MainState::exit() {

}

