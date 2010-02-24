#include "the_forge_of_souls.h"

struct trash_soulwardenAI : public ScriptedAI
{
	trash_soulwardenAI(Creature* c) : ScriptedAI(c)
	{
		c->GetInstanceData();
        //m_bIsRegularMode = c->GetMap();
        Reset();
  }
		ScriptedInstance* m_pInstance;

		uint32 m_SeelenKrankheitTimer;
		uint32 m_SchattenBlitzTimer;
		uint32 m_SeelenEntzugTimer;
		uint32 m_TotenErweckungTimer;

		void Reset()
		{
			m_SeelenKrankheitTimer = 15000;
			m_SchattenBlitzTimer = 8000;
			m_SeelenEntzugTimer = 13000;
			m_TotenErweckungTimer = 30000;
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			return;


			if (m_SeelenKrankheitTimer<=uiDiff)
				{
					m_SeelenKrankheitTimer = 15000;
					SELECT_TARGET_RANDOM, 1;
					DoCast(m_creature->getVictim(), SPELL_SEELENKRANKHEIT);
				}else m_SeelenKrankheitTimer -= uiDiff;

			if (m_SchattenBlitzTimer<=uiDiff)
				{
					m_SchattenBlitzTimer = 8000;
					DoCast(m_creature->getVictim(), SPELL_SHADOWBOLT);
				}else m_SchattenBlitzTimer -= uiDiff;

			if (m_SeelenEntzugTimer<=uiDiff)
				{
					m_SeelenEntzugTimer = 13000;
					DoCast(m_creature->getVictim(), SPELL_SEELENENTZUG);
				}else m_SeelenEntzugTimer -= uiDiff;

			if (m_TotenErweckungTimer<=uiDiff)
				{
					m_TotenErweckungTimer = 30000;
					DoCast(m_creature->getVictim(), SPELL_TOTENERWECKUNG);
				}else m_TotenErweckungTimer -= uiDiff;

			DoMeleeAttackIfReady();
		}
};
	CreatureAI* GetAI_trash_soulwarden(Creature* c)
{
	return new trash_soulwardenAI(c);
}

void AddSC_trash_soulwarden()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "trash_soulwarden";
	newscript->GetAI = &GetAI_trash_soulwarden;
	newscript->RegisterSelf();
}
