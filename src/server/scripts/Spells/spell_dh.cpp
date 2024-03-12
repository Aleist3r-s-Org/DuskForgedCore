#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "AreaTriggerTemplate.h"
#include "AreaTriggerEntityScript.h"
#include "Player.h"
#include "SpellAuraEffects.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "SpellScript.h"
#include "ScriptMgr.h"
#include "TemporarySummon.h"
#include <G3D/Vector3.h>

enum DemonHunterSpells
{
    SPELL_DH_ANNIHILATION_MH                = 1420004,
    SPELL_DH_ANNIHILATION_OH                = 1420005,
    SPELL_DH_AURA_OF_FLAME_BUFF             = 1410044,
    SPELL_DH_AURA_OF_FLAME_TALENT           = 1410043,
    SPELL_DH_AURA_OF_PAIN_BUFF              = 1410042,
    SPELL_DH_AURA_OF_PAIN_TALENT            = 1410041,
    SPELL_DH_BACKDRAFT_IMMOLATION_AURA      = 1420088,
    SPELL_DH_BACKDRAFT_TALENT               = 1420019,
    SPELL_DH_BURNING_HATRED_PROC            = 1420023,
    SPELL_DH_BURNING_HATRED_TALENT          = 1420021,
    SPELL_DH_CHAOS_NOVA_PROC                = 1410036,
    SPELL_DH_CHAOS_NOVA_SPELL               = 1410035,
    SPELL_DH_CHAOS_STRIKE_MH                = 1410068,
    SPELL_DH_CHAOS_STRIKE_OH                = 1410069,
    SPELL_DH_CHAOS_STRIKE_SPELL             = 1410067,
    SPELL_DH_CRITICAL_CHAOS_AURA_PROC       = 1420029,
    SPELL_DH_CRITICAL_CHAOS_TALENT          = 1420028,
    SPELL_DH_DARKNESS_SPELL                 = 1410051,
    SPELL_DH_DARK_NIGHT_BUFF                = 1410057,
    SPELL_DH_DARK_NIGHT_TALENT              = 1410056,
    SPELL_DH_DEMONIC_MUZZLE_DEBUFF          = 1410065,
    SPELL_DH_DEMONIC_MUZZLE_TALENT          = 1410064,
    SPELL_DH_DESPAIR_DEBUFF                 = 1410014,
    SPELL_DH_DESPAIR_TALENT                 = 1410013,
    SPELL_DH_DOUBLE_JUMP_AURA_STATE         = 1410115,
    SPELL_DH_DOUBLE_JUMP_DIRECTIONAL        = 1410114,
    SPELL_DH_DOUBLE_JUMP_STATIONARY         = 1410113,
    SPELL_DH_DOUBLE_JUMP_TRIGGER            = 1410112,
    SPELL_DH_FAMINE_DEBUFF                  = 1430026,
    SPELL_DH_FAMINE_TALENT                  = 1430025,
    SPELL_DH_FEL_RUSH_AIR                   = 1410125,
    SPELL_DH_FEL_RUSH_GROUND                = 1410126,
    SPELL_DH_FRAILTY_TALENT                 = 1430033,
    SPELL_DH_FRAILTY_DEBUFF_AURA1           = 1430035,
    SPELL_DH_FRAILTY_EXPLOSION              = 1430034,
    SPELL_DH_FRAILTY_HEAL                   = 1430047,
    SPELL_DH_GLIDE_AURA_PERIODIC_TRIGGER    = 1410104,
    SPELL_DH_GLIDE_DURATION_AURA            = 1410103,
    SPELL_DH_GLIDE_KNOCKBACK                = 1410106,
    SPELL_DH_GLIDE_KNOCKBACK_PROC           = 1410105,
    SPELL_DH_GLIDE_SLOWFALL_PROC            = 1410136,
    SPELL_DH_GLUTTONY_DEBUFF                = 1410030,
    SPELL_DH_GLUTTONY_TALENT                = 1410029,
    SPELL_DH_IMMOLATION_AURA_SPELL          = 1410076,
    SPELL_DH_IMMOLATION_AURA_TRIGGER        = 1410135,
    SPELL_DH_IMP_IMMOLATION_AURA_DAMAGE     = 1410085,
    SPELL_DH_IMP_IMMOLATION_AURA_PASSIVE    = 1410084,
    SPELL_DH_INFERNAL_STRIKE_DAMAGE         = 1430030,
    SPELL_DH_INFERNAL_STRIKE_IMMUNITY_AURA  = 1430029,
    SPELL_DH_MASTERY_FELPACT_AURA           = 1430001,
    SPELL_DH_MASTERY_FELPACT_EXPLOSION      = 1430002,
    SPELL_DH_MASTERY_HAVOC1                 = 1420000,
    SPELL_DH_MASTERY_HAVOC2                 = 1420001,
    SPELL_DH_MASTERY_VENGEANCE1             = 1430000,
    SPELL_DH_METAMORPHOSIS_DAZE             = 1410110,
    SPELL_DH_METAMORPHOSIS_HAVOC            = 1420002,
    SPELL_DH_METAMORPHOSIS_SPELL            = 1410107,
    SPELL_DH_METAMORPHOSIS_STUN_DAMAGE      = 1410109,
    SPELL_DH_METAMORPHOSIS_TRANSFORM        = 1410108,
    SPELL_DH_METAMORPHOSIS_VENGEANCE        = 1430013,
    SPELL_DH_MOMENTUM_PROC                  = 1420017,
    SPELL_DH_MOMENTUM_TALENT                = 1420016,
    SPELL_DH_NEMESIS_BEASTS                 = 1410093,
    SPELL_DH_NEMESIS_CRITTERS               = 1410100,
    SPELL_DH_NEMESIS_DRAGONKINS             = 1410094,
    SPELL_DH_NEMESIS_DEMONS                 = 1410095,
    SPELL_DH_NEMESIS_ELEMENTALS             = 1410096,
    SPELL_DH_NEMESIS_GIANTS                 = 1410097,
    SPELL_DH_NEMESIS_HUMANOIDS              = 1410099,
    SPELL_DH_NEMESIS_MECHANICALS            = 1410101,
    SPELL_DH_NEMESIS_UNDEADS                = 1410098,
    SPELL_DH_PITCH_BLACK_BUFF               = 1410059,
    SPELL_DH_PITCH_BLACK_TALENT             = 1410058,
    SPELL_DH_PUNISH_THE_WEAK_PROC           = 1420101,
    SPELL_DH_PUNISH_THE_WEAK_SPELL          = 1420011,
    SPELL_DH_PUNISH_THE_WEAK_TALENT         = 1420100,
    SPELL_DH_SHATTERED_SOUL_PROC            = 1410083,
    SPELL_DH_SHEAR_MAIN                     = 1430014,
    SPELL_DH_SHIFTING_STEEL_PROC            = 1410039,
    SPELL_DH_SIGIL_OF_COMBUSTION_EXPLOSION  = 1410079,
    SPELL_DH_SIGIL_OF_FLAME_DUMMY           = 1430019,
    SPELL_DH_SIGIL_OF_FLAME_EXPLOSION       = 1410004,
    SPELL_DH_SIGIL_OF_FLAME_ENERGIZE        = 1410005,
    SPELL_DH_SIGIL_OF_FLAME_STUN            = 1430023,
    SPELL_DH_SIGIL_OF_MISERY_EXPLOSION      = 1410007,
    SPELL_DH_SIGIL_OF_SILENCE_EXPLOSION     = 1410016,
    SPELL_DH_SIGIL_OF_SUPRESSION_EXPLOSION  = 1410024,
    SPELL_DH_SLOTH_DEBUFF                   = 1410026,
    SPELL_DH_SLOTH_TALENT                   = 1410025,
    SPELL_DH_SMOTHER_TALENT                 = 1430022,
    SPELL_DH_SOUL_CRUSH_TALENT              = 1430000,
    SPELL_DH_SOUL_FRAGMENT                  = 1430010,
    SPELL_DH_STOKE_TALENT                   = 1430018,
    SPELL_DH_TORMENT_SPELL                  = 1410073,
    SPELL_DH_TORMENT_TAUNT                  = 1410074,
    SPELL_DH_TORMENTOR_DEBUFF               = 1410034,
    SPELL_DH_TORMENTOR_TALENT               = 1410033,
    SPELL_DH_TYRANT_FORM_PROC               = 1410046,
    SPELL_DH_TYRANT_FORM_TALENT             = 1410045,
    SPELL_DH_UNFORGIVING_PACT_SHIELD        = 1410061,
    SPELL_DH_UNFORGIVING_PACT_SPELL         = 1410060,
    SPELL_DH_VANITY_AURA_COMBAT             = 1410018,
    SPELL_DH_VANITY_AURA_OUT_OF_COMBAT      = 1410119,
    SPELL_DH_VANITY_INTERRUPT_REGEN         = 1410133,
    SPELL_DH_VANITY_TALENT                  = 1410017,
};

enum SpellBunnies
{
    NPC_DH_IMMOLATION_AURA_CASTER           = 1411000
};

class SpellDemonHunterCastFromSummonEvent : public BasicEvent
{
public:
    SpellDemonHunterCastFromSummonEvent(Unit* caster, Unit* target, uint32 summon, uint32 spellId) : _caster(caster), _target(target), _summon(summon), _spellId(spellId) {}
    bool Execute(uint64 /*time*/, uint32 /*diff*/) override
    {
        Creature* pSpawn = _caster->SummonCreature(_summon, _caster->GetPositionX(), _caster->GetPositionY(), _caster->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 1500);
        pSpawn->SetFaction(_caster->GetFaction());
        pSpawn->CastSpell(_target, _spellId, true);
        return true;
    }
private:
    Unit* _caster;
    Unit* _target;
    uint32 _summon;
    uint32 _spellId;
};

class SpellDemonHunterCastEvent : public BasicEvent
{
public:
    SpellDemonHunterCastEvent(Unit* caster, Unit* target, uint32 spellId) : _caster(caster), _target(target), _spellId(spellId) {}

    bool Execute(uint64 /*time*/, uint32 /*diff*/) override
    {
        _caster->CastSpell(_target, _spellId);
        return true;
    }

private:
    Unit* _caster;
    Unit* _target;
    uint32 _spellId;
};

// 1410078 - Sigil of Combustion
struct at_dh_sigil_of_combustion : public AreaTriggerAI
{
    at_dh_sigil_of_combustion(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnRemove() override
    {
        Unit* caster = at->GetCaster();

        if (!caster)
            return;

        caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_SIGIL_OF_COMBUSTION_EXPLOSION, true);

        for (uint8 i = 0; i < 3; ++i)
            caster->CastSpell(caster, SPELL_DH_SHATTERED_SOUL_PROC, true);
    }
};

// 1410003 - Sigil of Flame
struct at_dh_sigil_of_flame : public AreaTriggerAI
{
    at_dh_sigil_of_flame(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnRemove() override
    {
        Unit* caster = at->GetCaster();

        if (!caster)
            return;

        caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_SIGIL_OF_FLAME_EXPLOSION, true);
        caster->CastSpell(caster, SPELL_DH_SIGIL_OF_FLAME_ENERGIZE, true);

        if (caster->HasAura(SPELL_DH_STOKE_TALENT))
            caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_SIGIL_OF_FLAME_DUMMY, true);

        if (caster->HasAura(SPELL_DH_SMOTHER_TALENT))
            caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_SIGIL_OF_FLAME_STUN, true);

        if (caster->HasAura(SPELL_DH_FRAILTY_TALENT))
            caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_FRAILTY_EXPLOSION, true);
    }
};

// 1410006 - Sigil of Misery
struct at_dh_sigil_of_misery : public AreaTriggerAI
{
    at_dh_sigil_of_misery(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnRemove() override
    {
        Unit* caster = at->GetCaster();

        if (!caster)
            return;

        caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_SIGIL_OF_MISERY_EXPLOSION, true);

        if (caster->HasAura(SPELL_DH_DESPAIR_TALENT))
            caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_DESPAIR_DEBUFF, true);

        if (caster->HasAura(SPELL_DH_DEMONIC_MUZZLE_TALENT))
            caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_DEMONIC_MUZZLE_DEBUFF, true);
    }
};

// 1410015 - Sigil of Silence
struct at_dh_sigil_of_silence : public AreaTriggerAI
{
    at_dh_sigil_of_silence(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnRemove() override
    {
        Unit* caster = at->GetCaster();

        if (!caster)
            return;

        caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_SIGIL_OF_SILENCE_EXPLOSION, true);

        if (caster->HasAura(SPELL_DH_SLOTH_TALENT))
            caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_SLOTH_DEBUFF, true);

        if (caster->HasAura(SPELL_DH_DEMONIC_MUZZLE_TALENT))
            caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_DEMONIC_MUZZLE_DEBUFF, true);
    }
};

// 1410024 - Sigil of Supression
struct at_dh_sigil_of_supression : public AreaTriggerAI
{
    at_dh_sigil_of_supression(AreaTrigger* areatrigger) : AreaTriggerAI(areatrigger) { }

    void OnRemove() override
    {
        Unit* caster = at->GetCaster();

        if (!caster)
            return;

        caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_SIGIL_OF_SUPRESSION_EXPLOSION, true);

        if (caster->HasAura(SPELL_DH_DEMONIC_MUZZLE_TALENT))
            caster->CastSpell(at->GetPositionX(), at->GetPositionY(), at->GetPositionZ(), SPELL_DH_DEMONIC_MUZZLE_DEBUFF, true);
    }
};

// 1410035 - Chaos Nova
class spell_dh_chaos_nova : public SpellScript
{
    PrepareSpellScript(spell_dh_chaos_nova);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_CHAOS_NOVA_PROC,
                SPELL_DH_CHAOS_NOVA_SPELL
            });
    }

    void HandleOnEffectHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        uint32 procChance = sSpellMgr->GetSpellInfo(SPELL_DH_CHAOS_NOVA_SPELL)->Effects[EFFECT_2].CalcValue();

        if (irand(1, 100) <= procChance)
            caster->CastSpell(caster, SPELL_DH_CHAOS_NOVA_PROC, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_chaos_nova::HandleOnEffectHit, EFFECT_2, SPELL_EFFECT_DUMMY);
    }
};

// 1410036 - Chaos Nova
class spell_dh_chaos_nova_proc : public SpellScript
{
    PrepareSpellScript(spell_dh_chaos_nova_proc);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_CHAOS_NOVA_PROC
            });
    }

    void HandleOnEffectHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        uint32 healPct = sSpellMgr->GetSpellInfo(SPELL_DH_CHAOS_NOVA_PROC)->Effects[EFFECT_2].CalcValue();
        uint32 healAmount = round(CalculatePct(caster->GetMissingHealth(), healPct));

        SetHitHeal(healAmount);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_chaos_nova_proc::HandleOnEffectHit, EFFECT_1, SPELL_EFFECT_HEAL);
    }
};

// 1410067 - Chaos Strike
class spell_dh_chaos_strike : public SpellScript
{
    PrepareSpellScript(spell_dh_chaos_strike);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_ANNIHILATION_MH,
                SPELL_DH_ANNIHILATION_OH,
                SPELL_DH_CHAOS_STRIKE_MH,
                SPELL_DH_CHAOS_STRIKE_OH,
                SPELL_DH_CHAOS_STRIKE_SPELL,
                SPELL_DH_METAMORPHOSIS_HAVOC
            });
    }

    void HandleOnHitTarget(SpellEffIndex effIndex)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        /*if (caster->HasAura(SPELL_DH_METAMORPHOSIS_HAVOC))
        {
            PreventHitDefaultEffect(effIndex);

            uint32 triggerSpell = sSpellMgr->GetSpellInfo(SPELL_DH_CHAOS_STRIKE_SPELL)->Effects[effIndex].TriggerSpell;

            if (triggerSpell == SPELL_DH_CHAOS_STRIKE_MH)
                caster->CastSpell(target, SPELL_DH_ANNIHILATION_MH, true);
            else if (triggerSpell == SPELL_DH_CHAOS_STRIKE_OH)
                caster->CastSpell(target, SPELL_DH_ANNIHILATION_OH, true);
        }*/
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_chaos_strike::HandleOnHitTarget, EFFECT_0, SPELL_EFFECT_TRIGGER_SPELL);
        OnEffectHitTarget += SpellEffectFn(spell_dh_chaos_strike::HandleOnHitTarget, EFFECT_1, SPELL_EFFECT_TRIGGER_SPELL);
    }
};

// 1420029 - Critical Chaos
class spell_dh_critical_chaos : public SpellScript
{
    PrepareSpellScript(spell_dh_critical_chaos);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_CRITICAL_CHAOS_AURA_PROC,
                SPELL_DH_CRITICAL_CHAOS_TALENT
            });
    }

    void HandleBeforeHit(SpellMissInfo missInfo)
    {
        caster = GetCaster();

        if (caster->HasAura(SPELL_DH_CRITICAL_CHAOS_AURA_PROC))
        {
            duration = caster->GetAura(SPELL_DH_CRITICAL_CHAOS_AURA_PROC)->GetDuration();
        }
    }

    void HandleAfterHit()
    {
        if (caster && caster->HasAura(SPELL_DH_CRITICAL_CHAOS_AURA_PROC))
        {
            Aura* aura = caster->GetAura(SPELL_DH_CRITICAL_CHAOS_AURA_PROC);

            if (aura->GetStackAmount() > 1)
                aura->SetDuration(duration);
        }
    }

    void Register() override
    {
        BeforeHit += BeforeSpellHitFn(spell_dh_critical_chaos::HandleBeforeHit);
        AfterHit += SpellHitFn(spell_dh_critical_chaos::HandleAfterHit);
    }

private:
    Unit* caster;
    float duration = 0;
};

// 1410051 - Darkness
class spell_dh_darkness : public SpellScript
{
    PrepareSpellScript(spell_dh_darkness);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_DARKNESS_SPELL,
                SPELL_DH_DARK_NIGHT_BUFF,
                SPELL_DH_DARK_NIGHT_TALENT,
                SPELL_DH_PITCH_BLACK_BUFF,
                SPELL_DH_PITCH_BLACK_TALENT
            });
    }

    void HandleOnHit()
    {
        Unit* caster = GetCaster();

        if (caster->HasAura(SPELL_DH_DARK_NIGHT_TALENT))
            caster->CastSpell(caster, SPELL_DH_DARK_NIGHT_BUFF, true);

        if (caster->HasAura(SPELL_DH_PITCH_BLACK_TALENT))
            caster->CastSpell(caster, SPELL_DH_PITCH_BLACK_BUFF, true);
    }

    void Register() override
    {

    }
};

// 1410057 - Dark Night
class spell_dh_dark_night_proc : public SpellScript
{
    PrepareSpellScript(spell_dh_dark_night_proc);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_DARK_NIGHT_BUFF,
                SPELL_DH_DARK_NIGHT_TALENT
            });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([&](WorldObject const* target)
            {
                if (Unit const* unitTarget = target->ToUnit())
                {
                    int32 maxTargets = sSpellMgr->GetSpellInfo(SPELL_DH_DARK_NIGHT_TALENT)->GetEffect(EFFECT_0).CalcValue();

                    if (unitTarget == GetCaster())
                        return true;

                    if (targets.size() > maxTargets)
                        targets.resize(maxTargets);
                }
            });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dh_dark_night_proc::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
    }
};

// 1410112 - Double Jump
class spell_dh_double_jump : public SpellScript
{
    PrepareSpellScript(spell_dh_double_jump);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_DOUBLE_JUMP_AURA_STATE,
                SPELL_DH_DOUBLE_JUMP_DIRECTIONAL,
                SPELL_DH_DOUBLE_JUMP_STATIONARY,
                SPELL_DH_DOUBLE_JUMP_TRIGGER
            });
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();

        if (caster->IsMounted() || caster->GetVehicleBase() || caster->HasAura(SPELL_DH_DOUBLE_JUMP_AURA_STATE))
            return SPELL_FAILED_DONT_REPORT;

        return SPELL_CAST_OK;
    }

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        bool directional = false;

        if (caster->GetUnitMovementFlags() & MOVEMENTFLAG_FORWARD || caster->GetUnitMovementFlags() & MOVEMENTFLAG_BACKWARD
            || caster->GetUnitMovementFlags() & MOVEMENTFLAG_STRAFE_LEFT || caster->GetUnitMovementFlags() & MOVEMENTFLAG_STRAFE_RIGHT)
            directional = true;

        ChatHandler(caster->ToPlayer()->GetSession()).PSendSysMessage("Unit Movement Flags: %u", caster->GetUnitMovementFlags());

        if (directional)
            caster->CastSpell(caster, SPELL_DH_DOUBLE_JUMP_DIRECTIONAL, true);
        else
            caster->CastSpell(caster, SPELL_DH_DOUBLE_JUMP_STATIONARY, true);

        caster->CastSpell(caster, SPELL_DH_DOUBLE_JUMP_AURA_STATE, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_dh_double_jump::CheckCast);
        OnHit += SpellHitFn(spell_dh_double_jump::HandleOnHit);
    }
};

// 1410124 - Fel Rush   //TODO
class spell_dh_fel_rush : public SpellScript
{
    PrepareSpellScript(spell_dh_fel_rush);

    void HandleOnHit()
    {
        Unit* caster = GetCaster();

        if (caster->ToPlayer()->IsFalling() || caster->HasUnitState(UNIT_STATE_JUMPING))
            caster->CastSpell(caster, SPELL_DH_FEL_RUSH_AIR, true);
        else
            caster->CastSpell(caster, SPELL_DH_FEL_RUSH_GROUND, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dh_fel_rush::HandleOnHit);
    }
};

// 1410125 - Fel Rush   //TODO
class spell_dh_fel_rush_air : public AuraScript
{
    PrepareAuraScript(spell_dh_fel_rush_air);

    void HandleAuraApply()
    {
       
    }

    void HandleAuraRemove()
    {
        
    }

    void Register() override
    {
        OnAuraApply += AuraApplyFn(spell_dh_fel_rush_air::HandleAuraApply);
        OnAuraRemove += AuraRemoveFn(spell_dh_fel_rush_air::HandleAuraRemove);
    }
};

// 1410126 - Fel Rush   //TODO
class spell_dh_fel_rush_ground : public AuraScript
{
    PrepareAuraScript(spell_dh_fel_rush_ground);

    void HandleAuraApply()
    {
        
    }

    void HandleAuraRemove()
    {
        
    }

    void Register() override
    {
        OnAuraApply += AuraApplyFn(spell_dh_fel_rush_ground::HandleAuraApply);
        OnAuraRemove += AuraRemoveFn(spell_dh_fel_rush_ground::HandleAuraRemove);
    }
};

// 1430034 - Frailty
class spell_dh_frailty_explosion : public SpellScript
{
    PrepareSpellScript(spell_dh_frailty_explosion);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_FRAILTY_DEBUFF_AURA1,
                SPELL_DH_FRAILTY_EXPLOSION,
                SPELL_DH_SOUL_CRUSH_TALENT
            });
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (caster->HasAura(SPELL_DH_SOUL_CRUSH_TALENT))
        {
            for (uint32 i = SPELL_DH_FRAILTY_DEBUFF_AURA1; i < SPELL_DH_FRAILTY_DEBUFF_AURA1 + 12; ++i)
                if (!target->HasAura(i))
                {
                    caster->CastSpell(target, i, true);
                    break;
                }
        }
        else
            caster->CastSpell(target, SPELL_DH_FRAILTY_DEBUFF_AURA1, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_frailty_explosion::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 1430035-1430046 - Frailty
class spell_dh_frailty_debuf_aura : public AuraScript
{
    PrepareAuraScript(spell_dh_frailty_debuf_aura);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_FRAILTY_DEBUFF_AURA1,
                SPELL_DH_FRAILTY_HEAL
            });
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();

        Unit* caster = GetCaster();
        Unit* attacker = eventInfo.GetDamageInfo()->GetAttacker();
        AuraEffect* aurEff = caster->GetAura(SPELL_DH_FRAILTY_DEBUFF_AURA1)->GetEffect(EFFECT_0);
        int32 damageDone = eventInfo.GetDamageInfo()->GetDamage();
        int32 healing = CalculatePct(damageDone, aurEff->GetAmount());

        if (caster && attacker)
            if (caster->GetGUID() == attacker->GetGUID())
                caster->CastCustomSpell(SPELL_DH_FRAILTY_HEAL, SPELLVALUE_BASE_POINT0, healing, caster, true);
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_dh_frailty_debuf_aura::HandleProc);
    }
};

// 1410103 - Glide
class spell_dh_glide : public SpellScript
{
    PrepareSpellScript(spell_dh_glide);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_DOUBLE_JUMP_AURA_STATE,
                SPELL_DH_GLIDE_AURA_PERIODIC_TRIGGER,
                SPELL_DH_GLIDE_DURATION_AURA
            });
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();

        if (caster->IsMounted() || caster->GetVehicleBase() || !caster->HasAura(SPELL_DH_DOUBLE_JUMP_AURA_STATE))
            return SPELL_FAILED_DONT_REPORT;

        if (!caster->IsFalling())
            return SPELL_FAILED_NOT_ON_GROUND;

        return SPELL_CAST_OK;
    }

    void HandleCast()
    {
        Unit* caster = GetCaster();

        caster->m_Events.AddEvent(new SpellDemonHunterCastEvent(caster, caster, SPELL_DH_GLIDE_AURA_PERIODIC_TRIGGER), caster->m_Events.CalculateTime(750));
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_dh_glide::CheckCast);
        BeforeCast += SpellCastFn(spell_dh_glide::HandleCast);
    }
};

class spell_dh_glide_aura : public AuraScript
{
    PrepareAuraScript(spell_dh_glide_aura);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_GLIDE_AURA_PERIODIC_TRIGGER,
                SPELL_DH_GLIDE_DURATION_AURA,
                SPELL_DH_GLIDE_SLOWFALL_PROC
            });
    }

    void HandleOnRemove()
    {
        Unit* caster = GetCaster();

        if (caster->HasAura(SPELL_DH_GLIDE_AURA_PERIODIC_TRIGGER))
            caster->RemoveAura(SPELL_DH_GLIDE_AURA_PERIODIC_TRIGGER);

        if (caster->HasAura(SPELL_DH_GLIDE_SLOWFALL_PROC))
            caster->RemoveAura(SPELL_DH_GLIDE_SLOWFALL_PROC);
    }

    void Register() override
    {
        OnAuraRemove += AuraRemoveFn(spell_dh_glide_aura::HandleOnRemove);
    }
};

// 1410135 - Immolation Aura
class spell_dh_immolation_aura_trigger : public SpellScript
{
    PrepareSpellScript(spell_dh_immolation_aura_trigger);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_BURNING_HATRED_PROC,
                SPELL_DH_BURNING_HATRED_TALENT,
                SPELL_DH_AURA_OF_FLAME_BUFF,
                SPELL_DH_AURA_OF_FLAME_TALENT,
                SPELL_DH_AURA_OF_PAIN_BUFF,
                SPELL_DH_AURA_OF_PAIN_TALENT,
                SPELL_DH_BACKDRAFT_IMMOLATION_AURA,
                SPELL_DH_BACKDRAFT_TALENT,
                SPELL_DH_IMMOLATION_AURA_SPELL,
                SPELL_DH_IMMOLATION_AURA_TRIGGER
            });
    }

    void HandleOnHit()
    {
        Unit* caster = GetCaster();

        if (caster->HasAura(SPELL_DH_BACKDRAFT_TALENT))
        {
            if (!caster->HasAura(SPELL_DH_IMMOLATION_AURA_SPELL))
                caster->CastSpell(caster, SPELL_DH_IMMOLATION_AURA_SPELL, true);
            else       //Honk honk imma clown
                for (uint32 i = SPELL_DH_BACKDRAFT_IMMOLATION_AURA; i < SPELL_DH_BACKDRAFT_IMMOLATION_AURA + 12; ++i)
                    if (!caster->HasAura(i))
                    {
                        caster->CastSpell(caster, i, true);
                        break;
                    }

            uint32 chance = sSpellMgr->GetSpellInfo(SPELL_DH_BACKDRAFT_TALENT)->Effects[EFFECT_0].CalcValue();
            flag96 spellFlags = sSpellMgr->GetSpellInfo(SPELL_DH_IMMOLATION_AURA_TRIGGER)->SpellFamilyFlags;

            if (irand(1, 100) <= chance)
                caster->ToPlayer()->TriggerChargeRegen(spellFlags);
        }
        else
            caster->CastSpell(caster, SPELL_DH_IMMOLATION_AURA_SPELL, true);

        if (caster->HasAura(SPELL_DH_AURA_OF_FLAME_TALENT))
            caster->CastSpell(caster, SPELL_DH_AURA_OF_FLAME_BUFF, true);

        if (caster->HasAura(SPELL_DH_AURA_OF_PAIN_TALENT))
            caster->CastSpell(caster, SPELL_DH_AURA_OF_PAIN_BUFF, true);

        if (caster->HasAura(SPELL_DH_IMP_IMMOLATION_AURA_PASSIVE))
            caster->CastSpell(caster, SPELL_DH_IMP_IMMOLATION_AURA_DAMAGE, true);

        if (caster->HasAura(SPELL_DH_BURNING_HATRED_TALENT))
            caster->CastSpell(caster, SPELL_DH_BURNING_HATRED_PROC, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dh_immolation_aura_trigger::HandleOnHit);
    }
};

// 1430029 - Infernal Strike
class spell_dh_infernal_strike_immunity_aura : public AuraScript
{
    PrepareAuraScript(spell_dh_infernal_strike_immunity_aura);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_INFERNAL_STRIKE_DAMAGE,
                SPELL_DH_INFERNAL_STRIKE_IMMUNITY_AURA
            });
    }

    void HandleOnRemove()
    {
        Unit* caster = GetCaster();

        caster->CastSpell(caster, SPELL_DH_INFERNAL_STRIKE_DAMAGE, true);
    }

    void Register() override
    {
        OnAuraRemove += AuraRemoveFn(spell_dh_infernal_strike_immunity_aura::HandleOnRemove);
    }
};

// 1430030 - Infernal Strike
class spell_dh_infernal_strike_damage : public SpellScript
{
    PrepareSpellScript(spell_dh_infernal_strike_damage);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                
            });
    }
};

// 1430001 - Mastery: Felpact
class spell_dh_mastery_felpact_aura : public AuraScript
{
    PrepareAuraScript(spell_dh_mastery_felpact_aura);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_MASTERY_FELPACT_AURA,
                SPELL_DH_MASTERY_FELPACT_EXPLOSION
            });
    }

    void HandleOnRemove()
    {
        GetCaster()->CastSpell(GetCaster(), SPELL_DH_MASTERY_FELPACT_EXPLOSION, true);
    }

    void Register() override
    {
        OnAuraRemove += AuraRemoveFn(spell_dh_mastery_felpact_aura::HandleOnRemove);
    }
};

// 1420000 - Mastery: Inner Demon
class spell_dh_mastery_havoc_aura : public AuraScript
{
    PrepareAuraScript(spell_dh_mastery_havoc_aura);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_MASTERY_HAVOC1,
                SPELL_DH_MASTERY_HAVOC2
            });
    }

    void HandleOnApply()
    {
        GetCaster()->AddAura(SPELL_DH_MASTERY_HAVOC2, GetCaster());
    }

    void HandleOnRemove()
    {
        GetCaster()->RemoveAura(SPELL_DH_MASTERY_HAVOC2);
    }

    void Register() override
    {
        OnAuraApply += AuraApplyFn(spell_dh_mastery_havoc_aura::HandleOnApply);
        OnAuraRemove += AuraRemoveFn(spell_dh_mastery_havoc_aura::HandleOnRemove);
    }
};

// 1410109 - Metamorphosis
class spell_dh_metamorphosis_damage : public SpellScript
{
    PrepareSpellScript(spell_dh_metamorphosis_damage);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_METAMORPHOSIS_DAZE,
                SPELL_DH_METAMORPHOSIS_STUN_DAMAGE
            });
    }

    void HandleOnEffectHit(SpellEffIndex effIndex)
    {
        Unit* target = GetHitUnit();
        Unit* caster = GetCaster();

        if (target->GetTypeId() == TYPEID_PLAYER)
        {
            PreventHitEffect(effIndex);
            caster->CastSpell(target, SPELL_DH_METAMORPHOSIS_DAZE, true);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_metamorphosis_damage::HandleOnEffectHit, EFFECT_1, SPELL_EFFECT_APPLY_AURA);
    }
};

// 1410137 - Metamorphosis
class spell_dh_metamorphosis_immunity_aura : public AuraScript
{
    PrepareAuraScript(spell_dh_metamorphosis_immunity_aura);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_MASTERY_HAVOC1,
                SPELL_DH_MASTERY_VENGEANCE1,
                SPELL_DH_METAMORPHOSIS_HAVOC,
                SPELL_DH_METAMORPHOSIS_STUN_DAMAGE,
                SPELL_DH_METAMORPHOSIS_TRANSFORM,
                SPELL_DH_METAMORPHOSIS_VENGEANCE,
                SPELL_DH_TYRANT_FORM_PROC,
                SPELL_DH_TYRANT_FORM_TALENT,
            });
    }

    void HandleOnRemove()
    {
        Unit* caster = GetCaster();

        caster->CastSpell(caster, SPELL_DH_METAMORPHOSIS_STUN_DAMAGE, true);
        caster->CastSpell(caster, SPELL_DH_METAMORPHOSIS_TRANSFORM, true);

        if (caster->HasAura(SPELL_DH_MASTERY_HAVOC1))
            caster->CastSpell(caster, SPELL_DH_METAMORPHOSIS_HAVOC, true);

        if (caster->HasAura(SPELL_DH_TYRANT_FORM_TALENT))
            caster->CastSpell(caster, SPELL_DH_TYRANT_FORM_PROC, true);

        if (caster->HasAura(SPELL_DH_MASTERY_VENGEANCE1))
            caster->CastSpell(caster, SPELL_DH_METAMORPHOSIS_VENGEANCE, true);
    }

    void Register() override
    {
        OnAuraRemove += AuraRemoveFn(spell_dh_metamorphosis_immunity_aura::HandleOnRemove);
    }
};

// 1420016 - Momentum
class spell_dh_momentum_aura : public AuraScript
{
    PrepareAuraScript(spell_dh_momentum_aura);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_MOMENTUM_PROC,
                SPELL_DH_MOMENTUM_TALENT
            });
    }

    void HandleProc(ProcEventInfo& eventInfo)
    {
        Unit* caster = GetCaster();

        if (caster->HasAura(SPELL_DH_MOMENTUM_PROC))
        {
            uint8 stackAmount = caster->GetAura(SPELL_DH_MOMENTUM_PROC)->GetStackAmount();

            if (stackAmount && stackAmount >= 15)
                PreventDefaultAction();
        }
    }

    void Register() override
    {
        OnProc += AuraProcFn(spell_dh_momentum_aura::HandleProc);
    }
};

// 1410092 - Nemesis
class spell_dh_nemesis_aura : public AuraScript
{
    PrepareAuraScript(spell_dh_nemesis_aura);

    void HandleAfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetTargetApplication())
            return;
        if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_DEATH)
            return;

        Unit* target = GetTargetApplication()->GetTarget();
        uint32 type = target->GetCreatureType();
        int32 dur = GetTargetApplication()->GetBase()->GetDuration();
        Unit* caster = GetAura()->GetCaster();

        if (!caster || !target)
            return;

        int32 spellId = 0;

        switch (type)
        {
            case CREATURE_TYPE_BEAST:
                spellId = SPELL_DH_NEMESIS_BEASTS;
                break;
            case CREATURE_TYPE_CRITTER:
                spellId = SPELL_DH_NEMESIS_CRITTERS;
                break;
            case CREATURE_TYPE_DEMON:
                spellId = SPELL_DH_NEMESIS_DEMONS;
                break;
            case CREATURE_TYPE_DRAGONKIN:
                spellId = SPELL_DH_NEMESIS_DRAGONKINS;
                break;
            case CREATURE_TYPE_ELEMENTAL:
                spellId = SPELL_DH_NEMESIS_ELEMENTALS;
                break;
            case CREATURE_TYPE_GIANT:
                spellId = SPELL_DH_NEMESIS_GIANTS;
                break;
            case CREATURE_TYPE_HUMANOID:
                spellId = SPELL_DH_NEMESIS_HUMANOIDS;
                break;
            case CREATURE_TYPE_MECHANICAL:
                spellId = SPELL_DH_NEMESIS_MECHANICALS;
                break;
            case CREATURE_TYPE_UNDEAD:
                spellId = SPELL_DH_NEMESIS_UNDEADS;
                break;
            default:
                break;
        }

        if (spellId)
            if (Aura* aur = caster->AddAura(spellId, caster))
                aur->SetDuration(dur);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_dh_nemesis_aura::HandleAfterRemove, EFFECT_0, SPELL_AURA_MOD_SCHOOL_MASK_DAMAGE_FROM_CASTER, AURA_EFFECT_HANDLE_REAL);
    }
};

// 1410059 - Pitch Black
class spell_dh_pitch_black_proc : public SpellScript
{
    PrepareSpellScript(spell_dh_pitch_black_proc);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_PITCH_BLACK_BUFF,
                SPELL_DH_PITCH_BLACK_TALENT
            });
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([&](WorldObject const* target)
            {
                if (Unit const* unitTarget = target->ToUnit())
                {
                    int32 maxTargets = sSpellMgr->GetSpellInfo(SPELL_DH_PITCH_BLACK_TALENT)->GetEffect(EFFECT_0).CalcValue();

                    if (unitTarget == GetCaster())
                        return true;

                    if (targets.size() > maxTargets)
                        targets.resize(maxTargets);
                }
            });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dh_pitch_black_proc::FilterTargets, EFFECT_0, TARGET_UNIT_CASTER_AREA_RAID);
    }
};

// 1420100 - Punish the Weak
class spell_dh_punish_the_weak_talent_aura : public AuraScript
{
    PrepareAuraScript(spell_dh_punish_the_weak_talent_aura);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_PUNISH_THE_WEAK_PROC,
                SPELL_DH_PUNISH_THE_WEAK_SPELL,
                SPELL_DH_PUNISH_THE_WEAK_TALENT
            });
    }

    void HandleOnApply()
    {
        Unit* caster = GetCaster();

        if (caster->GetTypeId() == TYPEID_PLAYER)
            caster->ToPlayer()->learnSpell(SPELL_DH_PUNISH_THE_WEAK_SPELL);
    }

    void HandleOnRemove()
    {
        Unit* caster = GetCaster();

        if (caster->GetTypeId() == TYPEID_PLAYER)
            caster->ToPlayer()->removeSpell(SPELL_DH_PUNISH_THE_WEAK_SPELL, SPEC_MASK_ALL, false);

        if (caster->HasAura(SPELL_DH_PUNISH_THE_WEAK_PROC))
            caster->RemoveAura(SPELL_DH_PUNISH_THE_WEAK_PROC);
    }

    void Register() override
    {
        OnAuraApply += AuraApplyFn(spell_dh_punish_the_weak_talent_aura::HandleOnApply);
        OnAuraRemove += AuraRemoveFn(spell_dh_punish_the_weak_talent_aura::HandleOnRemove);
    }
};

// 1430014 - Shear
class spell_dh_shear : public SpellScript
{
    PrepareSpellScript(spell_dh_shear);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_METAMORPHOSIS_VENGEANCE,
                SPELL_DH_SHEAR_MAIN,
                SPELL_DH_SOUL_FRAGMENT
            });
    }

    void HandleOnHit()
    {
        Unit* caster = GetCaster();

        if (caster->HasAura(SPELL_DH_METAMORPHOSIS_VENGEANCE))
        {
            for (uint8 u = 0; u < 2; ++u)
                caster->CastSpell(caster, SPELL_DH_SOUL_FRAGMENT, true);
        }
        else
            caster->CastSpell(caster, SPELL_DH_SOUL_FRAGMENT, true);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_dh_shear::HandleOnHit);
    }
};

// 1410004 - Sigil of Misery
class spell_dh_sigil_of_misery_aura : public AuraScript
{
    PrepareAuraScript(spell_dh_sigil_of_misery_aura);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_FAMINE_DEBUFF,
                SPELL_DH_FAMINE_TALENT,
                SPELL_DH_SIGIL_OF_MISERY_EXPLOSION
            });
    }

    void HandleOnRemove()
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();

        if (caster->HasAura(SPELL_DH_FAMINE_TALENT))
            caster->CastSpell(target, SPELL_DH_FAMINE_DEBUFF, true);
    }

    void Register() override
    {
        OnAuraRemove += AuraRemoveFn(spell_dh_sigil_of_misery_aura::HandleOnRemove);
    }
};

// 1410073 - Torment
class spell_dh_torment : public SpellScript
{
    PrepareSpellScript(spell_dh_torment);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_TORMENT_SPELL,
                SPELL_DH_TORMENT_TAUNT,
                SPELL_DH_TORMENTOR_DEBUFF,
                SPELL_DH_TORMENTOR_TALENT
            });
    }

    void HandleOnHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();

        if (caster->HasAura(SPELL_DH_TORMENTOR_TALENT))
            caster->CastSpell(target, SPELL_DH_TORMENTOR_DEBUFF, true);
        else
            caster->CastSpell(target, SPELL_DH_TORMENT_TAUNT, true);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_dh_torment::HandleOnHit);
    }
};

// 1410034 - Tormentor
class spell_dh_tormentor : public SpellScript
{
    PrepareSpellScript(spell_dh_tormentor);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_TORMENTOR_DEBUFF
            });
    }

    void HandleAfterHit()
    {
        Unit* caster = GetCaster();
        Unit* target = GetHitUnit();
        uint32 attackerCount = target->getAttackers().size();

        if (attackerCount > 5)
            attackerCount = 5;

        caster->SetAuraStack(SPELL_DH_TORMENTOR_DEBUFF, target, attackerCount);
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_dh_tormentor::HandleAfterHit);
    }
};

// 1410051 - Turn the Tables
class spell_dh_turn_the_tables : public AuraScript
{
    PrepareAuraScript(spell_dh_turn_the_tables);

    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo({ spellInfo->GetEffect(EFFECT_0).TriggerSpell });
    }

    void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
    {
        PreventDefaultAction();

        Unit* caster = GetCaster();
        if (!caster)
            return;

        Unit* target = GetTarget();
        target->CastSpell((Unit*)nullptr, GetSpellInfo()->Effects[EFFECT_0].TriggerSpell, true, nullptr, aurEff, caster->GetGUID());
    }

    void Register() override
    {
        OnEffectProc += AuraEffectProcFn(spell_dh_turn_the_tables::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};

// 1410060 - Unforgiving Pact
class spell_dh_unforgiving_pact : public SpellScript
{
    PrepareSpellScript(spell_dh_unforgiving_pact);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_UNFORGIVING_PACT_SHIELD,
                SPELL_DH_UNFORGIVING_PACT_SPELL
            });
    }

    void HandleOnEffectHit(SpellEffIndex /*effIndex*/)
    {
        caster = GetCaster();
        int32 currHealthPct = sSpellMgr->GetSpellInfo(SPELL_DH_UNFORGIVING_PACT_SPELL)->Effects[EFFECT_1].CalcValue();
        damage = round(CalculatePct(caster->GetHealth(), currHealthPct));

        SetHitDamage(damage);
    }

    void HandleAfterHit()
    {
        int32 modPct = sSpellMgr->GetSpellInfo(SPELL_DH_UNFORGIVING_PACT_SHIELD)->Effects[EFFECT_1].CalcValue();
        damage = round(CalculatePct(damage, modPct));

        caster->CastCustomSpell(caster, SPELL_DH_UNFORGIVING_PACT_SHIELD, &damage, nullptr, nullptr, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_dh_unforgiving_pact::HandleOnEffectHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        AfterHit += SpellHitFn(spell_dh_unforgiving_pact::HandleAfterHit);
    }

private:
    Unit* caster;
    int32 damage;
};

// 1410017 - Vanity
class spell_dh_vanity_talent : public AuraScript
{
    PrepareAuraScript(spell_dh_vanity_talent);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo(
            {
                SPELL_DH_VANITY_TALENT,
                SPELL_DH_VANITY_AURA_COMBAT,
                SPELL_DH_VANITY_AURA_OUT_OF_COMBAT,
                SPELL_DH_VANITY_INTERRUPT_REGEN
            });
    }

    void HandleOnRemove()
    {
        Unit* caster = GetCaster();

        if (caster->HasAura(SPELL_DH_VANITY_AURA_COMBAT))
            caster->RemoveAura(SPELL_DH_VANITY_AURA_COMBAT);

        if (caster->HasAura(SPELL_DH_VANITY_AURA_OUT_OF_COMBAT))
            caster->RemoveAura(SPELL_DH_VANITY_AURA_OUT_OF_COMBAT);

        if (caster->HasAura(SPELL_DH_VANITY_INTERRUPT_REGEN))
            caster->RemoveAura(SPELL_DH_VANITY_INTERRUPT_REGEN);
    }

    void Register() override
    {
        OnAuraRemove += AuraRemoveFn(spell_dh_vanity_talent::HandleOnRemove);
    }
};

// xxxxxxx - Debug Script
class spell_debug : public SpellScript
{
    PrepareSpellScript(spell_debug);

    void HandleOnHit()
    {
        ChatHandler(GetCaster()->ToPlayer()->GetSession()).PSendSysMessage("Spell ID: %u", GetSpellInfo()->Id);
    }

    void Register() override
    {
        OnHit += SpellHitFn(spell_debug::HandleOnHit);
    }
};

void AddSC_demonhunter_spell_scripts()
{
    RegisterAreaTriggerAI(at_dh_sigil_of_combustion);
    RegisterAreaTriggerAI(at_dh_sigil_of_flame);
    RegisterAreaTriggerAI(at_dh_sigil_of_misery);
    RegisterAreaTriggerAI(at_dh_sigil_of_silence);
    RegisterAreaTriggerAI(at_dh_sigil_of_supression);
    RegisterSpellScript(spell_dh_chaos_nova);
    RegisterSpellScript(spell_dh_chaos_nova_proc);
    RegisterSpellScript(spell_dh_chaos_strike);
    RegisterSpellScript(spell_dh_critical_chaos);
    RegisterSpellScript(spell_dh_darkness);
    RegisterSpellScript(spell_dh_dark_night_proc);
    RegisterSpellScript(spell_dh_double_jump);
    RegisterSpellScript(spell_dh_fel_rush);
    RegisterSpellScript(spell_dh_fel_rush_air);
    RegisterSpellScript(spell_dh_fel_rush_ground);
    RegisterSpellScript(spell_dh_glide);
    RegisterSpellScript(spell_dh_glide_aura);
    RegisterSpellScript(spell_dh_immolation_aura_trigger);
    RegisterSpellScript(spell_dh_mastery_felpact_aura);
    RegisterSpellScript(spell_dh_mastery_havoc_aura);
    RegisterSpellScript(spell_dh_metamorphosis_damage);
    RegisterSpellScript(spell_dh_metamorphosis_immunity_aura);
    RegisterSpellScript(spell_dh_momentum_aura);
    RegisterSpellScript(spell_dh_nemesis_aura);
    RegisterSpellScript(spell_dh_pitch_black_proc);
    RegisterSpellScript(spell_dh_punish_the_weak_talent_aura);
    RegisterSpellScript(spell_dh_shear);
    RegisterSpellScript(spell_dh_sigil_of_misery_aura);
    RegisterSpellScript(spell_dh_torment);
    RegisterSpellScript(spell_dh_tormentor);
    RegisterSpellScript(spell_dh_turn_the_tables);
    RegisterSpellScript(spell_dh_unforgiving_pact);
    RegisterSpellScript(spell_dh_vanity_talent);
    RegisterSpellScript(spell_debug);
}
