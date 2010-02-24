#include "the_forge_of_souls.h"

struct trash_soulscareAI : public ScriptedAI
{
			trash_soulscareAI(Creature* c) : ScriptedAI(c)
	{
		c->GetInstanceData();
        //m_bIsRegularMode = c->GetMap();
        Reset();
  }
		ScriptedInstance* m_pInstance;

		uint32 m_SoulHitTimer;

		void Reset()
		{
			m_SoulHitTimer = 10000;
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			return;
			if (m_SoulHitTimer <= uiDiff)
			{
				m_SoulHitTimer = 10000;
				SELECT_TARGET_RANDOM, 1;
				DoCast(m_creature->getVictim() , SPELL_SOUL_HIT);
			}else m_SoulHitTimer -= uiDiff;

			DoMeleeAttackIfReady();
		}
};
	CreatureAI* GetAI_trash_soulscare(Creature* c)
{
	return new trash_soulscareAI(c);
}

void AddSC_trash_soulscare()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "trash_soulscare";
	newscript->GetAI = &GetAI_trash_soulscare;
	newscript->RegisterSelf();
}