#include "render.hpp"

void DungeonThing::on_render_walking()
{
    auto [winx, winy] = GetScreenSize();
    DrawLine(BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line

    auto walls = m_reg.view<_renderable, pos, size, _wall>();
    for( auto [ent, p, s]: walls.each() )
    {
        for(int y = 0; y < s.height; y+=PIXEL_OFFS)
        {
            for(int x = 0; x < s.width; x+=PIXEL_OFFS)
            {
                DrawString(p.x+x, p.y+y, "H", olc::WHITE, 2);
            }
        }
    }

    auto simple = m_reg.view<_renderable, pos, simple_appearence>();
    for( auto [ent, p, app]: simple.each() )
    {
        DrawString(p.x, p.y, app.c, olc::WHITE, 2);
    }
}
