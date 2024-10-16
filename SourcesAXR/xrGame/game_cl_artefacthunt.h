#pragma once
#include "game_cl_teamdeathmatch.h"

class CUIGameAHunt;

class game_cl_ArtefactHunt :public game_cl_TeamDeathmatch
{
	friend class CUIMessagesWindow;
	CUIGameAHunt*						m_game_ui;	
	shared_str							m_Eff_Af_Spawn;
	shared_str							m_Eff_Af_Disappear;
	typedef game_cl_TeamDeathmatch inherited;

protected:
	const shared_str			GetBaseCostSect			() override {return "artefacthunt_base_cost";}
	void				TranslateGameMessage	(u32 msg, NET_Packet& P) override;
	void				shedule_Update			(u32 dt) override;

	BOOL				CanCallBuyMenu			() override;
	bool				CanBeReady				() override;
	void				UpdateMapLocations		() override;

	bool				NeedToSendReady_Spectator		(int key, game_PlayerState* ps) override;
	void				LoadSndMessages				() override;

	void				OnBuySpawnMenu_Ok		() override;	
public:
	u8									artefactsNum;//ah
	u16									artefactBearerID;//ah,ZoneMap
	u16									old_artefactBearerID;
	u8									teamInPossession;//ah,ZoneMap
	u8									old_teamInPossession;
	u16									artefactID;
	u16									old_artefactID;
	s32									iReinforcementTime;
	s32									dReinforcementTime;

	int									m_iSpawn_Cost;

public :
										game_cl_ArtefactHunt	();
	~game_cl_ArtefactHunt	() override;
	void				Init					() override;
	CUIGameCustom*		createGameUI			() override;
	void				SetGameUI				(CUIGameCustom*) override;
	void				net_import_state		(NET_Packet& P) override;
	void				GetMapEntities(xr_vector<SZoneMapEntityData>& dst) override;
	char*				getTeamSection			(int Team) override;
	bool				PlayerCanSprint			(CActor* pActor) override;

	void						SetScore				() override;
	void				OnSellItemsFromRuck		() override;

	void				OnSpawn					(CObject* pObj) override;
	void				OnDestroy				(CObject* pObj) override;
	void				SendPickUpEvent			(u16 ID_who, u16 ID_what) override;
	void					OnConnected				() override;
};
