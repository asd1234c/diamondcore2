// Copyright (C) DiamondCore <http://www.diamondcore.eu>
// Script by Skull

#include "vault_of_archavon.h"

/******************************************* Toravon's AI *******************************************/
struct DIAMOND_DLL_DECL boss_toravonAI : public ScriptedAI
{
	boss_toravonAI(Creature* c) : ScriptedAI(c)
	{
		m_pInstance = (ScriptedInstance*)c->GetInstanceData();
		Reset();
	}

	ScriptedInstance* m_pInstance;

	uint32 m_uiWhiteTimer;
	uint32 m_uiFrostTimer;
	uint32 m_uiFreezingTimer;
	uint32 m_uiFrozenTimer;

	void Reset()
	{
		m_uiWhiteTimer = 35000;
		m_uiFrostTimer = 15000;		 //Custom Timer don't know the correct Timer, if anyone knows the correct Timer please post it in the forum! <http://www.diamondcore.eu>
		m_uiFreezingTimer = 25000; //Custom Timer don't know the correct Timer, if anyone knows the correct Timer please post it in the forum! <http://www.diamondcore.eu>
		m_uiFrozenTimer = 30000;
	}

	void UpdateAI(const uint32 uiDiff)
	{
		if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
		return;
	
		if (m_uiWhiteTimer <= uiDiff)
		{
			DoCast(m_creature->getVictim(), SPELL_WHITEOUT);
			m_uiWhiteTimer = 35000;
		}
		else
		{
			m_uiWhiteTimer -= uiDiff;
		}

		if (m_uiFrostTimer <= uiDiff)
		{
			DoCast(m_creature->getVictim(), SPELL_FROSTBITE);
			m_uiFrostTimer = 15000;
		}
		else
		{
			m_uiFrostTimer -= uiDiff;
		}

		if (m_uiFreezingTimer <= uiDiff)
		{
			if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
      {
				if (Player* pPlayer = pTarget->GetCharmerOrOwnerPlayerOrPlayerItself())
				DoCast(pPlayer, SPELL_FREEZING_GROUND);
				m_uiFreezingTimer = 25000;
			}
		}
		else
		{
			m_uiFreezingTimer -= uiDiff;
		}

		if (m_uiFrozenTimer <= uiDiff)
		{
			if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
      {
				if (Player* pPlayer = pTarget->GetCharmerOrOwnerPlayerOrPlayerItself())
				DoCast(pPlayer, SPELL_FROZEN_ORB);
				m_uiFrozenTimer = 30000;
			}
		}
		else
		{
			m_uiFrozenTimer -= uiDiff;
		}
		DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_boss_toravon(Creature* pCreature)
{
	return new boss_toravonAI(pCreature);
}

void AddSC_boss_toravon()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "boss_toravon";
	newscript->GetAI = &GetAI_boss_toravon;
	newscript->RegisterSelf();
}