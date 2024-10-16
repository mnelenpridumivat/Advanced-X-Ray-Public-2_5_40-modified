#include "pch_script.h"
#include "ai_trader.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CAI_Trader::script_register(lua_State *L)
{
	module(L)
	[
		class_<CAI_Trader,CGameObject>("CAI_Trader")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CAI_Trader, CObjectScript);
