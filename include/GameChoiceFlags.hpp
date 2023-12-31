#pragma once

class GameChoiceFlags
{
    public:
        bool m_isButinButtonHovered = false;
        bool m_wasButinButtonHovered = false;
        bool m_isButinButtonSelected = false;
        bool m_isButinButtonPressed = false;

        bool m_isCheckersButtonHovered = false;
        bool m_wasCheckersButtonHovered = false;
        bool m_isCheckersButtonSelected = false;
        bool m_isCheckersButtonPressed = false;

        bool m_isBulltrickerButtonHovered = false;
        bool m_wasBulltrickerButtonHovered = false;
        bool m_isBulltrickerButtonSelected = false;
        bool m_isBulltrickerButtonPressed = false;

        bool m_isExitButtonHovered = false;
        bool m_wasExitButtonHovered = false;
        bool m_isExitButtonSelected = false;
        bool m_isExitButtonPressed = false;
};