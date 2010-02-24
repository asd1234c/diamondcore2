#include "the_forge_of_souls.h"

struct trash_wardenAI : public ScriptedAI
{
		trash_wardenAI(Creature* c) : ScriptedAI(c)
	{
		c->GetInstanceData();
        m_bIsRegularMode = c->GetMap();
        Reset();
  }

		ScriptedInstance* m_pInstance;

		uint32 m_RunenhuelleTimer;
		uint32 m_EntwaffnenTimer;
		uint32 m_HitTimer;
		uint32 m_DemoshoutTimer;

		bool m_bIsRegularMode;

		void Reset()
		{
			m_RunenhuelleTimer = 20000;
			m_EntwaffnenTimer = 15000;
			m_HitTimer = 4100;
			m_DemoshoutTimer = 1000;
		}
		void UpdateAI(const uint32 uiDiff)
		{
			if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			return;


			if (m_DemoshoutTimer < uiDiff)
			{
			m_DemoshoutTimer = 39000;
				DoCast(m_creature, SPELL_DEMOSHOUT);
			}m_DemoshoutTimer-=uiDiff;

			if (m_EntwaffnenTimer < uiDiff)
			{
				m_EntwaffnenTimer = 15000;
				DoCast(m_creature->getVictim(), SPELL_ENTWAFFNEN);
			}m_EntwaffnenTimer-=uiDiff;
			
			if (m_HitTimer < uiDiff)
			{
				m_HitTimer = 4100;
				DoCast(m_creature->getVictim(), SPELL_HIT);
			}m_HitTimer-=uiDiff;

			if (m_RunenhuelleTimer < uiDiff)
			{
				m_RunenhuelleTimer = 20000;
				DoCast(m_creature, SPELL_RUNENHUELLE);
			}m_RunenhuelleTimer-=uiDiff;
			DoMeleeAttackIfReady();
		}
};

	CreatureAI* GetAI_trash_warden(Creature* c)
{
	return new trash_wardenAI(c);
}

void AddSC_trash_warden()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "trash_warden";
	newscript->GetAI = &GetAI_trash_warden;
	newscript->RegisterSelf();
}