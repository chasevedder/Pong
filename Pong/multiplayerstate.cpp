#include "multiplayerstate.h"
#include <enet/enet.h>
#include <stdio.h>
#include <iostream>
#include "gamestatemanager.h"
#include "mainmenu.h"
#include "game.h"
#include <vector>
#include "test.pb.h"
#include <sstream>

int x = 0;

MultiplayerState::MultiplayerState() {

}

MultiplayerState::~MultiplayerState() {

}

void MultiplayerState::onEnter(GameStateManager *gsm, SDL_Renderer *renderer) {

    client = NULL;
    if (enet_initialize () != 0)
    {

    }

    client = enet_host_create(NULL, 1, 2, 57600 / 8, 14400 / 8);

    enet_address_set_host(&address, "chasevedder.xyz");
    address.port = 1234;

    peer = enet_host_connect(client, &address, 2, 0);

    text = new SDLText("Connecting...", 48, Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);

    connectedToServer = false;
}

void MultiplayerState::update(GameStateManager *gsm, SDL_Event *event, SDL_Renderer *renderer, float deltaTime) {

    if (!connectedToServer) {
        if (enet_host_service (client, &enetEvent, 0) > 0 &&
            enetEvent.type == ENET_EVENT_TYPE_CONNECT)
        {
            std::cout << "connected to server" << std::endl;
            connectedToServer = true;
        } else {
            std::cout << "connecting..." << std::endl;
        }
    }
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_1]) {
        ENetPacket * packet = enet_packet_create ("test", 5, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
    }

    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_QUIT) {
            gsm->changeState(NULL);
        }
        else if (event->type == SDL_MOUSEMOTION) {
            if (text->visible &&
                    event->button.x > text->getPos().x &&
                    event->button.x < text->getPos().x + text->getPos().w &&
                    event->button.y > text->getPos().y &&
                    event->button.y < text->getPos().y + text->getPos().h) {
                if (!text->selected) {
                    text->selected = true;
                    text->setColor(SDL_Color{255, 0, 0});
                }
            }
            else {
                if (text->selected) {
                    text->selected = false;
                    text->setColor(SDL_Color{255, 255, 255});
                }
            }
        }
        else if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
            if (text->visible &&
                    event->button.x > text->getPos().x &&
                    event->button.x < text->getPos().x + text->getPos().w &&
                    event->button.y > text->getPos().y &&
                    event->button.y < text->getPos().y + text->getPos().h) {
                ENetPacket * packet = enet_packet_create ("test", 5, ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(peer, 0, packet);
            }
        }
    }

    if (connectedToServer) {
        text->setText("Connected!");
    }


    while (enet_host_service(client, &enetEvent, 0) > 0) {
        switch (enetEvent.type) {
        case ENET_EVENT_TYPE_CONNECT:
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            std::stringstream ss;
            ss << enetEvent.packet->data;
            Test t;
            t.ParseFromString(ss.str());
            std::cout << t.message(0) << std::endl;
            break;
        }
    }




}

void MultiplayerState::render(SDL_Renderer *renderer, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    text->render(renderer);
}

void MultiplayerState::exit() {
    //enet_host_destroy (client);
    enet_deinitialize ();
}

