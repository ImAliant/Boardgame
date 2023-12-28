#pragma once

class ViewFlags
{
    public:
        bool m_isLaunchgameButtonSelected = false;
        bool m_isLaunchgameButtonPressed = false;
        bool m_isLaunchgameButtonHovered = false;
        bool m_wasLaunchgameButtonHovered = false;
        bool m_isLaunchgameButtonVisible = true;
        bool m_isMenuButtonSelected = false;
        bool m_isMenuButtonPressed = false;
        bool m_isMenuButtonHovered = false;
        bool m_wasMenuButtonHovered = false;
        bool m_hasHighLightedCell = false;
        bool m_isPlayerturnTextVisible = false;
};  