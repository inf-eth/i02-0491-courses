/*
 * FrostScripts
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (C) 2008-2010 FrostEmu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _INSTANCE_SCRIPTS_BASE_H_
#define _INSTANCE_SCRIPTS_BASE_H_

#define INVALIDATE_TIMER			-1
#define DEFAULT_UPDATE_FREQUENCY	1000	//milliseconds
#define DEFAULT_DESPAWN_TIMER		2000	//milliseconds

#define MOONSCRIPT_FACTORY_FUNCTION(ClassName, ParentClassName) \
public: \
	CREATURE_INIT_SCRIPT(ClassName); \
	typedef ParentClassName ParentClass;

#define MOONSCRIPT_FACTORY_FUNCTION_CUSTOM(ClassName, ParentClassName) \
public: \
	CREATURE_INIT_SCRIPT_CUSTOM(ClassName); \
	typedef ParentClassName ParentClass;

#define MOONSCRIPT_GO_FACTORY_FUNCTION(ClassName, ParentClassName) \
public:	\
	GAMEOBJECT_INIT_SCRIPT(ClassName); \
	typedef ParentClassName ParentClass;

enum TargetType
{
	Target_Self,						//Target self (Note: doesn't always mean self, also means the spell can choose various target)
	Target_Current,						//Current highest aggro (attacking target)
	Target_SecondMostHated,				//Second highest aggro
	Target_Destination,					//Target is a destination coordinates (x, y, z)
	Target_Predefined,					//Pre-defined target unit
	Target_RandomPlayer,				//Random target player
	Target_RandomPlayerWithMana,		//Random target player with mana
	Target_RandomPlayerNotCurrent,		//Random target player, but not the current highest
	Target_RandomPlayerDestination,		//Random player destination coordinates (x, y, z)
	Target_RandomPlayerApplyAura,		//Random target player to self cast aura
	Target_RandomUnit,					//Random target unit (players, totems, pets, etc.)
	Target_RandomUnitNotCurrent,		//Random target unit (players, totems, pets, etc.), but not the current highest aggro
	Target_RandomDestination,			//Random destination coordinates (x, y, z)
	Target_RandomDestinationNotCurrent,	//Random destination coordinates (x, y, z)
	Target_RandomFriendly,				//Random friendly target unit
	Target_RandomFriendlyNotSelf,		//Random friendly target unit
	Target_WoundedPlayer,				//Random wounded player
	Target_WoundedUnit,					//Random wounded unit (players, totems, pets, etc.)
	Target_WoundedFriendly,				//Random wounded friendly target
	Target_ClosestPlayer,				//Closest target player
	Target_ClosestPlayerNotCurrent,		//Closest target player, but not the current highest aggro
	Target_ClosestUnit,					//Closest target unit (players, totems, pets, etc.)
	Target_ClosestUnitNotCurrent,		//Closest target unit (players, totems, pets, etc.), but not the current highest aggro
	Target_ClosestFriendly,				//Closest friendly target unit
	Target_ClosestCorpse,				//Closest unit corpse
	Target_RandomCorpse,				//Random unit corpse
	Target_RangedPlayer,				//Ranged player
	Target_RangedPlayerApplyAura,		//Ranged player to self cast it
	Target_RangedPlayerDestination,		//Ranged player destination coords
	Target_Healer,						//Chosen by class and certain talents
	Target_MeleePlayer,					//Player whose attacks are melee based
	Target_MeleePlayerApplyAura,		//Melee player to self cast it
	Target_MeleePlayerDestination,		//Melee player destination coords
};

enum TargetFilter
{
	TargetFilter_None				= 0,
	TargetFilter_Closest			= 1<<0,
	TargetFilter_Friendly			= 1<<1,
	TargetFilter_NotCurrent			= 1<<2,
	TargetFilter_Wounded			= 1<<3,
	TargetFilter_SecondMostHated	= 1<<4,
	TargetFilter_Aggroed			= 1<<5,
	TargetFilter_Corpse				= 1<<6,
	TargetFilter_WithMana			= 1<<7,
	TargetFilter_Hostile			= 1<<8,
	TargetFilter_NotSelf			= 1<<9,
	TargetFilter_Healer				= 1<<10,
	TargetFilter_Ranged				= 1<<11,
	TargetFilter_Melee				= 1<<12,
};

enum TextType
{
	Text_Say,
	Text_Yell,
	Text_Emote,
	Text_Boss_Emote,
};

enum EventType
{
	Event_OnCombatStart,
	Event_OnTargetDied,
	Event_OnDied,
	Event_OnTaunt,
	Event_OnWipe,
};

enum BehaviorType
{
	Behavior_Default,
	Behavior_Melee,
	Behavior_Ranged,
	Behavior_Spell,
	Behavior_Flee,
	Behavior_CallForHelp,
};

enum MoveType
{
	Move_None,
	Move_RandomWP,
	Move_CircleWP,
	Move_WantedWP,
	Move_DontMoveWP,
	Move_Quest,
	Move_ForwardThenStop,
};

enum MoveFlag
{
	Flag_Walk	= 0,
	Flag_Run	= 256,
	Flag_Fly	= 768,
};

struct EmoteDesc
{
	EmoteDesc(const char *pText, TextType pType, uint32 pSoundId, uint32 pEmoteChance)
	{
		mText = (pText && strlen(pText) > 0) ? pText : "";
		mType = pType;
		mSoundId = pSoundId;
		mEmoteChance = pEmoteChance;
	}

	std::string	mText;
	TextType	mType;
	uint32		mSoundId;
	uint32		mEmoteChance;
};

typedef struct
{
	float x, y, z, o;
	uint32 waittime;
} ssWaypoint;

typedef struct
{
	const char *Text;
	uint32 SoundId;
} emoteDesc;

class SpellDesc;
class MoonScriptCreatureAI;
class MoonScriptBossAI;

typedef void(*SpellFunc)(SpellDesc *pThis, MoonScriptCreatureAI *pCreatureAI, Unit *pTarget, TargetType pType);
typedef std::vector<EmoteDesc*> EmoteArray;
typedef std::vector<Player*> PlayerArray;
typedef std::vector<Unit*> UnitArray;
typedef std::vector<SpellDesc*> SpellDescArray;
typedef std::list<SpellDesc*> SpellDescList;
typedef std::pair<int32, SpellDesc*> PhaseSpellPair;
typedef std::vector<PhaseSpellPair> PhaseSpellArray;
typedef std::pair<int32, int32> TimerPair;
typedef std::vector<TimerPair> TimerArray;

typedef struct
{
	SpellDesc *spell;
	float minRange;
	float maxRange;
} rangedSpellDesc;

typedef struct
{
	UnitArray array;
	TargetFilter filter;
	MoonScriptCreatureAI *script;
} UnitArrayData;

typedef std::vector<rangedSpellDesc> RangedSpellArray;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class SpellDesc
class SpellDesc
{
public:
	SpellDesc(SpellEntry *pInfo, SpellFunc pFnc, TargetType pTargetType, float pChance, bool pStrictRange, const char *pText, TextType pTextType, uint32 pSoundId, uint32 pEmoteChance);
	virtual ~SpellDesc();

	EmoteDesc	*AddEmote(const char *pText, TextType pType = Text_Yell, uint32 pSoundId = 0, uint32 pEmoteChance = 100);
	void		AddBossEmote(const char *pText, uint32 pSoundId = 0);
	void		TriggerCooldown(uint32 pCurrentTime = 0);
	void		SetFirstTime(uint32 Value);

	SpellEntry*	mInfo;				//Spell Entry information (generally you either want a SpellEntry OR a SpellFunc, not both)
	SpellFunc	mSpellFunc;			//Spell Function to be executed (generally you either want a SpellEntry OR a SpellFunc, not both)
	TargetType	mTargetType;		//Target type (see enum above)
	float		mChance;			//Percent of the cast of this spell in a total of 100% of the attacks
	uint32		mFirstTime;			//First cast time
	uint32		mBaseTime;			//Base Time for spell to get cast
	uint32		mRandTime;			//Rand Time sums to BaseTime to get the actual time
	uint32		mCastTime;			//Duration of the spell cast (seconds). Zero means the spell is instant cast
	int32		mCooldown;			//Spell cooldown (seconds)
	float		mMinRange;			//Minimum range for spell to be cast
	float		mMaxRange;			//Maximum range for spell to be cast
	bool		mStrictRange;		//If true, creature won't run to (or away of) target, it will instead skip that attack
	EmoteArray	mEmotes;			//Emotes (random) shouted on spell cast
	EmoteDesc*	mBossEmote;			//Executes a boss emote next to a (random) emote above
	bool		mEnabled;			//True if the spell is enabled for casting, otherwise it will never be scheduled (useful for bosses with phases, etc.)
	uint32		mHardMode;			//Hard Mode only
	uint64		mPredefinedTarget;	//Pre-defined Target Unit (Only valid with target type Target_Predefined);

	//Those are not properties, they are data member used by the evaluation system
	uint32		mLastCastTime;		//Last time at which the spell casted (used to implement cooldown), set to 0
	int32		mTimeToCast;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class MoonScriptCreatureAI
class MoonScriptCreatureAI : public CreatureAIScript
{
public:
	MoonScriptCreatureAI(Creature *pCreature);
	virtual ~MoonScriptCreatureAI();

	//Movement
	bool					GetCanMove();
	void					SetCanMove(bool pCanMove);

	//Attack and Combat State
	void					SetDespawnWhenInactive(bool pValue);

	//Behavior
	void					SetBehavior(BehaviorType pBehavior);
	BehaviorType			GetBehavior();
	void					AggroNearestUnit(int pInitialThreat = 1);
	void					AggroRandomUnit(int pInitialThreat = 1);
	void					AggroNearestHostilePlayer();
	void					AggroNearestPlayer(int pInitialThreat = 1);
	void					AggroRandomPlayer(int pInitialThreat = 1);
	void					AggroRandomPlayer(struct Coords *cells, uint32 cellCount);
	void					AggroNearestAlivePlayer(struct Coords *cells, uint32 cellCount);
	void					AggroUnit(Unit *pUnit, int pInitialThreat = 1);
	void					FollowTarget(Unit *pTarget, float pAngle, float pDistance);
	void					FollowTarget(uint64 pTarget, float pAngle, float pDistance);

	//Environment
	float					GetRange(MoonScriptCreatureAI *pCreature);
	MoonScriptCreatureAI*	GetNearestCreature(uint32 pCreatureId = 0);
	MoonScriptCreatureAI*	GetNearestCreatureCoords(float X, float Y, float Z, uint32 pCreatureId);
	MoonScriptCreatureAI*	GetNearestCreatureCells(uint32 pCreatureId, struct Coords *cells, uint32 cellCount);
	MoonScriptCreatureAI*	GetCreature(uint64 pCreatureGUID);
	MoonScriptCreatureAI*	SpawnCreature(uint32 pCreatureId, float pX, float pY, float pZ, float pO = 0, bool pForceSameFaction = false);
	MoonScriptCreatureAI*	SpawnCreature(uint32 pCreatureId, coordsXYZO *coords, bool pForceSameFaction = false);
	MoonScriptCreatureAI*	SpawnCreature(uint32 pCreatureId, bool pForceSameFaction = false);
	MoonScriptCreatureAI*	SpawnCreatureAt(uint32 pCreatureId, Object *pObject, bool pForceSameFaction = false);
	MoonScriptCreatureAI*	SpawnCreatureIfNotFound(uint32 pCreatureId, float pX, float pY, float pZ, float pO = 0, bool pForceSameFaction = false);
	MoonScriptCreatureAI*	SpawnCreatureNearRadius(uint32 pCreatureId, float Radius, bool pForceSameFaction = false);
	MoonScriptCreatureAI*	ForceCreatureAIFind(uint32 pCreatureId, float pX, float pY, float pZ);
	MoonScriptCreatureAI*	ForceCreatureAIFind(uint32 pCreatureId);
	MoonScriptCreatureAI*	ForceCreatureAIFind(uint32 pCreatureId, struct Coords *cells, uint32 cellCount);

	//Spells
	void					_AddSpell(SpellDesc *Spell);
	SpellDesc*				AddSpell(uint32 spellId, TargetType pTargetType, float pChance, bool pStrictRange = false, const char *pText = NULL, TextType pTextType = Text_Yell, uint32 pSoundId = 0);
	SpellDesc*				AddSpell2(uint32 spellId, TargetType pTargetType, uint32 BaseTime = 0, uint32 RandTime = 0, const char *pText = NULL, TextType pTextType = Text_Yell, uint32 pSoundId = 0, uint32 pEmoteChance = 100);
	SpellDesc*				AddHardModeSpell2(uint32 spellId, TargetType pTargetType, uint32 HardMode, uint32 BaseTime = 0, uint32 RandTime = 0, const char *pText = NULL, TextType pTextType = Text_Yell, uint32 pSoundId = 0, uint32 pEmoteChance = 100);
	SpellDesc*				AddSpellFunc(SpellFunc pFnc, TargetType pTargetType, float pChance, bool pStrictRange = false, const char *pText = NULL, TextType pTextType = Text_Yell, uint32 pSoundId = 0);
	SpellDesc*				AddOnCombatStartSpell(uint32 spellId, TargetType pTargetType, uint32 BaseTime = 0, uint32 RandTime = 0, const char *pText = NULL, TextType pTextType = Text_Yell, uint32 pSoundId = 0);
	bool					CastSpell(uint32 spellId);
	bool					CastSpell(Unit *target, SpellDesc *spell, bool triggered);
	void					CastSpell(SpellDesc *spell);
	void					CastSpellTo(uint32 spellId, MoonScriptCreatureAI *target);
	void					CastSpellNowNoScheduling(SpellDesc *spell);
	void					CastSpellNowNoMeleeDelay(SpellDesc *spell);
	SpellDesc*				FindSpellById(uint32 spellId);
	SpellDesc*				FindSpellByFunc(SpellFunc pFnc);
	void					RemoveSpell(uint32 SpellId);
	void					TriggerCooldownOnAllSpells();
	void					CancelAllCooldowns();
	void					CancelAllSpells();
	void					ResetSpellTimers();

	//Emotes
	EmoteDesc*				AddEmote(EventType pEventType, const char *pText, TextType pType, uint32 pSoundId = 0, uint32 pEmoteChance = 100);
	void					RemoveEmote(EventType pEventType, EmoteDesc *pEmote);
	void					RemoveAllEmotes(EventType pEventType);
	void					Emote(EmoteDesc *pEmote);
	void					Emote(const char *pText, TextType pType = Text_Yell, uint32 pSoundId = 0);
	void					AddIntro(uint32 pDuration, const char *pText = NULL, TextType pType = Text_Say, uint32 pSoundId=0);

	//Timers
	uint32					AddTimer(int32 pDurationMillisec);
	int32					GetTimer(int32 pTimerId);
	void					RemoveTimer(int32& pTimerId);
	void					ResetTimer(int32 pTimerId, int32 pDurationMillisec);
	void					DelayTimer(int32 pTimerId, int32 pDelayMillisec);
	bool					IsTimerFinished(int32 pTimerId);
	void					CancelAllTimers();

	//Waypoints
	void					SetWaypointList(ssWaypoint *list, int count);
	void					SetWaypointList(ssWaypoint *list, int count, float angle, float distance, bool all=true);
	WayPoint*				CreateWaypoint(int pId, uint32 pWaittime, Coords pCoords);
	WayPoint*				CreateWaypoint(int pId, uint32 pWaittime, float x, float y, float z, float o);
	void					AddWaypoint(WayPoint *pWayPoint);
	void					ForceWaypointMove(uint32 pWaypointId);
	void					SetWaypointToMove(uint32 pWaypointId);
	void					ResumeWaypointMovement(uint32 pWaypointId = 0);
	void					StopWaypointMovement();
	void					SetMoveType(MoveType pMoveType);
	MoveType				GetMoveType();
	uint32					GetCurrentWaypoint();
	size_t					GetWaypointCount();
	bool					HasWaypoints();

	//Options
	void					SetAIUpdateFreq(uint32 pUpdateFreq);
	uint32					GetAIUpdateFreq();
	void					SetCustomData(uint32 pData);
	uint32					GetCustomData() const;

	// Internal
	void					_ValidateTarget(UnitArrayData *data, Unit *target);

	//Reimplemented Events
	virtual void			OnCombatStart(Unit *pTarget);
	virtual void			OnCombatStop(Unit *pTarget);
	virtual void			OnTargetDied(Unit *pTarget);
	virtual void			OnDied(Unit *pKiller);
	virtual uint32			GetPossessSpells(uint32 *list, int max);
	virtual void			AIUpdate();
	virtual void			Destroy();

protected:
	void					AddScheduledSpell(SpellDesc *spell);
	bool					IsSpellScheduled(SpellDesc *spell);
	bool					CastSpellInternal(SpellDesc *spell, uint32 pCurrentTime = 0, bool NoMeleeDelay = false);
	void					CastSpellOnTarget(Unit *pTarget, TargetType pType, SpellEntry *pEntry);
	int32					CalcSpellAttackTime(SpellDesc *spell);
	bool					CastSpellForced(SpellDesc *spell);

	bool					IsUnitInRange(Unit *pTarget, SpellDesc *spell);
	Unit*					GetTargetForSpell(SpellDesc *spell);
	Unit*					GetBestPlayerTarget(TargetFilter pFilter=TargetFilter_None);
	Unit*					GetBestUnitTarget(TargetFilter pFilter=TargetFilter_None);
	Unit*					ChooseBestTargetInArray(UnitArray& pTargetArray, TargetFilter pFilter);
	Unit*					GetNearestTargetInArray(UnitArray& pTargetArray);
	Unit*					GetSecondMostHatedTargetInArray(UnitArray& pTargetArray);
	bool					IsValidUnitTarget(Object *pObject, TargetFilter pFilter);

	void					RandomEmote(EmoteArray& pEmoteArray);

	map_t					mSpells;
	int32					mFuncCounter;
	SpellDescList			mQueuedSpells;
	map_t					mScheduledSpells;

	EmoteArray				mOnCombatStartEmotes;
	EmoteArray				mOnTargetDiedEmotes;
	EmoteArray				mOnDiedEmotes;
	EmoteArray				mOnTauntEmotes;
	EmoteArray				mOnWipeEmotes;

	TimerArray				mTimers;
	int32					mTimerIdCounter;
	uint32					mAIUpdateFrequency;
	uint32					mBaseAttackTime;
	bool					mDespawnWhenInactive;
	bool					mAvoidAIUpdateChanges;
	bool					mCanMove;
	uint32					mHardMode;
	uint32					mOnAggroSpell;
	uint32					mCustomData;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class MoonScriptBossAI
class MoonScriptBossAI : public MoonScriptCreatureAI
{
public:
	MoonScriptBossAI(Creature *pCreature);
	virtual ~MoonScriptBossAI();

	//Basic Interface
	SpellDesc*		AddPhaseSpell(int32 pPhase, SpellDesc *spell);
	SpellDesc*		AddPhaseMaskSpell(uint32 Mask, SpellDesc *spell);
	int32			GetPhase();
	void			SetPhase(int32 pPhase, SpellDesc *pPhaseChangeSpell = NULL);
	void			IncPhase();
	void			SetEnrageInfo(SpellDesc *spell, int32 pTriggerMilliseconds);

	//Reimplemented Events
	virtual void	OnCombatStart(Unit *pTarget);
	virtual void	OnCombatStop(Unit *pTarget);
	virtual void	AIUpdate();

protected:
	int32			mPhaseIndex;
	PhaseSpellArray	mPhaseSpells;
	SpellDesc*		mEnrageSpell;
	int32			mEnrageTimerDuration;
	int32			mEnrageTimer;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class MoonScriptRangedAI
class MoonScriptRangedAI : public MoonScriptCreatureAI
{
public:
	MoonScriptRangedAI(Creature *pCreature);
	virtual ~MoonScriptRangedAI();

	// Basic Interface
	void			AddRangedSpell(SpellDesc *spell, float minRange, float maxRange);
	void			AddOnRangeSpell(SpellDesc *spell, float range, float moveDistance);
	void			SetRanges(float meleeRange, float chaseRange);
	void			SetDisableRangedAI(bool bDisable);

	// Reimplemented Events
	virtual void	OnCombatStart(Unit *pTarget);
	virtual void	AIUpdate();
protected:
	float			mMeleeRange;
	float			mChaseRange;
	RangedSpellArray mRangedSpells;
	SpellDesc *		mInRangeSpell;
	float			mInRangeRange;
	bool			mCastedInRangeSpell;
	bool			mRangedAIDisabled;
	float			mInRangeMoveDistance;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class MoonScriptGameObjectAI
class MoonScriptGameObjectAI : public GameObjectAIScript
{
public:
	MoonScriptGameObjectAI(GameObject *go);
	virtual ~MoonScriptGameObjectAI();

	// Basic Interface
	void			SetOpeningTime(uint32 openingTime);
	void			SetRespawnTime(uint32 delay, uint32 respawnTime, bool shouldRespawn);
	void			SetInitialState(uint32 state);
	virtual void	OnReportUse(Player *plr);
	virtual void	OnSpawn();
	virtual void	AIUpdate();
protected:
	uint32			mOpeningTime;
	uint32			mRespawnTime;
	uint32			mDespawnTime;
	uint32			mPlayerGuid;
	uint32			mInitialState;
	bool			mShouldRespawn;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Premade Spell Functions
void SpellFunc_ClearHateList(SpellDesc *pThis, MoonScriptCreatureAI *pCreatureAI, Unit *pTarget, TargetType pType);
void SpellFunc_Disappear(SpellDesc *pThis, MoonScriptCreatureAI *pCreatureAI, Unit *pTarget, TargetType pType);
void SpellFunc_Reappear(SpellDesc *pThis, MoonScriptCreatureAI *pCreatureAI, Unit *pTarget, TargetType pType);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//STL Utilities
template <class Type> inline void DeleteArray(std::vector<Type> pVector)
{
	typename std::vector<Type>::iterator Iter = pVector.begin();
	for (; Iter != pVector.end(); ++Iter)
		delete (*Iter);

	pVector.clear();
}

//Warning: do not use if item can reside more than once in same vector
template <class Type> inline void DeleteItem(std::vector<Type> pVector, Type pItem)
{
	typename std::vector<Type>::iterator Iter = std::find(pVector.begin(), pVector.end(), pItem);
	if (Iter != pVector.end())
	{
		delete (*Iter);
		pVector.erase(Iter);
	}
}

// http://www.fredosaurus.com/notes-cpp/misc/random-shuffle.html
template <class Type> void ShuffleArray(Type Array[], uint32 nItemCount)
{
	for (uint32 i = 0; i < (nItemCount-1); i++)
	{
		uint32 r = i + RandomUInt(0, (nItemCount-1)-i);
		Type temp = Array[i];
		Array[i] = Array[r];
		Array[r] = temp;
	}
}

#endif /* _INSTANCE_SCRIPTS_BASE_H_ */

