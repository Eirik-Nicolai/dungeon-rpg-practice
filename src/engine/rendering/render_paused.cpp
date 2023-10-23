#include "render.hpp"

void DungeonThing::on_render_paused()
{
    auto [winx, winy] = GetScreenSize();

    auto winx_main = winx * 0.65;

    DrawLine(BORDER_OFFS, BORDER_OFFS, winx_main-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(BORDER_OFFS, winy-BORDER_OFFS, winx_main-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(BORDER_OFFS, BORDER_OFFS, BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx_main-BORDER_OFFS, BORDER_OFFS, winx_main-BORDER_OFFS, winy-BORDER_OFFS); // right line

    DrawLine(winx_main + BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, BORDER_OFFS);     // top line
    DrawLine(winx_main + BORDER_OFFS, winy-BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // bottom line
    DrawLine(winx_main + BORDER_OFFS, BORDER_OFFS, winx_main + BORDER_OFFS, winy-BORDER_OFFS);     // left line
    DrawLine(winx-BORDER_OFFS, BORDER_OFFS, winx-BORDER_OFFS, winy-BORDER_OFFS); // right line

    auto winx_pause = winx - winx_main;

    //FIXME move to init menu
    int mid_menu_x = winx_main + winx_pause/2;
    int mid_menu_y = winy/2;

    //debug line
    // DrawLine(mid_menu_x, 0, mid_menu_x, winy);
    // DrawLine(0, mid_menu_y, winx, mid_menu_y);

    for(int i = 0; i < m_pausemenus[m_curr_menu].ListSize(); ++i)
    {
        DrawString(mid_menu_x - GetStringLength(m_pausemenus[m_curr_menu].list_items[i].text)/2,
                   mid_menu_y + (MENU_ITEM_OFFS_Y*i) - (MENU_ITEM_OFFS_Y*m_pausemenus[m_curr_menu].ListSize()/2),
                   m_pausemenus[m_curr_menu].list_items[i].text,
                   m_pausemenus[m_curr_menu].curr_selected==i ? olc::RED : olc::WHITE,
                   4);
    }
}
