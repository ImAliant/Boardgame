#include "../include/Launcher.hpp"
#include "../include/MainMenu.hpp"

#include <SFML/Window/Event.hpp>

using namespace WindowConstants;

Launcher::Launcher(): m_context(std::make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_TITLE, sf::Style::Close);
    m_context->m_window->setFramerateLimit(FRAMERATE_LIMIT);
    m_context->m_window->setVerticalSyncEnabled(VERTICAL_SYNC_ENABLED);
    m_context->m_window->setPosition(WINDOW_POSITION);
    
    InitAssets();

    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}

Launcher::~Launcher(){}

void Launcher::Run() const
{
    while (m_context->m_window->isOpen()) {
        m_context->m_states->ProcessStateChange();
        m_context->m_states->GetCurrent()->ProcessInput();
        m_context->m_states->GetCurrent()->Update();
        m_context->m_states->GetCurrent()->Draw();
    }
}

void Launcher::InitAssets() const
{
    m_context->m_assets->AddFont(MAIN_FONT, "../assets/fonts/DejaVuSansMono.ttf");
    m_context->m_assets->AddTexture(CHECKERS_BLACK_PAWN, "../assets/images/checkers/black_pawn.png");
    m_context->m_assets->AddTexture(CHECKERS_WHITE_PAWN, "../assets/images/checkers/white_pawn.png");
    m_context->m_assets->AddTexture(CHECKERS_BLACK_QUEEN, "../assets/images/checkers/black_queen.png");
    m_context->m_assets->AddTexture(CHECKERS_WHITE_QUEEN, "../assets/images/checkers/white_queen.png");
    m_context->m_assets->AddTexture(EMPTY_ASSET, "../assets/images/empty.png");
}