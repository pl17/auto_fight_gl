#include <Windows.h>
#include "GameObj_XPathConst.h"


const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_GOLD={TEXT("sstat_gold_val"), NULL};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_RUBI={TEXT("sstat_ruby_val"), NULL};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_LEVEL={TEXT("header_values_level"), NULL};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_RANK={TEXT("header_values_ressources"), TEXT("div[2]/div[2]")};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_HP={TEXT("header_values_hp_bar_box"), TEXT("table/tbody/tr/td/table/tbody/tr/td/table/tbody/tr[1]/td[2]")};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_EXP={TEXT("tOoLtIp_header_values_xp_bar"), TEXT("table/tbody/tr/td/table/tbody/tr/td/table/tbody/tr[1]/td[2]")};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_LOCATION_POINT={TEXT("expeditionpoints_value"), NULL};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_LOCATION_COOLDOWN={TEXT("cooldown_bar_text_expedition"), NULL};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_DUNGEON_POINT={TEXT("dungeonpoints_value"), NULL};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_DUNGEON_COOLDOWN={TEXT("cooldown_bar_text_dungeon"), NULL};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_ARENA_COOLDOWN={TEXT("cooldown_bar_text_arena"), NULL};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_ARENA_RANK={TEXT("header_values_pvp"), TEXT("/div[1]/div[2]")};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_TURMA_COOLDOWN={TEXT("cooldown_bar_text_ct"), NULL};

const GAMEOBJ_XPATH GameObj_XPathConst::HEADER_TURMA_RANK={TEXT("header_values_pvp"), TEXT("/div[2]/div[2]")};

const GAMEOBJ_XPATH GameObj_XPathConst::MOD_DUNGEON={TEXT("cooldown_bar_text_dungeon"), TEXT("a")};

const GAMEOBJ_XPATH GameObj_XPathConst::MOD_LOCATION={TEXT("cooldown_bar_expedition"), TEXT("a")};

const GAMEOBJ_XPATH GameObj_XPathConst::MOD_ARENA={TEXT("cooldown_bar_arena"), TEXT("a")};

const GAMEOBJ_XPATH GameObj_XPathConst::MOD_TURMA={TEXT("cooldown_bar_ct"), TEXT("a")};

const GAMEOBJ_XPATH GameObj_XPathConst::MOD_QUEST={TEXT("mainmenu"), TEXT("a[2]")};

const GAMEOBJ_XPATH GameObj_XPathConst::CONT_LISTARENASERVER={TEXT("content"), TEXT("div[2]/table/tbody/tr[2]/td/div[2]/div/table/tbody")};

const GAMEOBJ_XPATH GameObj_XPathConst::CONT_LISTARENASERVER_EMAILNOTACTIVE={TEXT("content"), TEXT("div[3]/table/tbody/tr[2]/td/div[2]/div/table/tbody")};

const GAMEOBJ_XPATH GameObj_XPathConst::CONT_LISTARENASERVER_BASH={TEXT("content"), TEXT("div/table/tbody/tr[2]/td/div[2]/div/table/tbody")};

const GAMEOBJ_XPATH GameObj_XPathConst::CONT_LISTQUEST={TEXT("content"), TEXT("div/div")};

const GAMEOBJ_XPATH GameObj_XPathConst::CONT_QUESTREFRESH={TEXT("quest_footer_reroll"), TEXT("input")};

const GAMEOBJ_XPATH GameObj_XPathConst::CONT_LISTITEMMARKET={TEXT("auction_table"), TEXT("table/tbody")};

const GAMEOBJ_XPATH GameObj_XPathConst::MOD_ARENASERVER={TEXT("mainnav"), TEXT("li[2]/a")};

const GAMEOBJ_XPATH GameObj_XPathConst::MOD_TURMASERVER={TEXT("mainnav"), TEXT("li[4]/a")};

const GAMEOBJ_XPATH GameObj_XPathConst::MOD_OVERVIEW={TEXT("mainmenu"), TEXT("a[1]")};
