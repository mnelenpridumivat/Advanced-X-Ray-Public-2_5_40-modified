#include "pch_script.h"
#include "WeaponAK74.h"
#include "script_export_space.h"

CWeaponAK74::CWeaponAK74(ESoundTypes eSoundType) : CWeaponMagazinedWGrenade(eSoundType)
{}

CWeaponAK74::~CWeaponAK74()
{}

using namespace luabind;

#pragma optimize("s",on)
void CWeaponAK74::script_register	(lua_State *L)
{
	module(L)
	[
		class_<CWeaponAK74,CGameObject>("CWeaponAK74")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CWeaponAK74, CObjectScript);
