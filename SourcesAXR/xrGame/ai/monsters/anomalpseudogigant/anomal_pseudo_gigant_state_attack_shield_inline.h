#include "anomal_pseudo_gigant_state_attack_shield.h"
#pragma once

template <class Object>
CStateAnomalPseudoGigantShield<Object>::CStateAnomalPseudoGigantShield (Object *obj) : inherited(obj)
{
	m_last_shield_started			=	0;
	m_shield_start_anim_length_sec	=	0;
	m_next_particle_allowed			=	0;
}

template <class Object>
void   CStateAnomalPseudoGigantShield<Object>::initialize()
{
	inherited::initialize				();
	object->set_script_capture			(false);
	m_last_shield_started			=	current_time();
	m_next_particle_allowed			=	-1;
	m_started						=	false;

	MotionID	motion;
	object->anim().get_animation_info	(eAnimShieldStart, 0, motion, m_shield_start_anim_length_sec);
}

template <class Object>
void   CStateAnomalPseudoGigantShield<Object>::execute()
{
	if ( !m_started ) // && current_time() > m_last_shield_started + TTime(m_shield_start_anim_length_sec*1000) )
	{
		m_started					=	true;
		object->ActivateShield			();
	}

	if ( m_started && 
		 object->m_shield_keep_particle != 0 && 
		 current_time() > m_next_particle_allowed )
	{
		object->CParticlesPlayer::StartParticles	(object->m_shield_keep_particle, 
													 Fvector().set(0,1,0), 
													 object->ID(), 
													 -1, 
													 true);

		m_next_particle_allowed		=	current_time() + object->m_shield_keep_particle_period;
	}

	//object->face_enemy					();
	object->set_action					(ACT_STAND_IDLE);

	object->anim().set_override_animation	(m_started ? eAnimShieldContinue : eAnimShieldStart);

	//inherited::execute();
}

template <class Object>
void   CStateAnomalPseudoGigantShield<Object>::finalize()
{
	inherited::finalize();
	object->DeactivateShield			();
	object->anim().clear_override_animation();
	//object->set_action(ACT_RUN);
	object->set_script_capture			(true);
}

template <class Object>
void   CStateAnomalPseudoGigantShield<Object>::critical_finalize()
{
	inherited::critical_finalize		();
	object->DeactivateShield			();
	//object->set_action(ACT_RUN);
	object->anim().clear_override_animation();
	object->set_script_capture			(false);
}

template <class Object>
bool   CStateAnomalPseudoGigantShield<Object>::check_start_conditions()
{
	if ( current_time() < m_last_shield_started + object->m_shield_time + object->m_shield_cooldown )
		return							false;
	
	if ( !object->EnemyMan.enemy_see_me_now() )
		return							false;

	return								true;
}

template <class Object>
bool   CStateAnomalPseudoGigantShield<Object>::check_completion()
{
	/*Msg("CStateAnomalPseudoGigantShield: shield active, start time = [%d], duration = [%d], current time = [%d], left = [%d]",
		m_last_shield_started,
		object->m_shield_time,
		current_time(),
		(int)(m_last_shield_started + object->m_shield_time) - (int)current_time()
	);*/
#ifdef DEBUG
	Msg("CStateAnomalPseudoGigantShield: shield active time = [%d], duration = [%d]",
		current_time() - m_last_shield_started,
		object->m_shield_time
	);
#endif
	if ( current_time() - m_last_shield_started >= object->m_shield_time )
		return							true;

	CEntityAlive const* enemy		=	object->EnemyMan.get_enemy();
	if ( !enemy )
		return							true;

	/*if (enemy == Actor())
	{
		if ( actor_is_reloading_weapon () )
			return						true;
	}*/

	if ( !object->EnemyMan.get_enemy() )
		return							true;

	return								false;
}