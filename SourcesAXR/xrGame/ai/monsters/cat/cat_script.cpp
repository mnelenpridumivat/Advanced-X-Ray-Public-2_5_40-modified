#include "pch_script.h"
#include "cat.h"
#include "base_client_classes.h"

using namespace luabind;

#pragma optimize("s",on)
void CCat::script_register(lua_State *L)
{
	module(L)
	[
		class_<CCat,CGameObject>("CCat")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CCat, CObjectScript);
