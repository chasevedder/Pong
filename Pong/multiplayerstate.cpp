#include "multiplayerstate.h"
#include <enet/enet.h>
#include <stdio.h>
#include <iostream>
#include "gamestatemanager.h"

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

    if (enet_host_service (client, &enetEvent, 5000) > 0 &&
        enetEvent.type == ENET_EVENT_TYPE_CONNECT)
    {
        std::cout << "connected to server" << std::endl;
    }
}

void MultiplayerState::update(GameStateManager *gsm, SDL_Event *event, SDL_Renderer *renderer, float deltaTime) {


    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_1]) {
        ENetPacket * packet = enet_packet_create ("test", 5, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
    }

    while (SDL_PollEvent(event) != 0) {
        if (event->type == SDL_QUIT) {
            gsm->changeState(NULL);
        }
    }

    while (enet_host_service(client, &enetEvent, 10) > 0) {
        switch (enetEvent.type) {
        case ENET_EVENT_TYPE_CONNECT:
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            break;
        }
    }



}

void MultiplayerState::render(SDL_Renderer *renderer, Uint8 alpha) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //Draw player
}

void MultiplayerState::exit() {
    enet_host_destroy (client);
    enet_deinitialize ();
}

