#pragma once

#include <stack>
#include <memory>

#include "State.hpp"

namespace Engine
{
    class StateManager
    {
        private:
            std::stack<std::unique_ptr<State>> m_stateS;
            std::unique_ptr<State> m_newState;

            bool m_add;
            bool m_replace;
            bool m_remove;
            bool m_removeAll;
        public:
            StateManager();
            ~StateManager();

            void Add(std::unique_ptr<State> toAdd, bool replace = false);
            void PopCurrent();
            void PopAll();
            void ProcessStateChange();
            std::unique_ptr<State>& GetCurrent();
            bool IsEmpty() const;
    };
}