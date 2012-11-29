#include "StdAfx.h"
#include "Naxxramas.h"


//Thaddius/mini-boss
#define CN_THADDIUS							15928
#define CN_STALAGG							15929
#define CN_FEUGEN							15930
#define CN_TESLA_COIL						16218

#define GO_TESLA_STALAGG					181477
#define GO_TESLA_FEUGEN						181478

// Thaddius
#define SPELL_POLARITY_SHIFT				28089	// Every 30s to whole raid
#define SPELL_POSITIVE_CHARGE				28059
#define SPELL_POSITIVE_CHARGE_DAMAGE		28062
#define SPELL_POSITIVE_CHARGE_BUFF			29659
#define SPELL_NEGATIVE_CHARGE				28084
#define SPELL_NEGATIVE_CHARGE_DAMAGE		28085
#define SPELL_NEGATIVE_CHARGE_BUFF			29660
#define SPELL_CHAIN_LIGHTNING				28167	// Main target every 15s
#define SPELL_CHAIN_LIGHTNING_H				40536	// Heroic version
#define SPELL_THADDIUS_BERSERK				27680	// 6mins after start
#define SPELL_THADDIUS_BALL_LIGHTNING		28299
#define SPELL_THADIUS_LIGHTNING_VISUAL		28136


// Stalagg
#define SPELL_POWER_SURGE					54529	//randomly throughout fight on self
#define SPELL_POWER_SURGE_H					28134	//heroic version
#define SPELL_STALAGG_CHAIN					28096
#define SPELL_STALAGG_TESLA_PASSIVE			28097

// Feugen
#define SPELL_STATIC_FIELD					28135	//All players within 60 yards every 3 seconds
#define SPELL_STATIC_FIELD_H				54528	//Heroic version
#define SPELL_FEUGEN_CHAIN					28111
#define SPELL_FEUGEN_TESLA_PASSIVE			28109

// Stalagg and Feugen
#define SPELL_MAGNETIC_PULL					28338
#define SPELL_WARSTOMP						28125
#define SPELL_COSMETIC_CHAIN_LIGHTNING		37071

#define GO_THADDIUS_DOOR					181121
#define GO_CONSTRUCT_PORTAL_RAMP			181213

#define PLATFORM_FIELD_LIST_SIZE			3

static struct Coords platformField[] =
{
	{ 3540.08f, -2963.12f, 303.32f, 0.f, 0 }, // Cell Position = 202x300
	{ 3516.91f, -2937.40f, 302.91f, 0.f, 0 }, // Cell Position = 203x300
	{ 3473.14f, -2892.12f, 303.20f, 0.f, 0 }, // Cell Position = 203x299
};

class Feugen : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(Feugen, MoonScriptCreatureAI);
	Feugen(Creature *pCreature) : MoonScriptCreatureAI(pCreature)
	{
		if (Is25PlayerNormalRaid())
		{
			SetMaxHealth(2091000);
			SetHealth(GetMaxHealth());
			AddSpell2(SPELL_STATIC_FIELD_H, Target_Current, 3000, 0);
		}
		else
			AddSpell2(SPELL_STATIC_FIELD, Target_Current, 3000, 0);

		AddSpell2(SPELL_WARSTOMP, Target_Current, 20000, 10000);
		ChainLightning = AddSpell2(SPELL_CHAIN_LIGHTNING, Target_Current);

		RespawnTimer = INVALIDATE_TIMER;
		MoveTimer = INVALIDATE_TIMER;

		RegisterAIUpdateEvent(1000);

		AddEmote(Event_OnCombatStart, "Feed you to master!", Text_Yell, 8802);
		AddEmote(Event_OnDied, "No... more... Feugen...", Text_Yell, 8803);
		AddEmote(Event_OnTargetDied, "Feugen make master happy!", Text_Yell, 8804);
	}

	void AddMoveTimer()
	{
		MoveTimer = AddTimer(3000);
	}

	void AIUpdate()
	{
		Creature *Stallag;
		Creature *creat;

		Stallag = ForceCreatureFind(CN_STALAGG, 3450.45f, -2931.42f, 312.091f);
		if (Stallag && Stallag->isAlive() == false)
		{
			if (RespawnTimer == INVALIDATE_TIMER)
				RespawnTimer = AddTimer(5000);

			if (RespawnTimer != INVALIDATE_TIMER && IsTimerFinished(RespawnTimer) && IsAlive())
			{
				Stallag->Despawn(1, 0); // This will remove his corpse.
				SpawnCreature(CN_STALAGG, Stallag->GetSpawnX(), Stallag->GetSpawnY(), Stallag->GetSpawnZ(), 0.f, true);
				RespawnTimer = INVALIDATE_TIMER;
			}
		}

		if (MoveTimer != INVALIDATE_TIMER && IsTimerFinished(MoveTimer))
		{
			SetCanMove(true);
			RemoveTimer(MoveTimer);
		}

		// Lightning Rods: Initially stands near a lightning rod.
		// If Feugen is pulled away from these rods, he will Chain Lightning the raid.
		creat = ForceCreatureFind(CN_TESLA_COIL, 3527.977295f, -2952.480957f, 318.761841f);
		if (creat != NULL)
		{
			float dist;

			creat->CastSpell(_unit, SPELL_COSMETIC_CHAIN_LIGHTNING, true);

			dist = _unit->CalcDistance(creat);
			if (dist > 60.f)
				CastSpell(ChainLightning);
		}

		ParentClass::AIUpdate();
	}

	SpellDesc *ChainLightning;
	int32 RespawnTimer;
	int32 MoveTimer;
};

class Stalagg : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(Stalagg, MoonScriptCreatureAI);
	Stalagg(Creature *pCreature) : MoonScriptCreatureAI(pCreature)
	{
		if (Is25PlayerNormalRaid())
		{
			SetMaxHealth(2091000);
			SetHealth(GetMaxHealth());
			AddSpell2(SPELL_POWER_SURGE_H, Target_Self, 10000, 30000);
		}
		else
			AddSpell2(SPELL_POWER_SURGE, Target_Self, 10000, 30000);

		AddSpell2(SPELL_WARSTOMP, Target_Current, 20000, 10000);
		ChainLightning = AddSpell2(SPELL_CHAIN_LIGHTNING, Target_Current);

		MagneticPullTimer = INVALIDATE_TIMER;
		MoveTimer = INVALIDATE_TIMER;
		RespawnTimer = INVALIDATE_TIMER;

		RegisterAIUpdateEvent(1000);

		AddEmote(Event_OnCombatStart, "Stalagg crush you!", Text_Yell, 8864);
		AddEmote(Event_OnDied, "Master, save me!", Text_Yell, 8865);
		AddEmote(Event_OnTargetDied, "Stalagg kill!", Text_Yell, 8866);
	}

	void OnCombatStart(Unit *pAttacker)
	{
		MagneticPullTimer = AddTimer(30000);

		ParentClass::OnCombatStart(pAttacker);
	}

	void MagneticPull(Unit *caster, Unit *dest, Player *target)
	{
		float o = target->calcRadAngle(target->GetPositionX(), target->GetPositionY(), dest->GetPositionX(), dest->GetPositionY());
		target->SendMoveKnockBack(o, caster->CalcDistance(dest), -10.f, true);
	}

	void CastMagneticPull(Creature *feug)
	{
		MoonScriptBossAI *script;
		Unit *feugTarget;
		Unit *stalTarget;

		feugTarget = feug->GetAIInterface()->GetNextTarget();
		stalTarget = _unit->GetAIInterface()->GetNextTarget();
		if (feugTarget && feugTarget->IsPlayer() &&
			stalTarget && stalTarget->IsPlayer())
		{
			_unit->CastSpell(stalTarget, SPELL_MAGNETIC_PULL, true);
			feug->CastSpell(feugTarget, SPELL_MAGNETIC_PULL, true);

			MagneticPull(_unit, feug, stalTarget->ToPlayer());
			MagneticPull(feug, _unit, feugTarget->ToPlayer());

			// Switch targets
			_unit->GetAIInterface()->SwitchTarget(stalTarget, feugTarget);
			feug->GetAIInterface()->SwitchTarget(feugTarget, stalTarget);

			MoveTimer = AddTimer(3000);
			script = (MoonScriptBossAI *)feug->GetScript();
			if (script)
			{
				((Feugen*)script)->AddMoveTimer();

				SetCanMove(false);
				script->SetCanMove(false);
			}
		}
	}

	void AIUpdate()
	{
		Creature *feug;
		Creature *creat;

		feug = ForceCreatureFind(CN_FEUGEN, 3508.14f, -2988.65f, 312.092f);
		if (feug && feug->isAlive() == false)
		{
			if (RespawnTimer == INVALIDATE_TIMER)
				RespawnTimer = AddTimer(5000);

			if (RespawnTimer != INVALIDATE_TIMER && IsTimerFinished(RespawnTimer) && IsAlive())
			{
				feug->Despawn(1, 0); // This will remove his corpse.
				SpawnCreature(CN_FEUGEN, 3508.14f, -2988.65f, 312.092f, 0.f, true);
				RespawnTimer = INVALIDATE_TIMER;
			}
		}

		if (feug && IsTimerFinished(MagneticPullTimer))
		{
			CastMagneticPull(feug);

			ResetTimer(MagneticPullTimer, 30000);
		}

		if (MoveTimer != INVALIDATE_TIMER && IsTimerFinished(MoveTimer))
		{
			SetCanMove(true);
			RemoveTimer(MoveTimer);
		}

		// Lightning Rods: Initially stands near a lightning rod.
		// If Stalagg is pulled away from these rods, he will Chain Lightning the raid
		creat = ForceCreatureFind(CN_TESLA_COIL, 3487.571289f, -2911.448975f, 318.761841f);
		if (creat != NULL)
		{
			float dist;

			creat->CastSpell(_unit, SPELL_COSMETIC_CHAIN_LIGHTNING, true);

			dist = _unit->CalcDistance(creat);
			if (dist > 60.f)
				CastSpell(ChainLightning);
		}

		ParentClass::AIUpdate();
	}

	SpellDesc *ChainLightning;
	int32 MagneticPullTimer;
	int32 MoveTimer;
	int32 RespawnTimer;
};

class Thaddius : public MoonScriptBossAI
{
	MOONSCRIPT_FACTORY_FUNCTION(Thaddius, MoonScriptBossAI);
	Thaddius(Creature *pCreature) : MoonScriptBossAI(pCreature)
	{
		SpellDesc *ChainLightning;

		Berserk = AddSpell2(SPELL_THADDIUS_BERSERK, Target_Self);
		Ball = AddSpell2(SPELL_THADDIUS_BALL_LIGHTNING, Target_RandomPlayer);

		if (Is25PlayerNormalRaid())
		{
			SetMaxMana(160000);
			SetMana(160000);
			ChainLightning = AddSpell2(SPELL_CHAIN_LIGHTNING_H, Target_Current, 15000, 0);
		}
		else
			ChainLightning = AddSpell2(SPELL_CHAIN_LIGHTNING, Target_Current, 15000, 0);

		ChainLightning->AddEmote("Now you feel pain!", Text_Yell, 8871);

		AddSpell2(SPELL_POLARITY_SHIFT, Target_Self, 30000, 0);

		spawnWights = true;
		mAvoidAIUpdateChanges = true;

		BerserkTimer = INVALIDATE_TIMER;
		BallTimer = INVALIDATE_TIMER;
		AggroTimer = INVALIDATE_TIMER;

		SetSelectable(true);
		StopCombat();
		started = false;

		RegisterAIUpdateEvent(1000);

		AddEmote(Event_OnCombatStart, "You are too late! I.. must.. obey!", Text_Yell, 8872);
		AddEmote(Event_OnDied, "Thank... you...", Text_Yell, 8870);
		AddEmote(Event_OnTargetDied, "Kill!", Text_Yell, 8867);
		AddEmote(Event_OnTargetDied, "EAT YOUR BONES!", Text_Yell, 8868);
		AddEmote(Event_OnTargetDied, "BREAK YOU!", Text_Yell, 8869);
		AddEmote(Event_OnTargetDied, "You die now!", Text_Yell, 8877);

		SpawnCreature(CN_TESLA_COIL, 3487.571289f, -2911.448975f, 318.761841f, 4.014108f, true);
		SpawnCreature(CN_TESLA_COIL, 3527.977295f, -2952.480957f, 318.761841f, 4.014108f, true);
		SpawnGameObject(GO_TESLA_STALAGG, 3487.571289f, -2911.448975f, 318.761841f, 4.014108f);
		SpawnGameObject(GO_TESLA_FEUGEN, 3527.977295f, -2952.480957f, 318.761841f, 4.014108f);
	}

	void OnCombatStart(Unit *pAttacker)
	{
		GameObject *go = ForceGameObjectFind(GO_THADDIUS_DOOR, 3421.86f, -3017.51f, 295.615f);
		if (go != NULL)
			go->OpenGO(false);

		BerserkTimer = AddTimer(360000);		//6mins
		BallTimer = AddTimer(3000);

		spawnWights = true;

		ParentClass::OnCombatStart(pAttacker);
	}

	void OnCombatStop(Unit *pTarget)
	{
		Player *plr = GetNearestAlivePlayer(platformField, PLATFORM_FIELD_LIST_SIZE);
		if (plr)
		{
			Attack(plr);
			return;
		}

		GameObject *go = ForceGameObjectFind(GO_THADDIUS_DOOR, 3421.86f, -3017.51f, 295.615f);
		if (go != NULL)
			go->OpenGO(true);

		StopCombat();
		RespawnWights();

		RemoveAuraOnPlayers(SPELL_POSITIVE_CHARGE);
		RemoveAuraOnPlayers(SPELL_POSITIVE_CHARGE_BUFF);
		RemoveAuraOnPlayers(SPELL_NEGATIVE_CHARGE);
		RemoveAuraOnPlayers(SPELL_NEGATIVE_CHARGE_BUFF);

		ParentClass::OnCombatStop(pTarget);
	}

	void OnDied(Unit *pKiller)
	{
		// Update script data
		Naxxramas *script = (Naxxramas *)GetInstanceScript(MAP_NAXXRAMAS);
		if (script != NULL)
		{
			script->CheckThaddius();
		}

		GameObject *portal = GetNearestGameObject(181232);
		if (portal)
			portal->SetState(0);

		SpawnGameObject(181576, 3539.02f, -2936.82f, 302.476f, 3.14159f, false);

		ParentClass::OnDied(pKiller);
	}

	void OnTargetDied(Unit *pTarget)
	{
		if (pTarget && pTarget->IsPlayer() == false)
			return;

		((Naxxramas*)_unit->GetMapMgr()->pInstance->script)->SetBossFlag(BOSS_PLAYER_KILLED);

		ParentClass::OnTargetDied(pTarget);
	}

	void RespawnWights()
	{
		if (spawnWights == false)
			return;

		Creature *Stalagg = ForceCreatureFind(CN_STALAGG, 3450.45f, -2931.42f, 312.091f);
		Creature *Feugen = ForceCreatureFind(CN_FEUGEN, 3508.14f, -2988.65f, 312.092f);

		if (Feugen == NULL || Feugen->isAlive() == false)
		{
			if (Feugen)
				Feugen->Despawn(1, 0);
			SpawnCreature(CN_FEUGEN, 3508.14f, -2988.65f, 312.092f, 2.37365f, true);
		}

		if (Stalagg == NULL || Stalagg->isAlive() == false)
		{
			if (Stalagg)
				Stalagg->Despawn(1, 0);
			SpawnCreature(CN_STALAGG, 3450.45f, -2931.42f, 312.091f, 5.49779f, true);
		}

		spawnWights = false;
	}

	void StopCombat()
	{
		SetCanEnterCombat(false);
		started = false;
	}

	void StartCombat()
	{
		SetCanEnterCombat(true);
	}

	void AIUpdate()
	{
		if (started == false)
		{
			Creature *Stalagg = ForceCreatureFind(CN_STALAGG, 3450.45f, -2931.42f, 312.091f);
			Creature *Feugen = ForceCreatureFind(CN_FEUGEN, 3508.14f, -2988.65f, 312.092f);

			// Start the combat whenever Feugen and Stallag are both dead
			if ((Feugen == NULL || Feugen->isAlive() == false) &&
				(Stalagg == NULL || Stalagg->isAlive() == false))
			{
				AggroTimer = AddTimer(15*1000);
				started = true;
			}
		}

		if (AggroTimer != INVALIDATE_TIMER && IsTimerFinished(AggroTimer))
		{
			AggroTimer = INVALIDATE_TIMER;
			StartCombat();
			AggroNearestAlivePlayer(platformField, PLATFORM_FIELD_LIST_SIZE);
		}

		if (IsTimerFinished(BallTimer) && BallTimer != INVALIDATE_TIMER)
		{
			Unit *unit = GetBestPlayerTarget(TargetFilter_Closest);
			if (unit == NULL || unit->CalcDistance(_unit) > 15.f)
				CastSpell(Ball);

			ResetTimer(BallTimer, 3000);
		}

		if (IsTimerFinished(BerserkTimer) && BerserkTimer != INVALIDATE_TIMER)
		{
			CastSpell(Berserk);
			BerserkTimer = INVALIDATE_TIMER;
		}

		ParentClass::AIUpdate();
	}

	int32 BerserkTimer;
	int32 BallTimer;
	int32 AggroTimer;
	SpellDesc *Berserk;
	SpellDesc *Ball;
	bool started;
	bool spawnWights;
};

class TestaCoil : public MoonScriptCreatureAI
{
	MOONSCRIPT_FACTORY_FUNCTION(TestaCoil, MoonScriptCreatureAI);

	TestaCoil(Creature *pCreature) : MoonScriptCreatureAI(pCreature)
	{
		SetCanEnterCombat(false);
		SetFlyMode(true);
	}
};

bool PolarityShift(uint32 i, Spell *spell)
{
	Player *target = spell->GetPlayerTarget();
	Unit *caster = spell->u_caster;

	if (caster == NULL || caster->IsCreature() == false ||
		target == NULL)
		return true;

	// Remove the possible auras before
	target->RemoveNegativeAura(SPELL_POSITIVE_CHARGE);
	target->RemoveAllAuras(SPELL_POSITIVE_CHARGE_BUFF);
	target->RemoveNegativeAura(SPELL_NEGATIVE_CHARGE);
	target->RemoveAllAuras(SPELL_NEGATIVE_CHARGE_BUFF);

	// Apply positive or negative with 50%
	target->CastSpell(target, Rand(50) ? SPELL_POSITIVE_CHARGE : SPELL_NEGATIVE_CHARGE, true);
	return true;
}

bool PositiveChargeCallback(Unit *caster, Player *target, void *userData)
{
	Spell *spell = (Spell *)userData;
	if (target->HasNegativeAura(SPELL_POSITIVE_CHARGE) == false)
		spell->AddTarget(target, 0);
	return true;
}

bool CountInRangePositivePlayersCB(Unit *caster, Player *target, void *userData)
{
	if (caster == NULL)
		return false;

	if (target == NULL || caster == target)
		return true;

	uint32 *count = (uint32 *)userData;

	if (target->HasAura(SPELL_POSITIVE_CHARGE))
		(*count)++;

	return true;
}

bool StackPositiveChargesCB(Object *obj, void *param)
{
	ASSERT(obj != NULL);

	Player *plr = obj->ToPlayer();
	uint32 count = 0;

	if (plr->IsInWorld() == false)
		return false;

	plr->DoForInRangePlayers(10.f, CountInRangePositivePlayersCB, (void *)&count);

	plr->RemoveAllAuras(SPELL_POSITIVE_CHARGE_BUFF);

	if (count > 0)
	{
		if (plr->IsIn25PlayerRaid())
			count = count > 10 ? 10 : count;
		else
			count = count > 3 ? 3 : count;

		plr->CastSpell(plr, SPELL_POSITIVE_CHARGE_BUFF, true);
		Aura *a = plr->FindAura(SPELL_POSITIVE_CHARGE_BUFF);
		if (a == NULL)
			return true;

		for (int i = 1; i < count; i++)
			a->AddStack();

		a->BuildAuraUpdate();
	}

	return true;
}

class PositiveCharge : public SpellScript
{
	void ExtraAuraEffect(Aura *aura, bool apply)
	{
		Player *p_target = aura->GetPlayerTarget();
		if (p_target == NULL)
			return;

		if (apply)
		{
			p_target->AddEvent2(OBJECT_EVENT_CALL_FUNC, (void*)StackPositiveChargesCB, NULL, 1000);
		}
		else
		{
			p_target->RemoveEventWithParam(OBJECT_EVENT_CALL_FUNC, (void*)StackPositiveChargesCB);
		}
	}
};

class PositiveChargeDamage : public SpellScript
{
public:
	bool TargetHandler(Spell *spell, uint32 i)
	{
		spell->DoForInRangeCasterPlayers(i, PositiveChargeCallback, (void*)spell);
		return true;
	}
};

bool CountInRangeNegativePlayersCB(Unit *caster, Player *target, void *userData)
{
	if (caster == NULL)
		return false;
	if (target == NULL || caster == target)
		return true;

	uint32 *count = (uint32 *)userData;

	if (target->HasAura(SPELL_NEGATIVE_CHARGE))
		(*count)++;

	return true;
}

bool StackNegativeChargesCB(Object *obj, void *param)
{
	ASSERT(obj != NULL);

	Player *plr = obj->ToPlayer();
	uint32 count = 0;

	if (plr->IsInWorld() == false)
		return false;

	plr->DoForInRangePlayers(10.f, CountInRangeNegativePlayersCB, (void *)&count);

	plr->RemoveAllAuras(SPELL_NEGATIVE_CHARGE_BUFF);

	if (count > 0)
	{
		if (plr->IsIn25PlayerRaid())
			count = count > 13 ? 13 : count;
		else
			count = count > 5 ? 5 : count;

		plr->CastSpell(plr, SPELL_NEGATIVE_CHARGE_BUFF, true);
		Aura *a = plr->FindAura(SPELL_NEGATIVE_CHARGE_BUFF);
		if (a == NULL)
			return true;

		for (int i = 1; i < count; i++)
			a->AddStack();

		a->BuildAuraUpdate();
	}

	return true;
}

bool NegativeChargeCallback(Unit *caster, Player *target, void *userData)
{
	Spell *spell = (Spell*)userData;
	if (target->HasNegativeAura(SPELL_NEGATIVE_CHARGE) == false)
		spell->AddTarget(target, 0);
	return true;
}

class NegativeCharge : public SpellScript
{
	void ExtraAuraEffect(Aura *aura, bool apply)
	{
		Player *p_target = aura->GetPlayerTarget();
		if (p_target == NULL)
			return;

		if (apply)
		{
			p_target->AddEvent2(OBJECT_EVENT_CALL_FUNC, (void*)StackNegativeChargesCB, NULL, 1000);
		}
		else
		{
			p_target->RemoveEventWithParam(OBJECT_EVENT_CALL_FUNC, (void*)StackNegativeChargesCB);
		}
	}
};

class NegativeChargeDamage : public SpellScript
{
public:
	bool TargetHandler(Spell *spell, uint32 i)
	{
		spell->DoForInRangeCasterPlayers(i, NegativeChargeCallback, (void*)spell);
		return true;
	}
};

class Tesla : public GameObjectAIScript
{
public:
	GAMEOBJECT_INIT_SCRIPT_DC(Tesla);
	void OnSpawn()
	{
		// Activate it (it will spin)
		SetState(0);
		SetFlags(GetFlags()-1);
	}
};

void Naxxramas::CheckThaddius()
{
	GameObject *go;

	// Thaddius's entry door
	go = _mapMgr->GetInterface()->GetGameObjectNearestCoords(3421.86f, -3017.51f, 295.615f, GO_THADDIUS_DOOR);
	if (go != NULL)
		go->OpenGO(true);

	// Construct Quarter portal ramp
	go = _mapMgr->GetInterface()->GetGameObjectNearestCoords(3019.93f, -3420.31f, 300.972f, GO_CONSTRUCT_PORTAL_RAMP);
	if (go != NULL)
		go->SetState(0);
}

void SetupThaddius(ScriptMgr *mgr)
{
	mgr->register_creature_script(CN_THADDIUS, &Thaddius::Create);
	mgr->register_creature_script(CN_FEUGEN, &Feugen::Create);
	mgr->register_creature_script(CN_STALAGG, &Stalagg::Create);
	mgr->register_creature_script(CN_TESLA_COIL, &TestaCoil::Create);

	mgr->register_gameobject_script(GO_TESLA_STALAGG, &Tesla::Create);
	mgr->register_gameobject_script(GO_TESLA_FEUGEN, &Tesla::Create);

	mgr->register_dummy_spell(SPELL_POLARITY_SHIFT, &PolarityShift);
	mgr->register_spell_script(SPELL_POSITIVE_CHARGE, new PositiveCharge);
	mgr->register_spell_script(SPELL_NEGATIVE_CHARGE, new NegativeCharge);
	mgr->register_spell_script(SPELL_POSITIVE_CHARGE_DAMAGE, new PositiveChargeDamage);
	mgr->register_spell_script(SPELL_NEGATIVE_CHARGE_DAMAGE, new NegativeChargeDamage);

	sSpellMgr.fixEffectTarget(SPELL_COSMETIC_CHAIN_LIGHTNING, 0, EFF_TARGET_SINGLE_ENEMY);
}
