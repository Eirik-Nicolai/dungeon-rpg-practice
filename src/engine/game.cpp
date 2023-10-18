#define OLC_PGE_APPLICATION
#include "game.hpp"


DungeonThing::DungeonThing()
{
    sAppName = "";
    m_curr_menu = 0;
    m_transition_time = 2;
    m_transition_progress = 0;
    m_transition_acc = 5;
    m_elapsed_transition_time = 1;

    TextItem resume{
        "RESUME",
        [this]{
            NEXT_STATE = {state::WALKING, type::FROM_PAUSED_TRANSITION};
        }
    };
    TextItem options{
        "OPTIONS",
        []{
            std::cout << "OPTIONS NOT IMPL" << std::endl;
        }
    };
    TextItem exit{
        "EXIT",
        []{
            std::cout << "EXIT NOT IMPL" << std::endl;
        }
    };
    m_pausemenus.emplace_back(PauseMenu(resume, options, exit));


    TextItem attack{
        "ATTACK",
        [this]{
            std::cout << "ATTACK NOT IMPL" << std::endl;
        }
    };
    TextItem skill{
        "SKILL",
        [this]{
            m_curr_menu = 1;
        }
    };
    TextItem item{
        "ITEM",
        []{
            std::cout << "EXIT NOT IMPL" << std::endl;
        }};
    TextItem run {
        "RUN",
        [this]{
            NEXT_STATE = {state::WALKING, type::FROM_COMBAT_TRANSITION};
            std::cout << "EXIT NOT IMPL" << std::endl;
        }
};

    TextItem fire{
        "FIRE",
        [this]{
            std::cout << "FIRE NOT IMPL" << std::endl;
        }
    };
    TextItem ice{
        "ICE",
        []{
            std::cout << "ICE NOT IMPL" << std::endl;
        }
    };
    TextItem wind{
        "WIND",
        []{
            std::cout << "WIND NOT IMPL" << std::endl;
        }};
    m_combatmenus.emplace_back(CombatMenu(attack, skill, item, run));
    m_combatmenus.emplace_back(CombatMenu(fire,ice, wind));
}

bool DungeonThing::OnUserCreate()
{
    on_init(m_reg, m_player);

    CURR_STATE = {GameState::state::WALKING, GameStateType::type::FREEROAM};
    NEXT_STATE = CURR_STATE;

    m_fElapsedTimeSinceTick = 0;

    return true;
}

bool DungeonThing::OnUserUpdate(float dt)
{
    Clear(olc::BLACK);

    switch(CURR_STATE.state)
    {
        case state::COMBAT:
        {
            DrawString(600,400, "COMBAT");
            switch(CURR_STATE.type)
            {
                case type::INIT:
                {
                    DrawString(600,420, "INIT");
                    std::cout << "INIT" << std::endl;
                    // TODO save curr state ?

                    // TODO init entities used for combat

                    NEXT_STATE.type = type::PLAYING_TRANSITION;
                }
                break;
                case type::PLAYING_TRANSITION:
                {
                    DrawString(600,420, "PLAYING_TRANSITION");
                    // FIXME calcuate based on time to transition
                    // m_transition_progress += dt * (40*m_transition_acc);
                    // if(m_transition_acc > 1.0)m_transition_acc = m_transition_acc-(5.5*dt);
                    if(m_transition_progress >= 100)
                    {
                        m_transition_progress = 1.0;
                        NEXT_STATE.type = type::PLAYER_SELECTING;
                    }
                    on_render_transition_combat();
                }
                break;
                case type::PLAYER_SELECTING:
                {
                    DrawString(600,420, "SELECTING");
                    //std::cout << "SELECTING" << std::endl;
                    on_userinput_combat();
                    on_render_combat();
                }
                break;
                default:
                    std::cout << "TYPE NOT IMPL" << std::endl;
            }
        }
        break;

        case state::PAUSED:
        {
            DrawString(600,400, "PAUSED");
            on_userinput_paused();
            on_render_paused();
        }
        break;

        case state::WALKING:
        {
            DrawString(600,400, "WALKING");
            switch(CURR_STATE.type)
            {
                case type::INIT:
                {
                    DrawString(600,420, "INIT");
                    std::cout << "INIT" << std::endl;
                    // TODO save curr state ?

                    // TODO init entities used for combat

                    //NEXT_STATE.type = type::PLAYING_TRANSITION;
                }
                break;
                case type::FROM_COMBAT_TRANSITION:
                {
                    DrawString(600,420, "FROM_COMBAT");
                    NEXT_STATE.type = type::FREEROAM;
                }
                break;
                case type::FROM_PAUSED_TRANSITION:
                {
                    DrawString(600,420, "FROM_PAUSED");
                    NEXT_STATE.type = type::FREEROAM;

                }
                break;
                case type::FREEROAM:
                {
                    DrawString(600,420, "FREEROAM");
                    //std::cout << "SELECTING" << std::endl;
                    on_userinput_walking();

                    on_ai(m_reg);
                    if(m_fElapsedTimeSinceTick >= 0.1)
                    {
                        on_move(m_reg);
                        on_collision(m_reg);

                        auto movement = m_reg.view<const movespeed, const dirVertical, const dirHorisontal, moveTick, pos>();
                        for (auto [ent, speed, dirV, dirH, tick, p]: movement.each())
                        {
                            if(tick.tick >= speed.speed)
                            {
                                auto &p = m_reg.get<pos>(ent);
                                if(dirV.up)
                                {
                                    p.y -= 10;
                                }
                                if(dirV.down)
                                {
                                    p.y += 10;
                                }
                                if(dirH.left)
                                {
                                    p.x -= 10;
                                }
                                if(dirH.right)
                                {
                                    p.x += 10;
                                }
                                tick.tick = 0;
                            }
                        }
                        m_fElapsedTimeSinceTick = 0;
                    }
                    else
                    {
                        m_fElapsedTimeSinceTick += dt;
                    }

                    on_render_walking();
                }
                break;
                default:
                    std::cout << "TYPE NOT IMPL" << std::endl;
            }
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
