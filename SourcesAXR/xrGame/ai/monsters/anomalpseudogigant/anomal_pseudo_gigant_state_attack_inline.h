#pragma once

//#include "burer_state_attack_tele.h"
//#include "burer_state_attack_gravi.h"
#include "anomal_pseudo_gigant_state_attack_shield.h"
//#include "burer_state_attack_melee.h"
#include "../states/state_look_point.h"
#include "../states/state_move_to_restrictor.h"
#include "../states/monster_state_attack_run.h"
#include "../states/monster_state_attack_run_attack.h"
#include "../states/monster_state_attack_melee.h"
#include "../states/monster_state_attack_on_run.h"
#include "../states/monster_state_find_enemy.h"
#include "../states/monster_state_steal.h"
#include "../states/monster_state_attack_camp.h"
#include "anomal_pseudo_gigant_state_attack.h"
//#include "burer_state_attack_run_around.h"
//#include "burer_state_attack_antiaim.h"

namespace anomal_pseudogigant
{
	float const health_delta				=	0.3f;

} // namespace detail

template <typename Object>
CStateAnomalPseudoGigantAttack<Object>::CStateAnomalPseudoGigantAttack(Object *obj) : inherited(obj)
{
	add_state(eStateAttack_Run, xr_new<CStateMonsterAttackRun<Object> >(obj));
	add_state(eStateAttack_Melee, xr_new<CStateMonsterAttackMelee<Object> >(obj));
	add_state(eStateAttack_RunAttack, xr_new<CStateMonsterAttackRunAttack<Object> >(obj));
	add_state(eStateAttack_Attack_On_Run, xr_new<CStateMonsterAttackOnRun<Object> >(obj));
	add_state(eStateAttack_RunAway, xr_new<CStateMonsterHideFromPoint<Object> >(obj));
	add_state(eStateAttack_FindEnemy, xr_new<CStateMonsterFindEnemy<Object> >(obj));
	add_state(eStateAttack_Steal, xr_new<CStateMonsterSteal<Object> >(obj));
	add_state(eStateAttackCamp, xr_new<CStateMonsterAttackCamp<Object> >(obj));
	add_state(eStateAttack_MoveToHomePoint, xr_new<CStateMonsterAttackMoveToHomePoint<Object> >(obj));
	add_state(eStateCustomMoveToRestrictor, xr_new<CStateMonsterMoveToRestrictor<Object> >(obj));

	add_state(eStateBurerAttack_Shield, xr_new<CStateAnomalPseudoGigantShield<Object> >(obj));
	//add_state(eStateAttack_AttackHidden, xr_new<CStateAnomalPseudoGigantAttackHidden<CAnomalPseudoGigant> >(obj));

	/*add_state(eStateBurerAttack_Tele, xr_new<CStateBurerAttackTele<Object> >(obj));
	add_state(eStateBurerAttack_Gravi,		xr_new<CStateBurerAttackGravi<Object> >		(obj));
	add_state(eStateBurerAttack_Melee,		xr_new<CStateBurerAttackMelee<Object> >		(obj));
	add_state(eStateBurerAttack_FaceEnemy,	xr_new<CStateMonsterLookToPoint<Object> >	(obj));
	add_state(eStateBurerAttack_RunAround,	xr_new<CStateBurerAttackRunAround<Object> >	(obj));
	add_state(eStateBurerAttack_Shield,		xr_new<CStateBurerShield<Object> >			(obj));
	add_state(eStateBurerAttack_AntiAim,	xr_new<CStateBurerAntiAim<Object> >			(obj));
	add_state(eStateAttack_Run,				xr_new<CStateMonsterAttackRun<Object> >		(obj));
	add_state(eStateCustomMoveToRestrictor,	xr_new<CStateMonsterMoveToRestrictor<Object> >(obj));

	m_allow_anti_aim						=	false;
	m_wait_state_end						=	false;
	m_lost_delta_health						=	false;*/
}

template <typename Object>
void CStateAnomalPseudoGigantAttack<Object>::initialize()
{
	inherited::initialize();
	object->MeleeChecker.init_attack();

	m_time_next_run_away = 0;
	m_time_start_check_behinder = 0;
	m_time_start_behinder = 0;

	m_last_health							=	object->conditions().GetHealth();
	m_lost_delta_health						=	false;
	m_next_runaway_allowed_tick				=	0;
	m_allow_anti_aim						=	false;
	m_wait_state_end						=	false;

	
// 	CMonsterSquad *squad					=	monster_squad().get_squad(object);
// 	if ( squad )
// 	{
// 		squad->InformSquadAboutEnemy			(object->EnemyMan.get_enemy());
// 	}
}

template <typename Object>
void   CStateAnomalPseudoGigantAttack<Object>::execute()
{

	//bool	can_attack_on_move = object->can_attack_on_move();

	if(!object->m_shield_active){

		if (object->conditions().GetHealth() <= m_last_health - anomal_pseudogigant::health_delta)
		{
			m_last_health = object->conditions().GetHealth();
			m_lost_delta_health = true;
		}

		if (check_shield_state()) {
			select_state(eStateBurerAttack_Shield);
		}
		else { 
			switch_original_states();
		}
	}
	else if(get_state_current()->check_completion()) {
		get_state_current()->finalize();
		current_substate = static_cast<u32>(-1);
		prev_substate = current_substate;
		switch_original_states();
	}
	/*if (check_home_point()) {
		select_state(eStateAttack_MoveToHomePoint);
	}
	else if (check_steal_state()) {
		select_state(eStateAttack_Steal);
	}
	else if (check_camp_state()) {
		select_state(eStateAttackCamp);
	}
	else if (check_find_enemy_state()) {
		select_state(eStateAttack_FindEnemy);
	}
	else if (check_run_away_state()) {
		select_state(eStateAttack_RunAway);
	}
	else if (!can_attack_on_move &&
		check_run_attack_state()) {
		select_state(eStateAttack_RunAttack);
	}
	else if (can_attack_on_move) {
		select_state(eStateAttack_Attack_On_Run);
	}
	else
	{
		// ���������� ��� �����
		bool b_melee = false;
		if (prev_substate == eStateAttack_Melee)
		{
			if (!get_state_current()->check_completion())
			{
				b_melee = true;
			}
		}
		else if (get_state(eStateAttack_Melee)->check_start_conditions())
		{
			b_melee = true;
		}

		// ���������� ������� ���������
		select_state(b_melee ? eStateAttack_Melee : eStateAttack_Run);
	}*/

	get_state_current()->execute();

	prev_substate = current_substate;

	// Notify squad	
	CMonsterSquad* squad = monster_squad().get_squad(object);
	if (squad) {
		SMemberGoal				goal;
		goal.type = MG_AttackEnemy;
		goal.entity = const_cast<CEntityAlive*>(object->EnemyMan.get_enemy());

		squad->UpdateGoal(object, goal);
	}
	//////////////////////////////////////////////////////////////////////////

	/*CEntityAlive* enemy = const_cast<CEntityAlive*>(object->EnemyMan.get_enemy());

	// Notify squad	
	CMonsterSquad *squad					=	monster_squad().get_squad(object);
	if (squad) {
		SMemberGoal								goal;
		goal.type							=	MG_AttackEnemy;
		goal.entity							=	enemy;
		squad->UpdateGoal						(object, goal);
	}

	if ( object->anim().has_override_animation() )
	{
		object->anim().clear_override_animation();
	}

	if ( object->conditions().GetHealth() <= m_last_health - anomal_pseudogigant::health_delta )
	{
		m_last_health						=	object->conditions().GetHealth();
		m_lost_delta_health					=	true;
	}

	if ( m_wait_state_end )
	{
		if ( get_state_current()->check_completion() )
		{
			m_wait_state_end				=	false;
		}
		else
		{
			get_state_current()->execute		();
			prev_substate					=	current_substate;
			return;
		}
	}

	//m_allow_anti_aim						=	true;
	//bool const	anti_aim_ready				=	get_state(eStateBurerAttack_AntiAim)->check_start_conditions();
	//m_allow_anti_aim						=	false;

	//bool const	gravi_ready					=	get_state(eStateBurerAttack_Gravi)->check_start_conditions();
	bool const	shield_ready				=	get_state(eStateBurerAttack_Shield)->check_start_conditions();
	//bool const	tele_ready					=	get_state(eStateBurerAttack_Tele)->check_start_conditions();

	bool		selected_state				=	true;

	if (m_lost_delta_health && shield_ready)
	{
		m_lost_delta_health					=	false;
		select_state							(eStateBurerAttack_Shield);
	}
	else
	{
		selected_state						=	false;
	}

	if ( selected_state )
	{
		get_state_current()->execute			();
		m_wait_state_end					=	true;
		prev_substate						=	current_substate;
		return;
	}

	Fvector	const		enemy_pos			=	enemy->Position();
	Fvector	const		self_pos			=	object->Position();
	Fvector	const		self2enemy			=	enemy_pos - self_pos;
	float	const		self2enemy_dist		=	magnitude(self2enemy);
	
	//bool	const		in_runaway_range	=	self2enemy_dist < object->m_runaway_distance;
	//bool	const		in_normal_range		=	self2enemy_dist < object->m_normal_distance;

	if ( current_substate == eStateCustomMoveToRestrictor )
	{
		if ( !get_state_current()->check_completion() )
		{
			get_state_current()->execute		();
			prev_substate					=	current_substate;
			return;
		}
	}

	if ( get_state(eStateCustomMoveToRestrictor)->check_start_conditions() ) 
	{
		select_state							(eStateCustomMoveToRestrictor);
		get_state_current()->execute			();
		prev_substate						=	current_substate;
		return;
	}

	get_state_current()->execute				();
	prev_substate							=	current_substate;*/
}

template <typename Object>
void CStateAnomalPseudoGigantAttack<Object>::finalize()
{
	if ( object->anim().has_override_animation() )
	{
		object->anim().clear_override_animation	();
	}

	inherited::finalize							();
}

template <typename Object>
void CStateAnomalPseudoGigantAttack<Object>::critical_finalize()
{
	if ( object->anim().has_override_animation() )
	{
		object->anim().clear_override_animation	();
	}

	inherited::critical_finalize				();
}


/*template <typename Object>
bool   CStateAnomalPseudoGigantAttack<Object>::check_control_start_conditions (ControlCom::EControlType type)
{
	if ( type == ControlCom::eAntiAim )
	{
		return									m_allow_anti_aim;
	}

	return										true;
}*/

template<typename Object>
void CStateAnomalPseudoGigantAttack<Object>::switch_original_states()
{
	bool	can_attack_on_move = object->can_attack_on_move();
	if (check_home_point()) {
		select_state(eStateAttack_MoveToHomePoint);
	}
	else if (check_steal_state()) {
		select_state(eStateAttack_Steal);
	}
	else if (check_camp_state()) {
		select_state(eStateAttackCamp);
	}
	else if (check_find_enemy_state()) {
		select_state(eStateAttack_FindEnemy);
	}
	else if (check_run_away_state()) {
		select_state(eStateAttack_RunAway);
	}
	else if (!can_attack_on_move &&
		check_run_attack_state()) {
		select_state(eStateAttack_RunAttack);
	}
	else if (can_attack_on_move) {
		select_state(eStateAttack_Attack_On_Run);
	}
	else
	{
		// ���������� ��� �����
		bool b_melee = false;
		if (prev_substate == eStateAttack_Melee)
		{
			if (!get_state_current()->check_completion())
			{
				b_melee = true;
			}
		}
		else if (get_state(eStateAttack_Melee)->check_start_conditions())
		{
			b_melee = true;
		}

		// ���������� ������� ���������
		select_state(b_melee ? eStateAttack_Melee : eStateAttack_Run);
	}
}

template <typename Object>
bool CStateAnomalPseudoGigantAttack<Object>::check_steal_state()
{
	if (prev_substate == static_cast<u32>(-1)) {
		if (get_state(eStateAttack_Steal)->check_start_conditions())
			return true;
	}
	else if (prev_substate == eStateAttack_Steal) {
		if (!get_state(eStateAttack_Steal)->check_completion())
			return true;
	}
	return false;
}

template <typename Object>
bool CStateAnomalPseudoGigantAttack<Object>::check_camp_state()
{
	if (prev_substate == static_cast<u32>(-1)) {
		if (get_state(eStateAttackCamp)->check_start_conditions())
			return true;
	}
	else if (prev_substate == eStateAttackCamp) {
		if (!get_state(eStateAttackCamp)->check_completion())
			return true;
	}
	return false;
}

template <typename Object>
bool CStateAnomalPseudoGigantAttack<Object>::check_find_enemy_state()
{
	// check state find enemy
	if (object->EnemyMan.get_enemy_time_last_seen() + FIND_ENEMY_DELAY < Device.dwTimeGlobal)
		return true;
	return false;
}

template <typename Object>
bool CStateAnomalPseudoGigantAttack<Object>::check_run_away_state()
{
	if (m_time_start_behinder != 0)
		return false;

	if (prev_substate == eStateAttack_RunAway) {
		if (!get_state(eStateAttack_RunAway)->check_completion())
			return true;
		else m_time_next_run_away = Device.dwTimeGlobal + 10000;
	}
	else if ((object->EnemyMan.get_enemy() != Actor()) && object->Morale.is_despondent() && (m_time_next_run_away < Device.dwTimeGlobal)) {
		return true;
	}

	return false;
}

template <typename Object>
bool CStateAnomalPseudoGigantAttack<Object>::check_home_point()
{
	if (m_lost_delta_health)
	{
		m_lost_delta_health = false;
		select_state(eStateBurerAttack_Shield);
	}

	if (prev_substate != eStateAttack_MoveToHomePoint) {
		if (get_state(eStateAttack_MoveToHomePoint)->check_start_conditions())
			return true;
	}
	else {
		if (!get_state(eStateAttack_MoveToHomePoint)->check_completion())
			return true;
	}

	return false;
}

template <typename Object>
bool CStateAnomalPseudoGigantAttack<Object>::check_run_attack_state()
{
	if (!object->ability_run_attack()) return false;

	if (prev_substate == eStateAttack_Run) {
		if (get_state(eStateAttack_RunAttack)->check_start_conditions())
			return true;
	}
	else if (prev_substate == eStateAttack_RunAttack) {
		if (!get_state(eStateAttack_RunAttack)->check_completion())
			return true;
	}

	return false;
}

template <typename Object>
bool CStateAnomalPseudoGigantAttack<Object>::check_shield_state()
{
	return m_lost_delta_health;
	/*if (prev_substate == eStateAttack_Run) {
		if (get_state(eStateAttack_RunAttack)->check_start_conditions())
			return true;
	}
	else if (prev_substate == eStateAttack_RunAttack) {
		if (!get_state(eStateAttack_RunAttack)->check_completion())
			return true;
	}

	return false;*/
}

template <typename Object>
void CStateAnomalPseudoGigantAttack<Object>::setup_substates()
{
	state_ptr state = get_state_current();

	if (current_substate == eStateAttack_RunAway) {

		SStateHideFromPoint		data;
		data.point = object->EnemyMan.get_enemy_position();
		data.accelerated = true;
		data.braking = false;
		data.accel_type = eAT_Aggressive;
		data.distance = 20.f;
		data.action.action = ACT_RUN;
		data.action.sound_type = MonsterSound::eMonsterSoundAggressive;
		data.action.sound_delay = object->db().m_dwAttackSndDelay;
		data.action.time_out = 5000;

		state->fill_data_with(&data, sizeof(SStateHideFromPoint));

		return;
	}
}