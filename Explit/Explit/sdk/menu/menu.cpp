#include "menu.hpp"
c_menu g_menu;
int imatype = 0;
std::vector<std::string> st = { "Cype 1", "type 2" ,"type 3", "type 4"};
std::vector<std::string> st2 = { "multi 1", "type 2" ,"type 3", "type 4" };
bool local = false;
bool enemy = false;
bool team = false;
bool weapons = false;
bool chickens = false;
bool grenades = false;
std::vector< zgui::multi_select_item > combo_test{{ "Local", &local },{ "Enemy", &enemy},
	{ "Team", &team},
	{ "Weapons", &weapons },
	{ "Chickens", &chickens},
	{ "Grenades", &grenades},
};
int dsds = 1;
bool dsa = false;
int key = 2;
float slid = 22;
float nslid = -24;
std::string dasd = "";
void c_menu::draw()
{
	zgui::poll_input("Counter-Strike: Global Offensive");
	if (zgui::begin_window("Explit for Counter-Strike: Global Offensive", { 500, 350 }, g_draw.menu, zgui::zgui_window_flags_none))
	{
		if (zgui::tab_button("Aimbot", { 165,30 }, aimbot))
		{
			aimbot = true;
			visuals = false;
			misc = false;
		}
		zgui::same_line();
		zgui::next_column( -5,0 );
		if (zgui::tab_button("Visuals", { 165,30 }, visuals))
		{
			aimbot = false;
			visuals = true;
			misc = false;
		}
		zgui::same_line();	
		zgui::next_column( -5,0 );
		if (zgui::tab_button("Misc", { 166,30 }, misc))
		{
			aimbot = false;
			visuals = false;
			misc = true;
		}
		zgui::next_column( -327,34 );
		if (aimbot)draw_aimbot();
		if (visuals)draw_visuals();
		if (misc)draw_misc();
		zgui::end_window();
	}

	if(g_config.settings.misc.watermark) draw_watermark();
}

void c_menu::draw_watermark()
{
	const auto chrono_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	const auto time = ctime(&chrono_time);
	auto fps = static_cast<int>(1.f / g_interfaces.p_global_vars->frame_time);
	int width, height;
	g_interfaces.p_engine->get_screen_size(width, height);
	
	g_draw.fill_rect(width - 280, 20, 260, 28, color(1, 1, 1, 255));
	g_draw.fill_rect(width - 279, 21, 258, 26, color(51, 51, 51, 255));
	g_draw.fill_rect(width - 278, 22, 256, 24, color(41, 41, 41, 255));
	g_draw.fill_rect(width - 277, 23, 254, 22, color(51, 51, 51, 255));
	g_draw.fill_rect(width - 276, 24, 252, 20, color(1, 1, 1, 255));
	g_draw.fill_rect(width - 275, 25, 250, 18, color(31, 31, 31, 255));
	g_draw.fill_rect(width - 275, 42, 250, 1, color(255, 85, 85, 255));

	const auto connected = g_interfaces.g_local_player && g_interfaces.p_engine->is_in_game() && g_interfaces.p_engine->is_connected();
	const auto ping_str = connected ? g_utils.stringer(static_cast<int>(g_interfaces.p_engine->get_net_channel_info()->get_avg_latency(0) * 1000)) : "0";

	g_draw.string(width - 271, 27, color(255, 255, 255), g_draw.menu, false , g_utils.stringer(time, "  FPS:", fps, "  PING:", ping_str, "ms"));
	
}

void c_menu::draw_misc()
{
	zgui::begin_groupbox("Misc", { 163,290 });
	if (zgui::button("Save"))
		g_config.save();
	if (zgui::button("Load"))
		g_config.load();
	if (zgui::button("Unhook"))
		g_sdk.unhook = true;
	zgui::end_groupbox();
}
void c_menu::draw_visuals()
{
	zgui::begin_groupbox("ESP");
	{
		zgui::checkbox("Enable#1", g_config.settings.visuals.esp.esp);
		zgui::checkbox("Box", g_config.settings.visuals.esp.box);
		zgui::combobox("Box Type", std::vector<std::string>{"Full Box", "Corner Box"}, g_config.settings.visuals.esp.box_type);
		zgui::checkbox("Filled Box", g_config.settings.visuals.esp.fill_box);
		zgui::checkbox("Outlined Box", g_config.settings.visuals.esp.outline_box);
		zgui::checkbox("Name", g_config.settings.visuals.esp.name);
		zgui::checkbox("Distance", g_config.settings.visuals.esp.distance);
		zgui::combobox("Health", std::vector<std::string>{"Off", "Bar", "Text", "Bar+Text"}, g_config.settings.visuals.esp.health);
		zgui::combobox("Armor", std::vector<std::string>{"Off", "Bar", "Text", "Bar+Text"}, g_config.settings.visuals.esp.armor);
		zgui::checkbox("Money", g_config.settings.visuals.esp.money);
		zgui::checkbox("Weapon", g_config.settings.visuals.esp.weapon);
		zgui::checkbox("Ammo", g_config.settings.visuals.esp.ammo);
		zgui::checkbox("Snaplines", g_config.settings.visuals.esp.snaplines);
		zgui::checkbox("Skeleton", g_config.settings.visuals.esp.skeletons);
		zgui::checkbox("Vulnerability", g_config.settings.visuals.esp.vulnerability);
		zgui::multi_combobox("Filter", std::vector< zgui::multi_select_item >{ { "Local", &g_config.settings.visuals.esp.local }, { "Enemy", &g_config.settings.visuals.esp.enemies }, { "Team", &g_config.settings.visuals.esp.team }, { "Weapons", &g_config.settings.visuals.esp.weapons }, { "Chickens", &g_config.settings.visuals.esp.chickens }});

	}
	zgui::end_groupbox();

	zgui::next_column();

	zgui::begin_groupbox("Chams");
	{
		zgui::checkbox("Enable#2", g_config.settings.visuals.chams.chams);
	}
	zgui::end_groupbox();

	zgui::next_column();

	zgui::begin_groupbox("Glow");
	{
		zgui::checkbox("Enable#3", g_config.settings.visuals.glow.glow);
	}
	zgui::end_groupbox();
}
void c_menu::draw_aimbot()
{

}
