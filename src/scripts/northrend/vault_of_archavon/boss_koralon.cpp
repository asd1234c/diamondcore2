// Copyright (C) DiamondCore <http://www.diamondcore.eu>
// Script by Skull

#include "vault_of_archavon.h"

/***************************************** Koralon's AI ******************************************/
struct DIAMOND_DLL_DECL boss_koralonAI : public ScriptedAI
{
	boss_koralonAI(Creature* c) : ScriptedAI(c)
	{
		m_pInstance = (ScriptedInstance*)c->GetInstanceData();
    Reset();
	}

	ScriptedInstance* m_pInstance;

	uint32 m_uiBreathTimer;
	uint32 m_uiMeteorTimer;
	uint32 m_uiCinderTimer;
	uint32 m_uiFuryTimer;

	void Reset()
	{
		m_uiBreathTimer = 45000;
		m_uiMeteorTimer = 50000;
		m_uiCinderTimer = 10000;	// Custom Timer don't know the correct Timer, if anyone knows the correct Timer please post it in the forum! <http://www.diamondcore.eu>
		m_uiFuryTimer = 20000;
	}

	void UpdateAI(const uint32 uiDiff)
	{
		if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
		return;

		if (m_uiBreathTimer <= uiDiff)
		{
			DoCast(m_creature->getVictim(), SPELL_BURNING_BREATH);
			m_uiBreathTimer = 45000;
		}
		else
		{
			m_uiBreathTimer -= uiDiff;
		}

		if (m_uiMeteorTimer <= uiDiff)
		{
			DoCast(m_creature->getVictim(), SPELL_METEOR_FISTS);
			m_uiMeteorTimer = 50000;
		}
		else
		{
			m_uiMeteorTimer -= uiDiff;
		}

		if (m_uiCinderTimer <= uiDiff)
		{
			if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
      {
				if (Player* pPlayer = pTarget->GetCharmerOrOwnerPlayerOrPlayerItself())
				DoCast(pPlayer, SPELL_FLAMING_CINDER);
				m_uiCinderTimer = 10000;
			}
		}
		else
		{
			m_uiCinderTimer -= uiDiff;
		}

		if (m_uiFuryTimer <= uiDiff)
		{
			DoCast(m_creature, SPELL_BURNING_FURY);
			m_uiFuryTimer = 20000;
		}
		else
		{
			m_uiFuryTimer -= uiDiff;
		}
		DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_boss_koralon(Creature *pCreature)
{
	return new boss_koralonAI(pCreature);
}

void AddSC_boss_koralon()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "boss_koralon";
	newscript->GetAI = &GetAI_boss_koralon;
	newscript->RegisterSelf();
}