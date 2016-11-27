#include "multiplayerstate.h"
#include <enet/enet.h>
#include <stdio.h>
#include <iostream>
#include "gamestatemanager.h"

int x = 0;

MultiplayerState::MultiplayerState() {
    player = new Paddle(20, 300);

}

MultiplayerState::~MultiplayerState() {

}

void MultiplayerState::onEnter(GameStateManager *gsm, SDL_Renderer *renderer) {

    server = NULL;
    if (enet_initialize () != 0)
    {

    }


    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = ENET_HOST_ANY;
    /* Bind the server to port 1234. */
    address.port = 1234;

    server = enet_host_create (&address,
                              32,   /* number of clients */
                              2,    /* number of channels */
                              0,    /* Any incoming bandwith */
                              0);   /* Any outgoing bandwith */


    //std::cout << enet_address_get_host_ip(&address, "chasevedder.xyz", 1000);
    enet_address_set_host(&address, "chasevedder.xyz");

    serviceResult = 1;
}

void MultiplayerState::update(GameStateManager *gsm, SDL_Event *event, SDL_Renderer *renderer, float deltaTime) {


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
    }

    while (enet_host_service(server, &enetEvent, 10) > 0) {
        std::string message = "Paddle y: " + std::to_string(player->getY());
        ENetPacket *asdfasdf = enet_packet_create (message.c_str(), message.length() + 1, ENET_PACKET_FLAG_RELIABLE);
        switch (enetEvent.type) {
        case ENET_EVENT_TYPE_CONNECT:
            std::cout << address.host << ":" << address.port << std::endl;
            std::cout << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << std::endl;
            enet_host_broadcast(server, 0, asdfasdf);
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            char* s = (char*)enetEvent.packet->data;
            std::string temp = s;
            int i = std::stoi(temp);
            std::cout << i << std::endl;
            player->move(i);
            break;
        }
    }



}

void MultiplayerState::render(SDL_Renderer *renderer, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //Draw player
    SDL_Rect playerRect = {player->getX(), player->getY(), Paddle::WIDTH, Paddle::HEIGHT};
    SDL_RenderFillRect(renderer, &playerRect);
}

void MultiplayerState::exit() {
    enet_host_destroy (server);
    enet_deinitialize ();
}

