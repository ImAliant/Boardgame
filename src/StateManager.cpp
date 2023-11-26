#include "../include/StateManager.hpp"

Engine::StateManager::StateManager(): m_add(false), m_replace(false), m_remove(false) {}
Engine::StateManager::~StateManager() {}

void Engine::StateManager::Add(std::unique_ptr<State> toAdd, bool replace) 
{
    m_add = true;
    m_newState = std::move(toAdd);
    m_replace = replace;
}

void Engine::StateManager::PopCurrent()
{
    m_remove = true;
}

void Engine::StateManager::PopAll()
{
    m_removeAll = true;
    m_remove = false;
}

void Engine::StateManager::ProcessStateChange() 
{
    if (m_removeAll)
    {
        while (!m_stateS.empty())
        {
            m_stateS.pop();
        }

        m_removeAll = false;
    }
    else if (m_remove && !m_stateS.empty())
    {
        m_stateS.pop();

        if (!m_stateS.empty())
        {
            m_stateS.top()->Start();
        }

        m_remove = false;
    }

    if (m_add)
    {
        if (m_replace && !m_stateS.empty())
        {
            m_stateS.pop();
            m_replace = false;
        }

        if (!m_stateS.empty())
        {
            m_stateS.top()->Pause();
        }

        m_stateS.push(std::move(m_newState));
        m_stateS.top()->Init();
        m_stateS.top()->Start();
        m_add = false;
    }
}

std::unique_ptr<Engine::State>& Engine::StateManager::GetCurrent() 
{
    return m_stateS.top();
}

bool Engine::StateManager::IsEmpty() const
{
    return m_stateS.empty();
}