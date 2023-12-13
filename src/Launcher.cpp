#include "../include/Launcher.hpp"
#include "../include/MainMenu.hpp"

#include <SFML/Window/Event.hpp>

using namespace WindowConstants;

Launcher::Launcher(): m_context(std::make_shared<Context>())
{
    /*m_context->m_window->create(sf::VideoMode(500, 600), "Boardgame - Diamant/Hamdi", sf::Style::Close);
    m_context->m_window->setFramerateLimit(60);
    m_context->m_window->setVerticalSyncEnabled(true);
    m_context->m_window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - m_context->m_window->getSize().x / 2, 
                                    sf::VideoMode::getDesktopMode().height / 2 - m_context->m_window->getSize().y / 2));*/
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
    m_context->m_assets->AddTexture(CHECKERS_BLACK_PIECE, "../assets/images/checkers/black_piece.png");
    m_context->m_assets->AddTexture(CHECKERS_WHITE_PIECE, "../assets/images/checkers/white_piece.png");
    m_context->m_assets->AddTexture(EMPTY_ASSET, "../assets/images/empty.png");
}