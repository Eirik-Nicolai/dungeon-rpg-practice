#include "render.hpp"


void DungeonThing::on_render_transition_combat(float dt)
{
    auto [winx, winy] = GetScreenSize();

    auto winy_main = winy * 0.7;
    auto winy_combat = winy - winy_main;

    // FIXME what the fuck
    auto v = winy_combat/m_transition_time;
    m_elapsed_transition_time += GetElapsedTime();
    auto transition_coeff = 60*(m_transition_time/(m_elapsed_transition_time*m_elapsed_transition_time*m_elapsed_transition_time*m_elapsed_transition_time));
    if(transition_coeff < 10) transition_coeff = 10;
    m_transition_progress = 100-transition_coeff+10;// * GetElapsedTime();
    auto winy_transition = winy - (winy_combat * (m_transition_progress/100));

    auto col = olc::WHITE;
    if(m_transition_progress > 20) col = olc::GREY;
    if(m_transition_progress > 40) col = olc::DARK_GREY;
    if(m_transition_progress > 60) col = olc::VERY_DARK_GREY;
    if(m_transition_progress < 80)
    {
        auto walls = m_reg.view<_renderable, pos, size, _wall>();
        for( auto [ent, p, s]: walls.each() )
        {
            for(int y = 0; y < s.height; y+=PIXEL_OFFS)
            {
                for(int x = 0; x < s.width; x+=PIXEL_OFFS)
                {
                    DrawString(p.x+x, p.y+y, "H", col, 2);
                }
            }
        }

        auto simple = m_reg.view<_renderable, pos, simple_appearence>();
        for( auto [ent, p, app]: simple.each() )
        {
            DrawString(p.x, p.y, app.c, col, 2);
        }
    }
    DrawLine(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy_transition-BORDER_OFFS, winx-BORDER_OFFS, winy_transition-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy_transition-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy_transition-BORDER_OFFS); // right line

    DrawLine(BORDER_OFFS, winy_transition, winx-BORDER_OFFS, winy_transition);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, winy_transition, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, winy_transition, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line
}



void DungeonThing::on_render_transition_to_walking_from_combat(float dt)
{
    auto [winx, winy] = GetScreenSize();

    auto winy_main = winy * 0.7;
    auto winy_combat = winy - winy_main;

    // FIXME what the fuck
    auto v = winy_combat/m_transition_time;
    m_elapsed_transition_time += dt;
    auto transition_coeff = (1-(m_elapsed_transition_time)/m_transition_time);
    m_transition_progress = 100*transition_coeff;// * GetElapsedTime();
    std::cout << transition_coeff << ", " << m_transition_progress << std::endl;
    auto winy_transition = winy - (winy_combat * (m_transition_progress/100));

    auto col = olc::WHITE;
    if(m_transition_progress > 20) col = olc::GREY;
    if(m_transition_progress > 40) col = olc::DARK_GREY;
    if(m_transition_progress > 60) col = olc::VERY_DARK_GREY;
    if(m_transition_progress < 80)
    {
        auto walls = m_reg.view<_renderable, pos, size, _wall>();
        for( auto [ent, p, s]: walls.each() )
        {
            for(int y = 0; y < s.height; y+=PIXEL_OFFS)
            {
                for(int x = 0; x < s.width; x+=PIXEL_OFFS)
                {
                    DrawString(p.x+x, p.y+y, "H", col, 2);
                }
            }
        }

        auto simple = m_reg.view<_renderable, pos, simple_appearence>();
        for( auto [ent, p, app]: simple.each() )
        {
            DrawString(p.x, p.y, app.c, col, 2);
        }
    }
    DrawLine(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy_transition-BORDER_OFFS, winx-BORDER_OFFS, winy_transition-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy_transition-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy_transition-BORDER_OFFS); // right line

    DrawLine(BORDER_OFFS, winy_transition, winx-BORDER_OFFS, winy_transition);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, winy_transition, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, winy_transition, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line
}
