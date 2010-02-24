#include "the_forge_of_souls.h"

struct trash_specwardenAI : public ScriptedAI
{
		trash_specwardenAI(Creature* c) : ScriptedAI(c)
	{
		c->GetInstanceData();
        //m_bIsRegularMode = c->GetMap();
        Reset();
  }
		ScriptedInstance* m_pInstance;

		uint32 m_SchattenSchleierTimer;
		uint32 m_KlageDerSeelenTimer;

		void Reset()
		{
			m_SchattenSchleierTimer = 19000;
			m_KlageDerSeelenTimer = 9000;
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			return;

			if (m_KlageDerSeelenTimer<=uiDiff)
				{
					m_KlageDerSeelenTimer = 9000;
					DoCast(m_creature->getVictim(), SPELL_KLAGE_DER_SEELEN);
				}else m_KlageDerSeelenTimer -= uiDiff;

			if (m_SchattenSchleierTimer<=uiDiff)
				{
					m_SchattenSchleierTimer = 19000;
					DoCast(m_creature->getVictim(), SPELL_SCHATTENSCHLEIER);
				}else m_SchattenSchleierTimer -= uiDiff;
			DoMeleeAttackIfReady();
		}
};
	CreatureAI* GetAI_trash_specwarden(Creature* c)
{
	return new trash_specwardenAI(c);
}

void AddSC_trash_specwarden()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "trash_specwarden";
	newscript->GetAI = &GetAI_trash_specwarden;
	newscript->RegisterSelf();
}