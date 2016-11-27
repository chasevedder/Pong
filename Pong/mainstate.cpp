#include "mainstate.h"

#include "gamestatemanager.h"
#include "pausemenu.h"
#include "game.h"
#include <iostream>
#include <string>
#include <sstream>

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

std::string to_string(int i) {
    std::ostringstream ss;
    ss << i;
    return ss.str();
}

void MainState::onEnter(GameStateManager *gsm, SDL_Renderer* renderer) {
    SDL_Surface* surf = TTF_RenderText_Solid(font, to_string(playerScore).c_str(), white);
    TTF_SizeText(font, to_string(playerScore).c_str(), &playerScoreRect.w, &playerScoreRect.h);
    playerScoreText = SDL_CreateTextureFromSurface(renderer, surf);
    playerScoreRect.x = (Game::SCREEN_WIDTH / 4) - (surf->w / 2);
    playerScoreRect.y = 50;

    surf = TTF_RenderText_Solid(font, to_string(enemyScore).c_str(), white);
    TTF_SizeText(font, to_string(enemyScore).c_str(), &enemyScoreRect.w, &enemyScoreRect.h);
    enemyScoreText = SDL_CreateTextureFromSurface(renderer, surf);
    enemyScoreRect.x = (3 * Game::SCREEN_WIDTH / 4) - (surf->w / 2);
    enemyScoreRect.y = 50;

    surf = TTF_RenderText_Solid(font, "Press Space to start", white);
    TTF_SizeText(font, "Press Space to start", &startRect.w, &startRect.h);
    startText = SDL_CreateTextureFromSurface(renderer, surf);
    startRect.x = (Game::SCREEN_WIDTH / 2) - (surf->w / 2);
    startRect.y = (Game::SCREEN_HEIGHT / 2) - (surf->h / 2) - 100;

    surf = TTF_RenderText_Solid(font, "You win!", white);
    TTF_SizeText(font, "You win!", &winRect.w, &winRect.h);
    winText = SDL_CreateTextureFromSurface(renderer, surf);
    winRect.x = (Game::SCREEN_WIDTH / 2) - (surf->w / 2);
    winRect.y = (Game::SCREEN_HEIGHT / 2) - (surf->h / 2) - 150;

    SDL_FreeSurface(surf);
}

void MainState::update(GameStateManager *gsm, SDL_Event* event, SDL_Renderer* renderer, float deltaTime) {

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W]) {
        player->move(-20 * deltaTime);
    }
    else if (keystate[SDL_SCANCODE_S]) {
        player->move(20 * deltaTime);
    }

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

    if (ball->started)
        ball->move(deltaTime);
    else {
        if (keystate[SDL_SCANCODE_SPACE]) {
            ball->started = true;
            int predY = enemy->predict(ball);
            enemy->setPred(predY);
            if (enemyScore >= 5 || playerScore >= 5){
                playerScore = 0;
                enemyScore = 0;
                SDL_Surface* surf = TTF_RenderText_Solid(font, to_string(playerScore).c_str(), white);
                TTF_SizeText(font, to_string(playerScore).c_str(), &playerScoreRect.w, &playerScoreRect.h);
                playerScoreText = SDL_CreateTextureFromSurface(renderer, surf);
                playerScoreRect.x = (Game::SCREEN_WIDTH / 4) - (surf->w / 2);
                playerScoreRect.y = 50;

                surf = TTF_RenderText_Solid(font, to_string(enemyScore).c_str(), white);
                TTF_SizeText(font, to_string(enemyScore).c_str(), &enemyScoreRect.w, &enemyScoreRect.h);
                enemyScoreText = SDL_CreateTextureFromSurface(renderer, surf);
                enemyScoreRect.x = (3 * Game::SCREEN_WIDTH / 4) - (surf->w / 2);
                enemyScoreRect.y = 50;
            }
        }
    }


    if (ball->getX() < 0) {
        ball->reset();
        ball->started = false;
        enemyScore++;
        if (enemyScore >= 5 && !ball->started) {
            SDL_Surface* lose = TTF_RenderText_Solid(font, "You lose!", white);
            TTF_SizeText(font, "You lose!", &winRect.w, &winRect.h);
            winText = SDL_CreateTextureFromSurface(renderer, lose);
            lose = TTF_RenderText_Solid(font, "Press Space to play again", white);
            TTF_SizeText(font, "Press Space to play again", &startRect.w, &startRect.h);
            startText = SDL_CreateTextureFromSurface(renderer, lose);
            startRect.x = (Game::SCREEN_WIDTH / 2) - (lose->w / 2);
            SDL_FreeSurface(lose);
        }
        SDL_Surface* surf = TTF_RenderText_Solid(font, to_string(enemyScore).c_str(), white);
        TTF_SizeText(font, to_string(enemyScore).c_str(), &enemyScoreRect.w, &enemyScoreRect.h);
        enemyScoreText = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
        player->collided = false;
        enemy->collided = false;
    }
    else if (ball->getX() > Game::SCREEN_WIDTH - (Ball::SIZE)) {
        ball->reset();
        ball->started = false;
        playerScore++;
        if (playerScore >= 5 && !ball->started) {
            SDL_Surface* win = TTF_RenderText_Solid(font, "You win!", white);
            TTF_SizeText(font, "You win!", &winRect.w, &winRect.h);
            winText = SDL_CreateTextureFromSurface(renderer, win);
            win = TTF_RenderText_Solid(font, "Press Space to play again", white);
            TTF_SizeText(font, "Press Space to play again", &startRect.w, &startRect.h);
            startText = SDL_CreateTextureFromSurface(renderer, win);
            startRect.x = (Game::SCREEN_WIDTH / 2) - (win->w / 2);
            SDL_FreeSurface(win);
        }
        SDL_Surface* surf = TTF_RenderText_Solid(font, to_string(playerScore).c_str(), white);
        TTF_SizeText(font, to_string(playerScore).c_str(), &playerScoreRect.w, &playerScoreRect.h);
        playerScoreText = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
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
    enemy->AI(ball, deltaTime);
}

void MainState::render(SDL_Renderer *renderer, Uint8 dim) {


    //Set color for everything
    SDL_SetRenderDrawColor(renderer, 0xFF - dim, 0xFF - dim, 0xFF - dim, 0xFF);
    SDL_SetTextureAlphaMod(playerScoreText, 0xFF-dim);
    SDL_SetTextureAlphaMod(enemyScoreText, 0xFF-dim);
    SDL_SetTextureAlphaMod(startText, 0xFF-dim);

    //Draw line
    for( int i = 0; i < 480; i += 4 ) {
        SDL_RenderDrawPoint(renderer, 640 / 2, i );
    }

    if (!ball->started) {
        SDL_RenderCopy(renderer, startText, NULL, &startRect);
        if (playerScore >= 5 || enemyScore >= 5) {
            std::cout << "gg" << std::endl;
            SDL_RenderCopy(renderer, winText, NULL, &winRect);
        }
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

