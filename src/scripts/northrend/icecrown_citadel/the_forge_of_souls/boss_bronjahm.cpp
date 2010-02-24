#include "the_forge_of_souls.h"

/* <Copyright by http://diamondcore.eu> 
TODO!
Work in Progress */

struct boss_bronjahmAI : public ScriptedAI
{
	boss_bronjahmAI(Creature* c) : ScriptedAI(c)
	{
		m_bIsRegularMode = c->GetMap();
		c->GetInstanceData();
        //m_bIsRegularMode = c->GetMap();
        Reset();
  }
	bool m_bIsRegularMode;

	ScriptedInstance* m_pInstance;
	//bool m_bIsRegularMode;

	uint32 m_MagicBaneTimer;
	uint32 m_ShadowBoltTimer;
	uint32 m_CorruptSoulTimer;
	//uint32 m_ConsumeSoulTimer;
	uint32 m_TeleportTimer;
	uint32 m_SoulStormTimer;
	uint32 m_FearTimer;
	uint32 m_uiPhase;

	void Reset()
	{
	m_MagicBaneTimer = 8000;
	m_ShadowBoltTimer = 2000;
	m_CorruptSoulTimer = 20000;
	//m_ConsumeSoulTimer = ;
	m_TeleportTimer = 1000;
	m_SoulStormTimer = 2000;
	m_FearTimer = 5000;
	m_uiPhase = 1;
	}

	void EnterCombat(Unit* who)
	{
		DoScriptText(SAY_AGGRO, m_creature);
	}

	void UpdateAI(const uint32 uiDiff)
	{
		if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			return;

		if (m_uiPhase = 1)
		{
			if ((m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 30))
			{
				m_uiPhase = 2;
			}
			
		if ((m_creature->GetHealth()*100 / m_creature->GetMaxHealth() > 30))
		{
		if (m_uiPhase == 1, m_MagicBaneTimer < uiDiff)
				{
					DoCast(m_creature->getVictim(), SPELL_MAGIC_BANE);
					m_MagicBaneTimer = 8000;
				}else m_MagicBaneTimer -= uiDiff;

		if (m_uiPhase == 1, m_CorruptSoulTimer < uiDiff)
		{
			SELECT_TARGET_RANDOM, 1;
			DoCast(m_creature->getVictim(), SPELL_CORRUPT_SOUL);
			//DoCast(m_creature->getVictim(), SPELL_CORRUPT_SOUL_FRAGMENT);
			m_CorruptSoulTimer = 20000;
		}else m_CorruptSoulTimer -= uiDiff;

		/*if (SPELL_CORRUPT_SOUL_FRAGMENT)
		{
			DoCast(m_creature->getVictim(), SPELL_CONSUME_SOUL);
		}*/
		if (m_uiPhase == 1)
		{
		DoMeleeAttackIfReady();
		}
		}
		}

		if ((m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 30))
		{
		if (m_uiPhase ==2, m_TeleportTimer < uiDiff)
		{
			DoCast(m_creature, SPELL_TELEPORT);
				m_TeleportTimer = 2000000;
			}else m_TeleportTimer -= uiDiff;

		if (m_uiPhase == 2, m_SoulStormTimer < uiDiff)
		{
			DoCast(m_creature, SPELL_SOULSTORM);
			m_SoulStormTimer = 2000000;
		}else m_SoulStormTimer -= uiDiff;

		if (m_uiPhase == 2, SPELL_SOULSTORM, m_FearTimer < uiDiff)
		{
					DoCast(m_creature->getVictim(), SPELL_FEAR);
					m_FearTimer = 9322;
				}else m_FearTimer -=uiDiff;

		if (m_uiPhase == 2, m_ShadowBoltTimer < uiDiff)
		{
			SELECT_TARGET_RANDOM, 1;
			DoCast(m_creature->getVictim(), SPELL_SHADOW_BOLT);
			m_ShadowBoltTimer = 2000;
		}else m_ShadowBoltTimer -= uiDiff;

				}
			}
};

	CreatureAI* GetAI_boss_bronjahm(Creature* c)
{
	return new boss_bronjahmAI(c);
}

void AddSC_boss_bronjahm()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "boss_bronjahm";
	newscript->GetAI = &GetAI_boss_bronjahm;
	newscript->RegisterSelf();
}