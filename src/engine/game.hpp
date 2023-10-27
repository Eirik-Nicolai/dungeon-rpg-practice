#ifndef GAME_H_
#define GAME_H_

#include <queue>
#include <entt/entt.hpp>
#include "olcPixelGameEngine.h"

#include "menu.hpp"
#include "utils/utils.hpp"

#include "types_and_defines.hpp"
#include "components/combat.hpp"
#include "components/globals.hpp"
#include "components/equipment.hpp"
#include "components/rendering.hpp"

#include "systems/AI/ai.hpp"
#include "systems/logic/logic.hpp"
#include "systems/movement/movement.hpp"
#include "systems/combat/buff_debuff.hpp"
#include "systems/combat/action_perform.hpp"

class DungeonThing : public olc::PixelGameEngine
{
    public:
        DungeonThing();

    public:
        bool OnUserCreate() override;
        bool OnUserUpdate(float) override;

    private: //states
        void STATE_WALKING(float);
        void STATE_COMBAT(float);
        void STATE_PAUSE(float);


        void on_load_init();
        void on_load_combat();

        void on_render_walking();


        void on_render_paused();
        void on_render_paused_stats();
        void on_render_paused_overview();
        void on_render_paused_inventory();
        void on_render_paused_equipment();


        void on_render_combat();

        void on_render_transition_to_walking_from_combat(float dt);
        void on_render_transition_combat(float dt);

        void on_userinput_walking();
        void on_userinput_paused();
        void on_userinput_combat();

        bool delay_for(float, float);

    private:
        entt::registry m_reg;
        void render_windows();


        State CURR_STATE;
        State NEXT_STATE;

        float m_fElapsedTimeSinceTick;

        entt::entity m_player;

        // TODO move to ctx and refactor
        float m_transition_progress;
        float m_transition_acc;
        float m_transition_time;
        float m_elapsed_transition_time;

        // COMBAT
        std::queue<combat_action> m_movequeue_player;
        std::queue<combat_action> m_movequeue_allies;
        std::queue<combat_action> m_movequeue_enemy;
        entt::entity m_intended_action;
        std::vector<CombatMenu> m_combat_menus;
        int m_curr_menu;
        TargetMenu m_target_menu;

        // EQUIPMENT AND INVENTORY
        SimpleMenu m_pause_menu;

        //ScrollableMenu m_equipment_menu;
        ScrollableMenu m_inventory_menu;
        int m_current_selected_equipment_type;
        std::vector<entt::entity> m_inventory_list;

    public:
        std::vector<std::string> m_debug;
        std::string get_name(const entt::entity&, std::string = "UNNAMED_ENTITY");

        bool has_enough_resources(entt::entity&, entt::entity&);
        std::vector<entt::entity> get_inventory_of_equip_type(entt::entity&);
        void set_equipment(const entt::entity &);
        void update_stats_on_hover(entt::entity &);
        void update_stats_on_select(entt::entity &);

        template <typename component>
        void draw_resource_bar(component &c, int x, int y, int w, int h, olc::Pixel col)
        {
            DrawRect(x,y, w, h, col);
            FillRect(x+5,y+5,
                     (w-5)*get_percentage(c.curr, c.max)-5, h-10, olc::WHITE);
        }

        void draw_effect_icon(const std::string&, int x, int y, olc::Pixel inner, olc::Pixel outer);

        //TODO a bit grim doing it like this
        bool m_equip_finger_left;
        bool m_equip_head_left;

        template <typename component>
        bool tryget_component(entt::entity &ent, component &comp)
        {
            if(auto getcomp = m_reg.try_get<component>(ent);m_reg.try_get<component>(ent) != nullptr)
            {
                comp = (*getcomp);
                return true;
            }
            return false;
        }

        template <typename component>
        bool tryget_component(const entt::entity &ent, component &comp)
        {
            if(auto getcomp = m_reg.try_get<component>(ent);m_reg.try_get<component>(ent) != nullptr)
            {
                comp = (*getcomp);
                return true;
            }
            return false;
        }

        //TODO check reference
        template <typename component>
        component get(entt::entity e)
        {
            return m_reg.get<component>(e);
        }

        template <typename component>
        const component cget(entt::entity e) const
        {
            return m_reg.get<component>(e);
        }
};


#endif // GAME_H_
