#define OLC_PGE_APPLICATION

#include "game.hpp"

DungeonThing::DungeonThing()
{
    sAppName = "";
}

bool DungeonThing::OnUserCreate()
{
    on_init(m_reg);

    CURR_STATE = state::WALKING;
    NEXT_STATE = CURR_STATE;

    return true;
}

bool DungeonThing::OnUserUpdate(float dt)
{
    Clear(olc::BLACK);

    switch(CURR_STATE)
    {
        case state::COMBAT:
        {

        }
        break;

        case state::WALKING:
        {
            on_userinput_walking();

            on_render_walking();
        }
        break;

        default:
        {
            std::cout << "not impl" << std::endl;
        }
    }

    CURR_STATE = NEXT_STATE;

    return true;
}

// void DungeonThing::WindowBorder()
// {
//     for(int x = 0; x < 800; ++x)
//     {
//         DrawString(x,2,"-");
//         DrawString(x,600-2, "-");
//     }

//     for(int y = 0; y < 600; ++y)
//     {
//         DrawString(2, y, "|");
//         DrawString(800-2, y, "|");
//     }
// }
