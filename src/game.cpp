#include "game.h"

EngineFeedRegisterRequest Game::GetFeedRegisterRequest() {
    EngineFeedRegisterRequest registerRequest;
    registerRequest.AddFeed(&m_GameMsgFeed);
    return registerRequest;
}
