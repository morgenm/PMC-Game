#include "engine_handler.h"

Game& EngineHandler::CreateGameEngine() {
    return m_GameEngine.Create();
}

MessageSystem& EngineHandler::CreateMsgSys() {
    return m_MsgSys.Create();
}
