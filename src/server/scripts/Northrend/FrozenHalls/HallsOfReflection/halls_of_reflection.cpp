/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "halls_of_reflection.h"

enum Yells
{
    /*INTRO - Pre Uther*/
    SAY_JAINA_INTRO_01                 = -1668001,
    SAY_SYLVANA_INTRO_01               = -1668021,
    SAY_JAINA_INTRO_02                 = -1668002,
    SAY_JAINA_INTRO_03                 = -1668003,
    SAY_SYLVANA_INTRO_03               = -1668022,
    SAY_JAINA_INTRO_04                 = -1668004,
    SAY_SYLVANA_INTRO_04               = -1668023,

    /*INTRO - Uther Dialog*/
    SAY_UTHER_A_01                     = -1668005, 
    SAY_UTHER_H_01                     = -1668024,
    SAY_JAINA_02                       = -1668006,
    SAY_SYLVANA_02                     = -1668025,
    SAY_UTHER_A_03                     = -1668007,
    SAY_UTHER_H_03                     = -1668026,
    SAY_JAINA_04                       = -1668008,
    SAY_SYLVANA_04                     = -1668027,
    SAY_UTHER_A_05                     = -1668009,
    SAY_UTHER_H_05                     = -1668028,
    SAY_JAINA_06                       = -1668010,
    SAY_SYLVANA_06                     = -1668029,
    SAY_UTHER_A_07                     = -1668011,
    SAY_UTHER_H_07                     = -1668030,
    SAY_JAINA_08                       = -1668012,
    SAY_SYLVANA_08                     = -1668031,
    SAY_UTHER_A_09                     = -1668013,
    SAY_UTHER_H_09                     = -1668032,
    SAY_JAINA_10                       = -1668014,
    SAY_UTHER_A_11                     = -1668015,
    SAY_UTHER_H_11                     = -1668033,
    SAY_JAINA_12                       = -1668017,
    SAY_SYLVANA_12                     = -1668034,
    SAY_UTHER_A_13                     = -1668016,
    SAY_UTHER_A_14                     = -1668018,
    SAY_JAINA_15                       = -1668019,

    /*INTRO - Lich King Arrive*/
    SAY_UTHER_A_16                     = -1668020,
    SAY_UTHER_H_16                     = -1668035,
    SAY_LICH_KING_17                   = -1668036,
    SAY_LICH_KING_18                   = -1668037,
    SAY_LICH_KING_19                   = -1668038,
    SAY_JAINA_20                       = -1668042,
    SAY_SYLVANA_20                     = -1668043,
    SAY_LICH_KING_A_21                 = -1594473,//
    SAY_LICH_KING_H_21                 = -1594474,//
    SAY_FALRIC_INTRO                   = -1668039,
    SAY_MARWYN_INTRO                   = -1668040,
    SAY_FALRIC_INTRO2                  = -1668041,

    /*INTRO - Pre Escape*/
    SAY_LICH_KING_AGGRO_A              = -1594477,
    SAY_LICH_KING_AGGRO_H              = -1594478,
    SAY_JAINA_AGGRO                    = -1594479,
    SAY_SYLVANA_AGGRO                  = -1594480,

    /*ESCAPE*/
    SAY_JAINA_WALL_01                  = -1594487,
    SAY_SYLVANA_WALL_01                = -1594488,
    SAY_JAINA_WALL_02                  = -1594489,
    SAY_SYLVANA_WALL_02                = -1594490,
    SAY_LICH_KING_WALL_02              = -1594491,
    SAY_LICH_KING_WALL_03              = -1594492,
    SAY_LICH_KING_WALL_04              = -1594493,
    SAY_JAINA_WALL_03                  = -1594494,
    SAY_JAINA_WALL_04                  = -1594495,
    SAY_SYLVANA_WALL_03                = -1594496,
    SAY_SYLVANA_WALL_04                = -1594497,
    SAY_JAINA_ESCAPE_01                = -1594498,
    SAY_JAINA_ESCAPE_02                = -1594499,
    SAY_SYLVANA_ESCAPE_01              = -1594500,
    SAY_SYLVANA_ESCAPE_02              = -1594501,
    SAY_JAINA_TRAP                     = -1594502,
    SAY_SYLVANA_TRAP                   = -1594503,
    SAY_MATHEAS_JAINA                  = -1594505,
    SAY_LICH_KING_END_01               = -1594506,
    SAY_LICH_KING_END_02               = -1594507,
    SAY_LICH_KING_END_03               = -1594508,
};

enum Spells
{
    // Pre Event
    SPELL_TAKE_FROSTMOURNE             = 72729,
    SPELL_FROSTMOURNE_DESPAWN          = 72726,
    SPELL_FROSTMOURNE_SOUNDS           = 70667,
    SPELL_CAST_VISUAL                  = 65633,  //Jaina And Sylavana cast this when summon uther.
    SPELL_BOSS_SPAWN_AURA              = 72712,  //Falric and Marwyn
    SPELL_UTHER_DESPAWN                = 70693,

    // Licht King Event
    SPELL_WINTER                       = 69780,
    SPELL_FURY_OF_FROSTMOURNE          = 70063,
    SPELL_SOUL_REAPER                  = 73797,
    SPELL_RAISE_DEAD                   = 69818,
    SPELL_ICE_PRISON                   = 69708,
    SPELL_DARK_ARROW                   = 70194,
    SPELL_ICE_BARRIER                  = 69787,
    SPELL_DESTROY_ICE_WALL_01          = 69784, //Jaina
    SPELL_DESTROY_ICE_WALL_02          = 70224, 
    SPELL_DESTROY_ICE_WALL_03          = 70225, //Sylvana
    SPELL_SUMMON_ICE_WALL              = 69784,
    SPELL_SYLVANA_JUMP                 = 68339,
    SPELL_SYLVANA_STEP                 = 69087,
    SPELL_SILENCE                      = 69413,
    SPELL_LICH_KING_CAST               = 57561,
    SPELL_FROSTMOURNE_VISUAL           = 73220,
    SPELL_SHIELD_DISRUPTION            = 58291,

    // Clones
    N_SPELL_BALEFUL_STRIKE             = 69933,
    H_SPELL_BALEFUL_STRIKE             = 70400,
    N_SPELL_SPIRIT_BURST               = 69900,
    H_SPELL_SPIRIT_BURST               = 73046,
};

enum Faction
{
    FACTION                            = 2076,
};

enum Creatures
{
    MOB_SPIRITUAL_REFLECTION           = 37107
};

enum Achievements
{
    ACHIEV_THE_HALLS_OF_REFLECTION_N   = 4518,
    ACHIEV_THE_HALLS_OF_REFLECTION_H   = 4521,
    ACHIEV_WERE_NOT_RETREATING         = 4526, // TimeRun
};

enum Gameobjects
{
    HORDE_CHEST_N                      = 202337,
    HORDE_CHEST_H                      = 202212,
};

enum DoAction
{
    ACTION_START_EVENT,
};

#define MAX_ENCOUNTER_TIME 6 * 60 * 1000 // 6 Min

class npc_jaina_and_sylvana_HRintro : public CreatureScript
{
public:
    npc_jaina_and_sylvana_HRintro() : CreatureScript("npc_jaina_and_sylvana_HRintro") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        InstanceScript* pInstance = pCreature->GetInstanceScript();

        if (!pInstance)
            return false;

        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->AI()->DoAction(ACTION_START_EVENT);
                break;
        }

        if(pPlayer->GetTeam() == ALLIANCE) 
            pInstance->SetData(DATA_LIDER, 1);
        else
            pInstance->SetData(DATA_LIDER, 2);

        pInstance->SetData64(DATA_ESCAPE_LIDER, pCreature->GetGUID());

        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        InstanceScript* pInstance = pCreature->GetInstanceScript();

        if(pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu( pCreature->GetGUID());

        switch(pCreature->GetEntry())
        {
            case NPC_JAINA:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Can you remove the sword?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                break;
            case NPC_SYLVANA: 
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Dark Lady, I think I hear Arthas coming. Whatever you're going to do, do it quickly.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                break;
        }

        pPlayer->PlayerTalkClass->SendGossipMenu(907,pCreature->GetGUID());
        return true;
    }

    struct npc_jaina_and_sylvana_HRintroAI : public ScriptedAI
    {
        npc_jaina_and_sylvana_HRintroAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = pCreature->GetInstanceScript();
        }

        void Reset()
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->SetStandState(UNIT_STAND_STATE_STAND);
            me->SetVisible(true);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            bSmall = false;

            // Closed Door
            if(pInstance)
               pInstance->SetData(DATA_START_ENCOUNTER, NOT_STARTED);

            // Frostmourne Reset
            /*Frostmourne = pInstance->GetData64(GO_FROSTMOURNE);
            if(GameObject* pFrostmourne = pInstance->instance->GetGameObject(Frostmourne))*/
            if (GameObject* pFrostmourne = pInstance->instance->GetGameObject(pInstance->GetData64(GO_FROSTMOURNE)))
            {
                pFrostmourne->SetGoState(GO_STATE_READY);
                pFrostmourne->SetPhaseMask(1, true);
            }
        }

        void JumpNextStep(uint32 Time)
        {
            StepTimer = Time;
            Step++;
        }

        void DoAction(const int32 actionId)
        {
            switch (actionId)
            {
                case ACTION_START_EVENT:
                    Event();
                    Step = 0;
                    JumpNextStep(100);
                    break;
            }
        }

        void Event()
        {
            switch(Step)
            {
                case 1:
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    JumpNextStep(2000);
                    break;
                case 2:
                    if(me->GetEntry() == NPC_JAINA)
                    {
                        DoScriptText(SAY_JAINA_INTRO_01, me);
                        JumpNextStep(5000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                    {
                        DoScriptText(SAY_SYLVANA_INTRO_01, me);
                        JumpNextStep(8000);
                    }
                    break;
                case 3: 
                    if(me->GetEntry() == NPC_JAINA)
                    {
                        DoScriptText(SAY_JAINA_INTRO_02, me);
                        JumpNextStep(5000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                        JumpNextStep(500);
                    break;
                case 4:
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    me->GetMotionMaster()->MovePoint(0, 5307.031f, 1997.920f, 709.341f);
                    JumpNextStep(10000);
                    break;
                case 5:
                    if(Creature* pTarget = me->SummonCreature(NPC_ALTAR_TARGET,5309.374f,2006.788f,711.615f,1.37f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,360000))
                    {
                        me->SetUInt64Value(UNIT_FIELD_TARGET, pTarget->GetGUID());
                        pTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    }
                    JumpNextStep(1000);
                    break;
                case 6:
                    if(me->GetEntry() == NPC_JAINA)
                    {
                        DoScriptText(SAY_JAINA_INTRO_03, me);
                        JumpNextStep(5000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                    {
                        DoScriptText(SAY_SYLVANA_INTRO_03, me);
                        JumpNextStep(6000);
                    }
                    break;
                case 7:
                    DoCast(me, SPELL_CAST_VISUAL);
                    if(me->GetEntry() == NPC_JAINA)
                        DoScriptText(SAY_JAINA_INTRO_04, me);
                    if(me->GetEntry() == NPC_SYLVANA)
                        DoScriptText(SAY_SYLVANA_INTRO_04, me);
                    JumpNextStep(3000);
                    break;
                case 8:
                    DoCast(me, SPELL_FROSTMOURNE_SOUNDS);
                    Frostmourne = pInstance->GetData64(GO_FROSTMOURNE);
                    if(GameObject* pFrostmourne = pInstance->instance->GetGameObject(Frostmourne))
                        pFrostmourne->SetGoState(GO_STATE_ACTIVE);
                    if(me->GetEntry() == NPC_JAINA)
                        JumpNextStep(12000);
                    if(me->GetEntry() == NPC_SYLVANA)
                        JumpNextStep(8000);
                    break;
                case 9:
                    if(Creature* Uther = me->SummonCreature(NPC_UTHER,5308.228f,2003.641f,709.341f,4.17f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,360000))
                    {
                        pUther = Uther;
                        Uther->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
                        me->SetUInt64Value(UNIT_FIELD_TARGET, Uther->GetGUID());
                        Uther->CastSpell(Uther, SPELL_BOSS_SPAWN_AURA, false);
                        if(me->GetEntry() == NPC_JAINA)
                        {
                            DoScriptText(SAY_UTHER_A_01, Uther);
                            JumpNextStep(3000);
                        }
                        if(me->GetEntry() == NPC_SYLVANA)
                        {
                            DoScriptText(SAY_UTHER_H_01, Uther);
                            JumpNextStep(10000);
                        }
                    }
                    break;
                case 10:
                    if(me->GetEntry() == NPC_JAINA)
                    {
                        DoScriptText(SAY_JAINA_02, me);
                        JumpNextStep(5000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                    {
                        DoScriptText(SAY_SYLVANA_02, me);
                        JumpNextStep(3000);
                    }
                    break;
                case 11:
                    if(me->GetEntry() == NPC_JAINA && pUther)
                    {
                        DoScriptText(SAY_UTHER_A_03, pUther);
                        JumpNextStep(7000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA && pUther)
                    {
                        DoScriptText(SAY_UTHER_H_03, pUther);
                        JumpNextStep(6000);
                    }
                    if(bSmall)
                        Step = 24;
                    break;
                case 12:
                    if(me->GetEntry() == NPC_JAINA)
                    {
                        DoScriptText(SAY_JAINA_04, me);
                        JumpNextStep(2000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                    {
                        DoScriptText(SAY_SYLVANA_04, me);
                        JumpNextStep(5000);
                    }
                    break;
                case 13:
                    if(me->GetEntry() == NPC_JAINA && pUther)
                    {
                        DoScriptText(SAY_UTHER_A_05, pUther);
                        JumpNextStep(10000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA && pUther)
                    {
                        DoScriptText(SAY_UTHER_H_05, pUther); 
                        JumpNextStep(19000);
                    }
                    break;
                case 14:
                    if(me->GetEntry() == NPC_JAINA)
                    {
                        DoScriptText(SAY_JAINA_06, me);
                        JumpNextStep(6000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                    {
                        DoScriptText(SAY_SYLVANA_06, me); 
                        JumpNextStep(2000);
                    }
                    break;
                case 15:
                    if(me->GetEntry() == NPC_JAINA && pUther)
                    {
                        DoScriptText(SAY_UTHER_A_07, pUther); 
                        JumpNextStep(12000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA && pUther)
                    {
                        DoScriptText(SAY_UTHER_H_07, pUther);
                        JumpNextStep(20000);
                    }
                    break;
                case 16:
                    if(me->GetEntry() == NPC_JAINA)
                    {
                        DoScriptText(SAY_JAINA_08, me); 
                        JumpNextStep(6000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                    {
                        DoScriptText(SAY_SYLVANA_08, me);
                        JumpNextStep(3000);
                    }
                    break;
                case 17:
                    if(me->GetEntry() == NPC_JAINA && pUther)
                    {
                        DoScriptText(SAY_UTHER_A_09, pUther);
                        JumpNextStep(12000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA && pUther)
                    {
                        DoScriptText(SAY_UTHER_H_09, pUther);
                        JumpNextStep(11000);
                    }
                    break;
                case 18:
                    if(me->GetEntry() == NPC_JAINA)
                    {
                        DoScriptText(SAY_JAINA_10, me);
                        JumpNextStep(11000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                        JumpNextStep(100);
                    break;
                case 19:
                    if(me->GetEntry() == NPC_JAINA && pUther)
                    {
                        DoScriptText(SAY_UTHER_A_11, pUther);
                        JumpNextStep(24000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA && pUther)
                    {
                        DoScriptText(SAY_UTHER_H_11, pUther);
                        JumpNextStep(9000);
                    }
                    break;
                case 20:
                    if(me->GetEntry() == NPC_JAINA)
                    {
                        DoScriptText(SAY_JAINA_12, me);
                        JumpNextStep(2000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                    {
                        DoScriptText(SAY_SYLVANA_12, me);
                        JumpNextStep(2100);
                    }
                    break;
                case 21:
                    if(me->GetEntry() == NPC_JAINA && pUther)
                    {
                        DoScriptText(SAY_UTHER_A_13, pUther); 
                        JumpNextStep(5000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                        JumpNextStep(100);
                    break;
                case 22:
                    if(me->GetEntry() == NPC_JAINA && pUther)
                    {
                        DoScriptText(SAY_UTHER_A_14, pUther); 
                        JumpNextStep(12000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                        JumpNextStep(100);
                    break;
                case 23:
                    if(me->GetEntry() == NPC_JAINA)
                    {
                        DoScriptText(SAY_JAINA_15, me);
                        JumpNextStep(2000);
                    }
                    if(me->GetEntry() == NPC_SYLVANA)
                        JumpNextStep(100);
                    break;
                case 24:
                    if(me->GetEntry() == NPC_JAINA && pUther)
                        DoScriptText(SAY_UTHER_A_16, pUther);
                    if(me->GetEntry() == NPC_SYLVANA && pUther)
                        DoScriptText(SAY_UTHER_H_16, pUther);
                    MainGate = pInstance->GetData64(GO_IMPENETRABLE_DOOR);
                    if(GameObject* pGate = pInstance->instance->GetGameObject(MainGate))
                        pGate->SetGoState(GO_STATE_ACTIVE);
                    if(Creature* LichKing = me->SummonCreature(NPC_LICH_KING,5362.469f,2062.342f,707.695f,3.97f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,360000))
                    {
                        pLichKing = LichKing;
                        LichKing->setActive(true);
                    }
                    JumpNextStep(1000);
                    break;
                case 25:
                    if(pUther)
                        pUther->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
                    if(pLichKing)
                    {
                        pLichKing->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pLichKing->AddUnitMovementFlag(MOVEMENTFLAG_WALKING); 
                        pLichKing->GetMotionMaster()->MovePoint(0, 5314.881f, 2012.496f, 709.341f);
                    }
                    JumpNextStep(3000);
                    break;
                case 26:
                    if(GameObject* pGate = pInstance->instance->GetGameObject(MainGate))
                        pGate->SetGoState(GO_STATE_READY);
                    JumpNextStep(7000);
                    break;
                case 27:
                    if(pUther)
                       pUther->CastSpell(pUther, SPELL_UTHER_DESPAWN, false);
                    JumpNextStep(500);
                    break;
                case 28:
                    if(pLichKing)
                       DoScriptText(SAY_LICH_KING_17, pLichKing);
                    if(pUther)
                       pUther->ForcedDespawn();
                    JumpNextStep(10000);
                    break;
                case 29:
                    if(pLichKing)
                       DoScriptText(SAY_LICH_KING_18, pLichKing);
                    JumpNextStep(5000);
                    break;
                case 30:
                    if(pLichKing)
                       pLichKing->CastSpell(pLichKing, SPELL_TAKE_FROSTMOURNE, false);
                    if(GameObject* pFrostmourne = pInstance->instance->GetGameObject(Frostmourne))
                        pFrostmourne->SetGoState(GO_STATE_READY);
                    JumpNextStep(1500);
                    break;
                case 31:
                    if(GameObject* pFrostmourne = pInstance->instance->GetGameObject(Frostmourne))
                        pFrostmourne->SetPhaseMask(0, true);
                    if(pLichKing)
                        pLichKing->CastSpell(pLichKing, SPELL_FROSTMOURNE_VISUAL, false);
                    me->RemoveAurasDueToSpell(SPELL_FROSTMOURNE_SOUNDS);
                    JumpNextStep(5000);
                    break;
                case 32:
                    if(pLichKing)
                        DoScriptText(SAY_LICH_KING_19, pLichKing);
                    JumpNextStep(9000);
                    break;
                case 33:
                    Falric = pInstance->GetData64(NPC_FALRIC);
                    Marwyn = pInstance->GetData64(NPC_MARWYN);
                    if(Creature* pFalric = pInstance->instance->GetCreature(Falric))
                    {
                        pFalric->RemoveAllAuras();
                        pFalric->SetVisible(true);
                        pFalric->CastSpell(pFalric, SPELL_BOSS_SPAWN_AURA, false);
                        pFalric->GetMotionMaster()->MovePoint(0, 5283.309f, 2031.173f, 709.319f);
                    }
                    if(Creature* pMarwyn = pInstance->instance->GetCreature(Marwyn))
                    {
                        pMarwyn->RemoveAllAuras();
                        pMarwyn->SetVisible(true);
                        pMarwyn->CastSpell(pMarwyn, SPELL_BOSS_SPAWN_AURA, false);
                        pMarwyn->GetMotionMaster()->MovePoint(0, 5335.585f, 1981.439f, 709.319f);
                    }
                    if(pLichKing)
                       pLichKing->GetMotionMaster()->MovePoint(0, 5402.286f, 2104.496f, 707.695f);
                    JumpNextStep(600);
                    break;
                case 34:
                    if(Creature* pFalric = ((Creature*)Unit::GetUnit(*me, Falric)))
                        DoScriptText(SAY_FALRIC_INTRO, pFalric);
                    if(Creature* pMarwyn = ((Creature*)Unit::GetUnit(*me, Marwyn)))
                        DoScriptText(SAY_MARWYN_INTRO, pMarwyn);
                    JumpNextStep(3000);
                    break;
                case 35:
                    if(GameObject* pGate = pInstance->instance->GetGameObject(MainGate))
                        pGate->SetGoState(GO_STATE_ACTIVE);
                    if(Creature* pFalric = ((Creature*)Unit::GetUnit(*me, Falric)))
                        DoScriptText(SAY_FALRIC_INTRO2, pFalric);
                    JumpNextStep(4000);
                    break;
                case 36:
                    if(me->GetEntry() == NPC_JAINA)
                        DoScriptText(SAY_JAINA_20, me);
                    if(me->GetEntry() == NPC_SYLVANA)
                        DoScriptText(SAY_SYLVANA_20, me);
                    me->GetMotionMaster()->MovePoint(0, 5443.880f, 2147.095f, 707.695f);
                    JumpNextStep(4000);
                    break;
                case 37:
                    if(pLichKing)
                    {
                        pLichKing->GetMotionMaster()->MovementExpired(false);
                        pLichKing->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        pLichKing->GetMotionMaster()->MovePoint(0, 5443.880f, 2147.095f, 707.695f);
                    }
                    if(me->GetEntry() == NPC_JAINA && pLichKing)
                        DoScriptText(SAY_LICH_KING_A_21, pLichKing);
                    if(me->GetEntry() == NPC_SYLVANA && pLichKing)
                        DoScriptText(SAY_LICH_KING_H_21, pLichKing);
                    JumpNextStep(8000);
                    break;
                case 38:
                    if(GameObject* pGate = pInstance->instance->GetGameObject(MainGate))
                        pGate->SetGoState(GO_STATE_READY); 
                    if (pInstance)
                    {
                        pInstance->SetData(TYPE_WAVE_COUNT, SPECIAL);
                        pInstance->SetData(DATA_START_ENCOUNTER, IN_PROGRESS);
                    }
                    JumpNextStep(5000);
                    break;
                case 39:
                    me->SetVisible(false);
                    me->DisappearAndDie();
                    if(pLichKing)
                       pLichKing->DisappearAndDie();
                    pInstance->SetData(TYPE_PHASE, 2);  
                    JumpNextStep(1000);
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if(!pInstance)
                return;

            if(StepTimer < diff)
                Event();
            else StepTimer -= diff;
        }

    private:
        InstanceScript* pInstance;
        uint32 StepTimer;
        uint32 Step;
        uint64 Frostmourne;
        uint64 MainGate;
        uint64 Falric;
        uint64 Marwyn;
        uint64 IceCrownDoor;
        Creature* pUther;
        Creature* pLichKing;
        bool bSmall;
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_jaina_and_sylvana_HRintroAI(pCreature);
    }
};

class npc_jaina_and_sylvana_HRextro : public CreatureScript
{
public:
    npc_jaina_and_sylvana_HRextro() : CreatureScript("npc_jaina_and_sylvana_HRextro") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
    {
        InstanceScript* pInstance = pCreature->GetInstanceScript();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->CLOSE_GOSSIP_MENU();
                ((npc_jaina_and_sylvana_HRextroAI*)pCreature->AI())->Start(false,true);
                pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                pCreature->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                pCreature->setActive(true);

                if(pInstance)
                {
                    pInstance->SetData64(DATA_ESCAPE_LIDER, pCreature->GetGUID());
                    pInstance->SetData(TYPE_LICH_KING, IN_PROGRESS);
                    pInstance->SetData(TYPE_PHASE, 5);
                }
                return true;
            default:
                return false;
        }
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        InstanceScript* pInstance = pCreature->GetInstanceScript();

        if(!pInstance)
            return false;

        if(pInstance->GetData(TYPE_LICH_KING) == DONE)
            return false;

        if(pCreature->isQuestGiver())
           pPlayer->PrepareQuestMenu( pCreature->GetGUID());

        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Los lasst uns fliehen!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

        return true;
    }

    struct npc_jaina_and_sylvana_HRextroAI : public npc_escortAI
    {
        npc_jaina_and_sylvana_HRextroAI(Creature *pCreature) : npc_escortAI(pCreature)
        {
            pInstance = pCreature->GetInstanceScript();
        }

        void Reset()
        {  
            if(!pInstance)
                return;

            if(pInstance->GetData(TYPE_LICH_KING) == IN_PROGRESS)
                return;

            Step = 0;
            StepTimer = 500;
            bFight = true;
            bEvent = false;
            WallTarget = 0;
            EncounterTimer = 0;

            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            if(me->GetEntry() == NPC_JAINA_OUTRO)
            {
                me->CastSpell(me, SPELL_ICE_BARRIER, false);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2HL);
            }
            if(pInstance->GetData(TYPE_LICH_KING) == DONE)
                me->SetVisible(false);

            pInstance->SetData(TYPE_PHASE, 3);
        }

        void AttackStart(Unit* who)
        {
            if(!who)
                return;

            if(me->GetEntry() != NPC_SYLVANA_OUTRO)
                return;

            if(pInstance->GetData(TYPE_LICH_KING) == IN_PROGRESS || bFight != true)
                return;

            npc_escortAI::AttackStart(who);
        }

        void JustDied(Unit* pKiller)
        {
            if(!pInstance)
                return;

            if(pInstance)
            {
               pInstance->SetData(TYPE_LICH_KING, NOT_STARTED);
               pInstance->SetData64(DATA_ESCAPE_LIDER, 0); // Nullcheck ist ein muss da sonst das bEvent Buggt
            }
            me->Respawn();
        }

        void WaypointReached(uint32 i)
        {
            switch(i)
            {
                case 3:
                    pInstance->SetData(TYPE_ICE_WALL_01, IN_PROGRESS);
                    if(GameObject* pGate = pInstance->instance->GetGameObject(pInstance->GetData64(GO_ICE_WALL_1)))
                    {
                        pGate->SetGoState(GO_STATE_READY);
                        IceWall = pGate->GetGUID();
                    }
                    break;
                case 4:
                    if(me->GetEntry() == NPC_JAINA_OUTRO)
                        DoScriptText(SAY_JAINA_WALL_01, me);
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                        DoScriptText(SAY_SYLVANA_WALL_01, me);
                    CastTimer = 1000;
                    HoldTimer = 120000;
                    SetEscortPaused(true);
                    if (Creature *pWallTarget = me->SummonCreature(NPC_ICE_WALL,me->GetPositionX(),me->GetPositionY(),me->GetPositionZ(),me->GetOrientation(),TEMPSUMMON_MANUAL_DESPAWN,720000))
                    {
                        WallTarget = pWallTarget->GetGUID();
                        pWallTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        if(me->GetEntry() == NPC_JAINA_OUTRO)
                            me->CastSpell(pWallTarget, SPELL_DESTROY_ICE_WALL_01, false);
                    }
                    bWallCast = true;
                    break;
                case 6:
                    pInstance->SetData(TYPE_ICE_WALL_02, IN_PROGRESS);
                    if (Creature* pWallTarget = pInstance->instance->GetCreature(WallTarget))
                    {
                        if(pWallTarget->isAlive())
                        {
                            pWallTarget->ForcedDespawn();
                            WallTarget = 0;
                        }
                    }
                    break;
                case 8:
                    if(me->GetEntry() == NPC_JAINA_OUTRO)
                        DoScriptText(SAY_JAINA_WALL_02, me);
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                        DoScriptText(SAY_SYLVANA_WALL_02, me);
                    CastTimer = 1000;
                    HoldTimer = 120000;
                    SetEscortPaused(true);
                    if (Creature *pWallTarget = me->SummonCreature(NPC_ICE_WALL,me->GetPositionX(),me->GetPositionY(),me->GetPositionZ(),me->GetOrientation(),TEMPSUMMON_MANUAL_DESPAWN,720000))
                    {
                        WallTarget = pWallTarget->GetGUID();
                        pWallTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        if(me->GetEntry() == NPC_JAINA_OUTRO)
                            me->CastSpell(pWallTarget, SPELL_DESTROY_ICE_WALL_01, false);
                    }
                    bWallCast = true;
                    break;
                case 9:
                    if(me->GetEntry() == NPC_JAINA_OUTRO)
                        DoScriptText(SAY_JAINA_ESCAPE_01, me);
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                        DoScriptText(SAY_SYLVANA_ESCAPE_01, me);
                    break;
                case 11:
                    pInstance->SetData(TYPE_ICE_WALL_03, IN_PROGRESS);
                    if (Creature* pWallTarget = pInstance->instance->GetCreature(WallTarget))
                    {
                        if(pWallTarget->isAlive())
                        {
                            pWallTarget->ForcedDespawn();
                            WallTarget = 0;
                        }
                    }
                    break;
                case 12:
                    if(me->GetEntry() == NPC_JAINA_OUTRO)
                        DoScriptText(SAY_JAINA_WALL_03, me);
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                        DoScriptText(SAY_SYLVANA_WALL_03, me);
                    CastTimer = 1000;
                    HoldTimer = 120000;
                    SetEscortPaused(true);
                    if (Creature *pWallTarget = me->SummonCreature(NPC_ICE_WALL,me->GetPositionX(),me->GetPositionY(),me->GetPositionZ(),me->GetOrientation(),TEMPSUMMON_MANUAL_DESPAWN,720000))
                    {
                        WallTarget = pWallTarget->GetGUID();
                        pWallTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        if(me->GetEntry() == NPC_JAINA_OUTRO)
                            me->CastSpell(pWallTarget, SPELL_DESTROY_ICE_WALL_01, false);
                    }
                    bWallCast = true;
                    break;
                case 13:
                    if(me->GetEntry() == NPC_JAINA_OUTRO)
                        DoScriptText(SAY_JAINA_ESCAPE_02, me);
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                        DoScriptText(SAY_SYLVANA_ESCAPE_02, me);
                    break;
                case 15:
                    pInstance->SetData(TYPE_ICE_WALL_04, IN_PROGRESS);
                    if (Creature* pWallTarget = pInstance->instance->GetCreature(WallTarget))
                    {
                        if(pWallTarget->isAlive())
                        {
                            pWallTarget->ForcedDespawn();
                            WallTarget = 0;
                        }
                    }
                    break;
                case 16:
                    if(me->GetEntry() == NPC_JAINA_OUTRO)
                        DoScriptText(SAY_JAINA_WALL_04, me);
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                        DoScriptText(SAY_SYLVANA_WALL_04, me);
                    CastTimer = 1000;
                    HoldTimer = 120000;
                    SetEscortPaused(true);
                    if (Creature *pWallTarget = me->SummonCreature(NPC_ICE_WALL,me->GetPositionX(),me->GetPositionY(),me->GetPositionZ(),me->GetOrientation(),TEMPSUMMON_MANUAL_DESPAWN,720000))
                    {
                        WallTarget = pWallTarget->GetGUID();
                        pWallTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        if(me->GetEntry() == NPC_JAINA_OUTRO)
                            me->CastSpell(pWallTarget, SPELL_DESTROY_ICE_WALL_01, false);
                    }
                    bWallCast = true;
                    break;
                case 19:
                    if(me->GetEntry() == NPC_JAINA_OUTRO)
                        DoScriptText(SAY_JAINA_TRAP, me);
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                        DoScriptText(SAY_SYLVANA_TRAP, me);
                    break;          
                case 20:
                    if (Creature* pWallTarget = pInstance->instance->GetCreature(WallTarget))
                    {
                        if(pWallTarget->isAlive())
                        {
                            pWallTarget->ForcedDespawn();
                            WallTarget = 0;
                        }
                    }
                    SetEscortPaused(true);
                    if(me->GetEntry() == NPC_JAINA_OUTRO)
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2HL);
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                        me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                    break;
            }
        }

        void MoveInLineOfSight(Unit* who)
        {
            if(!who || !pInstance)
                return;

            if(who->GetTypeId() != TYPEID_PLAYER)
                return;

            Player* pPlayer = (Player *)who;

            /*if(pPlayer->GetTeam() == ALLIANCE && me->GetEntry() == NPC_SYLVANA_OUTRO)
                return;

            if(pPlayer->GetTeam() == HORDE && me->GetEntry() == NPC_JAINA_OUTRO)
                return;*/

            if(me->IsWithinDistInMap(who, 50.0f)
                && pInstance->GetData(TYPE_FALRIC) == DONE && pInstance->GetData(TYPE_MARWYN) == DONE
                && pInstance->GetData(TYPE_FROST_GENERAL) == DONE && pInstance->GetData(TYPE_PHASE) == 3)
            {
                pPlayer = (Player *)who;
                bEvent = true;
                me->setFaction(FACTION);
                pInstance->SetData(TYPE_PHASE, 4);
            }
        }

        void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
        {
            if(!pInstance)
                return;

            if(pInstance->GetData(TYPE_LICH_KING) != IN_PROGRESS)
            {
                uiDamage = 0;
                return;
            }

            if(pInstance->GetData(TYPE_LICH_KING) == IN_PROGRESS && bWallCast == true)
            {
                HoldTimer = HoldTimer + 100;
                return;
            }
        }

        void JumpNextStep(uint32 Time)
        {
            StepTimer = Time;
            Step++;
        }

        void Intro()
        {
            switch(Step)
            {
                case 0:
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    LichKing = pInstance->GetData64(BOSS_LICH_KING);
                    pLichKing = pInstance->instance->GetCreature(LichKing);
                    JumpNextStep(100);
                    break;
                case 1:
                    if(pLichKing)
                    {
                        pLichKing->SetPhaseMask(65535, true);
                        if(me->GetEntry() == NPC_JAINA_OUTRO)
                            DoScriptText(SAY_LICH_KING_AGGRO_A, pLichKing);
                        if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                            DoScriptText(SAY_LICH_KING_AGGRO_H, pLichKing);
                        pLichKing->AI()->AttackStart(me);
                        me->AI()->AttackStart(pLichKing);
                    }
                    JumpNextStep(3000);
                    break; 
                case 2:
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                    {
                        bFight = false;
                        if(pLichKing)
                            me->GetMotionMaster()->MovePoint(0, (me->GetPositionX()-5)+rand()%10, (me->GetPositionY()-5)+rand()%10, me->GetPositionZ());
                        JumpNextStep(3000);
                    }
                    else
                        JumpNextStep(100);
                    break;
                case 3:
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                        bFight = true;
                    JumpNextStep(100);
                    break;
                case 4:
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                    {
                        if(pLichKing)
                            me->CastSpell(pLichKing, SPELL_SYLVANA_STEP, false);
                        JumpNextStep(3000);
                    }
                    else
                        JumpNextStep(100);
                    break;
                case 5:
                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                    {
                        bFight = false;
                        if(pLichKing)
                            me->GetMotionMaster()->MovePoint(0, (me->GetPositionX()-5)+rand()%10, (me->GetPositionY()-5)+rand()%10, me->GetPositionZ());
                        JumpNextStep(3000);
                    }
                    else
                        JumpNextStep(12000);
                    break;
                case 6:
                    bFight = true;

                    if(pLichKing) // Buggt Friert Jaina ein und somit ist das bEvent nicht Startbar
                      me->CastSpell(pLichKing, me->GetEntry() == NPC_JAINA_OUTRO ? SPELL_ICE_PRISON : SPELL_DARK_ARROW,true);

                    JumpNextStep(2500);
                    break; 
                case 7:
                   /*if(pLichKing && !pLichKing->HasAura(SPELL_ICE_PRISON))
                      pLichKing->CastSpell(pLichKing,me->GetEntry() == NPC_JAINA_OUTRO ? SPELL_ICE_PRISON : SPELL_DARK_ARROW,true);*/

                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                    me->AttackStop();

                    if(me->GetEntry() == NPC_JAINA_OUTRO)
                        DoScriptText(SAY_JAINA_AGGRO, me);

                    if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                        DoScriptText(SAY_SYLVANA_AGGRO, me);

                    JumpNextStep(3000);
                    break; 
                case 8:
                    me->GetMotionMaster()->MovePoint(0, 5577.187f, 2236.003f, 733.012f);
                    if(pLichKing)
                        me->SetUInt64Value(UNIT_FIELD_TARGET, pLichKing->GetGUID());
                    JumpNextStep(10000);
                    break; 
                case 9:
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    Count = 1;
                    JumpNextStep(100);
                    break; 
            }
        }

        void Outro()
        {
            switch(Step)
            {
                case 10:
                    LichKing = pInstance->GetData64(BOSS_LICH_KING);
                    pLichKing = pInstance->instance->GetCreature(LichKing);
                    pLichKing->RemoveAurasDueToSpell(74327);
                    /*me->CastSpell(me, SPELL_SHIELD_DISRUPTION,false);*/
                    /*me->RemoveAurasDueToSpell(74327);*/
                    JumpNextStep(5000);
                    break;
                case 11:
                    if(GameObject* pCave = pInstance->instance->GetGameObject(pInstance->GetData64(GO_CAVE)))
                        pCave->SetGoState(GO_STATE_READY);
                    /*me->CastSpell(me, SPELL_SHIELD_DISRUPTION,false);*/
                    me->GetMotionMaster()->MovePoint(0, 5258.911328f,1652.112f,784.295166f);
                    JumpNextStep(10000);
                    break;
                case 12:
                    if(pInstance)
                    {
                       pInstance->DoCompleteAchievement(DUNGEON_MODE(ACHIEV_THE_HALLS_OF_REFLECTION_N,ACHIEV_THE_HALLS_OF_REFLECTION_H));

                       if (EncounterTimer <= MAX_ENCOUNTER_TIME)
                           pInstance->DoCompleteAchievement(ACHIEV_WERE_NOT_RETREATING);
                    }
                    JumpNextStep(1000);
                    break;
                case 13:
                    if(pInstance)
                       pInstance->SetData(TYPE_LICH_KING, DONE);
                    me->SummonGameObject(DUNGEON_MODE(HORDE_CHEST_N, HORDE_CHEST_H), 5241.049805f, 1663.439941f, 784.294983f,0.56f,0,0,1,1,604800);
                    JumpNextStep(10000);
                    break;
                case 14:
                    me->GetMotionMaster()->MovePoint(0, 5240.66f, 1646.93f, 784.302f);
                    JumpNextStep(5000);
                    break;
                case 15:
                    me->SetOrientation(0.68f);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    QuestComplete();
                    JumpNextStep(5000);
                    break;
            }
        }

        void QuestComplete()
        {
            if(pInstance)
            {
                Map::PlayerList const &PlayerList = pInstance->instance->GetPlayers();
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                {
                    i->getSource()->KilledMonsterCredit(36955, 0);
                    i->getSource()->KilledMonsterCredit(37554, 0);
                }
            }
        }

        void UpdateEscortAI(const uint32 diff)
        {
            if(!pInstance || !bEvent)
                return;

            DoMeleeAttackIfReady();

            if(pInstance->GetData(TYPE_PHASE) == 4)
            {
                if(StepTimer < diff)
                    Intro();
                else
                    StepTimer -= diff;
            }

            if(pInstance->GetData(TYPE_LICH_KING) == SPECIAL
                && pInstance->GetData(TYPE_PHASE) != 6)       //End Cinematic
            {
                pInstance->SetData(TYPE_PHASE, 6);
                Step = 10;
            }

            if (pInstance->GetData(TYPE_PHASE) == 6)
            {
                if(StepTimer < diff)
                    Outro();
                else
                    StepTimer -= diff;
                return;
            }

            if(bWallCast == true && CastTimer < diff)
            {
                if(me->GetEntry() == NPC_SYLVANA_OUTRO)
                {
                   if (Creature* pWallTarget = pInstance->instance->GetCreature(WallTarget))
                        me->CastSpell(pWallTarget, SPELL_DESTROY_ICE_WALL_03, false);
                    CastTimer = 1000;
                }
            }
            else
                CastTimer -= diff;

            if(pInstance->GetData(TYPE_LICH_KING) == IN_PROGRESS)
                EncounterTimer += diff;

            if (bWallCast == true && HoldTimer < 120000 && (pInstance->GetData(DATA_SUMMONS) == 0) || !me->isInCombat())
            {
                bWallCast = false;
                me->InterruptNonMeleeSpells(false);
                SetEscortPaused(false);
                if(GameObject* pGate = pInstance->instance->GetGameObject(IceWall))
                    pGate->SetGoState(GO_STATE_ACTIVE); 
                ++Count;
                switch(Count)
                {
                    case 2:
                        if(GameObject* pGate = pInstance->instance->GetGameObject(pInstance->GetData64(GO_ICE_WALL_2)))
                        {
                            pGate->SetGoState(GO_STATE_READY);
                            if(pLichKing && pLichKing->isAlive())
                                DoScriptText(SAY_LICH_KING_WALL_02, pLichKing);
                            IceWall = pGate->GetGUID();
                        }
                        break;
                    case 3:
                        if(GameObject* pGate = pInstance->instance->GetGameObject(pInstance->GetData64(GO_ICE_WALL_3)))
                        {
                            pGate->SetGoState(GO_STATE_READY);
                            if(pLichKing && pLichKing->isAlive())
                                DoScriptText(SAY_LICH_KING_WALL_03, pLichKing);
                            IceWall = pGate->GetGUID();
                        }
                        break;
                    case 4:
                        if(GameObject* pGate = pInstance->instance->GetGameObject(pInstance->GetData64(GO_ICE_WALL_4)))
                        {
                            pGate->SetGoState(GO_STATE_READY);
                            if(pLichKing && pLichKing->isAlive())
                                DoScriptText(SAY_LICH_KING_WALL_04, pLichKing);
                            IceWall = pGate->GetGUID();
                        }
                        break;
                    case 5:
                        if(pLichKing && pLichKing->isAlive())
                        {
                            pLichKing->RemoveAurasDueToSpell(SPELL_WINTER);
                            pLichKing->SetSpeed(MOVE_WALK, 2.5f, true);
                            Step = 0;
                        }
                        break;
                }
            }
            else
            {
                HoldTimer -= diff;
                if (HoldTimer <= 0)
                    HoldTimer = 0;
            }

            return;
        }

    private:
        InstanceScript* pInstance;
        uint32 CastTimer;
        uint32 StepTimer;
        uint32 Step;
        uint32 Count;
        uint32 HoldTimer;
        uint32 ChestID;
        uint32 EncounterTimer;
        uint64 LichKing;
        uint64 JainaOrSylvanas;
        uint64 IceWall;
        uint64 WallTarget;
        Creature* pLichKing;
        bool bFight;
        bool bEvent;
        bool bPreFight;
        bool bWallCast;
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_jaina_and_sylvana_HRextroAI(pCreature);
    }
};

class npc_lich_king_hr : public CreatureScript
{
public:
    npc_lich_king_hr() : CreatureScript("npc_lich_king_hr") { }

    struct npc_lich_king_hrAI : public ScriptedAI
    {
        npc_lich_king_hrAI(Creature *pCreature) : ScriptedAI(pCreature){}

        void Reset(){}
        void JustDied(Unit* pKiller){}
        void AttackStart(Unit* who) 
        { 
            return;
        }
        void UpdateAI(const uint32 diff){}
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_lich_king_hrAI(pCreature);
    }
};

enum General_bEvent
{
    SAY_AGGRO                    = -1594519,
    SAY_DEATH                    = -1594520,

    N_SPELL_SHIELD_THROWN        = 69222,
    H_SPELL_SHIELD_THROWN        = 73076,

    SPELL_REFLECTION_GHOST       = 69861,
    SPELL_CLONE                  = 69828,
    SPELL_CLONE2                 = 69837,
    //SPELL_CLONE                = 45204
};

class npc_frostworn_general : public CreatureScript
{
public:
    npc_frostworn_general() : CreatureScript("npc_frostworn_general") { }

    struct npc_frostworn_generalAI : public ScriptedAI
    {
        npc_frostworn_generalAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = pCreature->GetInstanceScript();
        }

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            ShieldTimer = 5000;
            bHealth = false;

            if(pInstance)
               pInstance->SetData(TYPE_FROST_GENERAL, NOT_STARTED);
        }

        void JustDied(Unit* pKiller)
        {
            DoScriptText(SAY_DEATH, me);

            if(pInstance)
               pInstance->SetData(TYPE_FROST_GENERAL, DONE);
        }

        void MoveInLineOfSight(Unit* pWho) 
        {
            if (!pInstance)
                return;

            if (me->getVictim())
                return;

            if (pWho->GetTypeId() != TYPEID_PLAYER || pInstance->GetData(TYPE_MARWYN) != DONE || !me->IsWithinDistInMap(pWho, 20.0f)) 
                return;

            if (Player* pPlayer = (Player*)pWho)
                if (pPlayer->isGameMaster())
                    return;

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            AttackStart(pWho);
        }

        void EnterCombat(Unit* pVictim)
        {
            DoScriptText(SAY_AGGRO, me);

            DoZoneInCombat();

            if(pInstance)
               pInstance->SetData(TYPE_FROST_GENERAL, IN_PROGRESS);
        }

        void ClonePlayers()
        {
            if (Map* pMap = me->GetMap())
                if (pMap->IsDungeon())
                {
                    Map::PlayerList const &PlayerList = pMap->GetPlayers();

                    if (!PlayerList.isEmpty())
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                            if (i->getSource() && i->getSource()->isAlive())
                    if (Creature* pReflection = me->SummonCreature(MOB_SPIRITUAL_REFLECTION, i->getSource()->GetPositionX(),i->getSource()->GetPositionY(), i->getSource()->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
                    {
                       
                        i->getSource()->CastSpell(pReflection, SPELL_CLONE, true);
                        //pReflection->SetDisplayId(i->getSource()->GetDisplayId());
                        pReflection->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID,   i->getSource()->GetUInt32Value(PLAYER_VISIBLE_ITEM_16_ENTRYID));
                        pReflection->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+1, i->getSource()->GetUInt32Value(PLAYER_VISIBLE_ITEM_17_ENTRYID));
                        pReflection->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID+2, i->getSource()->GetUInt32Value(PLAYER_VISIBLE_ITEM_18_ENTRYID));
                        pReflection->AI()->DoZoneInCombat();
                    }
                }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if(!UpdateVictim())
                return;

            if(!bHealth)
            {
                if (HealthBelowPct(50))
                {
                    ClonePlayers();
                    bHealth = true;
                }
            }

            if(ShieldTimer < uiDiff)
            {
                if(Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1))
                   DoCast(pTarget, DUNGEON_MODE(N_SPELL_SHIELD_THROWN,H_SPELL_SHIELD_THROWN));
                ShieldTimer = urand(8000, 12000);
            }
            else ShieldTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }

    private:
        InstanceScript* pInstance;
        uint32 ShieldTimer;
        bool bHealth;
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_frostworn_generalAI(pCreature);
    }
};

class npc_Spiritual_Reflection : public CreatureScript
{
public:
    npc_Spiritual_Reflection() : CreatureScript("npc_Spiritual_Reflection") { }

    struct npc_Spiritual_ReflectionAI : public ScriptedAI
    {
        npc_Spiritual_ReflectionAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = pCreature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        uint32 uiBalefulStrikeTimer;

        void Reset()
        {
            uiBalefulStrikeTimer = 5000;
        }

        void EnterCombat(Unit* pVictim)
        {
            DoZoneInCombat();
        }

        void JustDied(Unit* pKiller)
        {
            DoCastAOE(DUNGEON_MODE(N_SPELL_SPIRIT_BURST, H_SPELL_SPIRIT_BURST));
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if(!UpdateVictim())
                return;

            if(uiBalefulStrikeTimer < uiDiff)
            {
                DoCastVictim(DUNGEON_MODE(N_SPELL_BALEFUL_STRIKE, H_SPELL_BALEFUL_STRIKE));
                uiBalefulStrikeTimer = urand(5000, 6000);
            }
            else uiBalefulStrikeTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_Spiritual_ReflectionAI(pCreature);
    }
};

enum TrashSpells
{
    // Ghostly Priest
    SPELL_SHADOW_WORD_PAIN                        = 72318,
    SPELL_CIRCLE_OF_DESTRUCTION                   = 72320,
    SPELL_COWER_IN_FEAR                           = 72321,
    SPELL_DARK_MENDING                            = 72322,

    // Phantom Mage
    SPELL_FIREBALL                                = 72163,
    SPELL_FLAMESTRIKE                             = 72169,
    SPELL_FROSTBOLT                               = 72166,
    SPELL_CHAINS_OF_ICE                           = 72121,
    SPELL_HALLUCINATION                           = 72342,

    // Phantom Hallucination (same as phantom mage + HALLUCINATION_2 when dies)
    SPELL_HALLUCINATION_2                         = 72344,

    // Shadowy Mercenary
    SPELL_SHADOW_STEP                             = 72326,
    SPELL_DEADLY_POISON                           = 72329,
    SPELL_ENVENOMED_DAGGER_THROW                  = 72333,
    SPELL_KIDNEY_SHOT                             = 72335,

    // Spectral Footman
    SPELL_SPECTRAL_STRIKE                         = 72198,
    SPELL_SHIELD_BASH                             = 72194,
    SPELL_TORTURED_ENRAGE                         = 72203,

    // Tortured Rifleman
    SPELL_SHOOT                                   = 72208,
    SPELL_CURSED_ARROW                            = 72222,
    SPELL_FROST_TRAP                              = 72215,
    SPELL_ICE_SHOT                                = 72268,
};

enum TrashbEvents
{
    EVENT_TRASH_NONE,

    // Ghostly Priest
    EVENT_SHADOW_WORD_PAIN,
    EVENT_CIRCLE_OF_DESTRUCTION,
    EVENT_COWER_IN_FEAR,
    EVENT_DARK_MENDING,

    // Phantom Mage
    EVENT_FIREBALL,
    EVENT_FLAMESTRIKE,
    EVENT_FROSTBOLT,
    EVENT_CHAINS_OF_ICE,
    EVENT_HALLUCINATION,

    // Shadowy Mercenary
    EVENT_SHADOW_STEP,
    EVENT_DEADLY_POISON,
    EVENT_ENVENOMED_DAGGER_THROW,
    EVENT_KIDNEY_SHOT,

    // Spectral Footman
    EVENT_SPECTRAL_STRIKE,
    EVENT_SHIELD_BASH,
    EVENT_TORTURED_ENRAGE,

    // Tortured Rifleman
    EVENT_SHOOT,
    EVENT_CURSED_ARROW,
    EVENT_FROST_TRAP,
    EVENT_ICE_SHOT,
};

class npc_ghostly_priest : public CreatureScript
{
public:
    npc_ghostly_priest() : CreatureScript("npc_ghostly_priest") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ghostly_priestAI(pCreature);
    }

    struct npc_ghostly_priestAI: public ScriptedAI
    {
        npc_ghostly_priestAI(Creature *c) : ScriptedAI(c)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SHADOW_WORD_PAIN, 8000); // TODO: adjust timers
            events.ScheduleEvent(EVENT_CIRCLE_OF_DESTRUCTION, 12000);
            events.ScheduleEvent(EVENT_COWER_IN_FEAR, 10000);
            events.ScheduleEvent(EVENT_DARK_MENDING, 20000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_SHADOW_WORD_PAIN:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_SHADOW_WORD_PAIN);
                        events.ScheduleEvent(EVENT_SHADOW_WORD_PAIN, 8000);
                        return;
                    case EVENT_CIRCLE_OF_DESTRUCTION:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_CIRCLE_OF_DESTRUCTION);
                        events.ScheduleEvent(EVENT_CIRCLE_OF_DESTRUCTION, 12000);
                        return;
                    case EVENT_COWER_IN_FEAR:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_COWER_IN_FEAR);
                        events.ScheduleEvent(EVENT_COWER_IN_FEAR, 10000);
                        return;
                    case EVENT_DARK_MENDING:
                        // find an ally with missing HP
                        if (Unit *pTarget = DoSelectLowestHpFriendly(40, DUNGEON_MODE(30000,50000)))
                        {
                            DoCast(pTarget, SPELL_DARK_MENDING);
                            events.ScheduleEvent(EVENT_DARK_MENDING, 20000);
                        }
                        else
                        {
                            // no friendly unit with missing hp. re-check in just 5 sec.
                            events.ScheduleEvent(EVENT_DARK_MENDING, 5000);
                        }
                        return;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

};

class npc_phantom_mage : public CreatureScript
{
public:
    npc_phantom_mage() : CreatureScript("npc_phantom_mage") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_phantom_mageAI(pCreature);
    }

    struct npc_phantom_mageAI: public ScriptedAI
    {
        npc_phantom_mageAI(Creature *c) : ScriptedAI(c)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_FIREBALL, 3000); // TODO: adjust timers
            events.ScheduleEvent(EVENT_FLAMESTRIKE, 6000);
            events.ScheduleEvent(EVENT_FROSTBOLT, 9000);
            events.ScheduleEvent(EVENT_CHAINS_OF_ICE, 12000);
            events.ScheduleEvent(EVENT_HALLUCINATION, 40000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 bEventId = events.ExecuteEvent())
            {
                switch(bEventId)
                {
                    case EVENT_FIREBALL:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_FIREBALL);
                        events.ScheduleEvent(EVENT_FIREBALL, 15000);
                        return;
                    case EVENT_FLAMESTRIKE:
                        DoCast(SPELL_FLAMESTRIKE);
                        events.ScheduleEvent(EVENT_FLAMESTRIKE, 15000);
                        return;
                    case EVENT_FROSTBOLT:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_FROSTBOLT);
                        events.ScheduleEvent(EVENT_FROSTBOLT, 15000);
                        return;
                    case EVENT_CHAINS_OF_ICE:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_CHAINS_OF_ICE);
                        events.ScheduleEvent(EVENT_CHAINS_OF_ICE, 15000);
                        return;
                    case EVENT_HALLUCINATION:
                        DoCast(SPELL_HALLUCINATION);
                        return;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

};

class npc_phantom_hallucination : public CreatureScript
{
public:
    npc_phantom_hallucination() : CreatureScript("npc_phantom_hallucination") { }

    struct npc_phantom_hallucinationAI : public npc_phantom_mage::npc_phantom_mageAI
    {
        npc_phantom_hallucinationAI(Creature *c) : npc_phantom_mage::npc_phantom_mageAI(c)
        {
        }

        void JustDied(Unit * /*pWho*/)
        {
            DoCast(SPELL_HALLUCINATION_2);
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_phantom_hallucinationAI(pCreature);
    }
};

class npc_shadowy_mercenary : public CreatureScript
{
public:
    npc_shadowy_mercenary() : CreatureScript("npc_shadowy_mercenary") { }

    struct npc_shadowy_mercenaryAI: public ScriptedAI
    {
        npc_shadowy_mercenaryAI(Creature *c) : ScriptedAI(c)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SHADOW_STEP, 8000); // TODO: adjust timers
            events.ScheduleEvent(EVENT_DEADLY_POISON, 5000);
            events.ScheduleEvent(EVENT_ENVENOMED_DAGGER_THROW, 10000);
            events.ScheduleEvent(EVENT_KIDNEY_SHOT, 12000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_SHADOW_STEP:
                        DoCast(SPELL_SHADOW_STEP);
                        events.ScheduleEvent(EVENT_SHADOW_STEP, 8000);
                        return;
                    case EVENT_DEADLY_POISON:
                        DoCast(me->getVictim(), SPELL_DEADLY_POISON);
                        events.ScheduleEvent(EVENT_DEADLY_POISON, 10000);
                        return;
                    case EVENT_ENVENOMED_DAGGER_THROW:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_ENVENOMED_DAGGER_THROW);
                        events.ScheduleEvent(EVENT_ENVENOMED_DAGGER_THROW, 10000);
                        return;
                    case EVENT_KIDNEY_SHOT:
                        DoCast(me->getVictim(), SPELL_KIDNEY_SHOT);
                        events.ScheduleEvent(EVENT_KIDNEY_SHOT, 10000);
                        return;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_shadowy_mercenaryAI(pCreature);
    }
};

class npc_spectral_footman : public CreatureScript
{
public:
    npc_spectral_footman() : CreatureScript("npc_spectral_footman") { }

    struct npc_spectral_footmanAI: public ScriptedAI
    {
        npc_spectral_footmanAI(Creature *c) : ScriptedAI(c)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SPECTRAL_STRIKE, 5000); // TODO: adjust timers
            events.ScheduleEvent(EVENT_SHIELD_BASH, 10000);
            events.ScheduleEvent(EVENT_TORTURED_ENRAGE, 15000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 bEventId = events.ExecuteEvent())
            {
                switch(bEventId)
                {
                    case EVENT_SPECTRAL_STRIKE:
                        DoCast(me->getVictim(), SPELL_SPECTRAL_STRIKE);
                        events.ScheduleEvent(EVENT_SPECTRAL_STRIKE, 5000);
                        return;
                    case EVENT_SHIELD_BASH:
                        DoCast(me->getVictim(), SPELL_SHIELD_BASH);
                        events.ScheduleEvent(EVENT_SHIELD_BASH, 5000);
                        return;
                    case EVENT_TORTURED_ENRAGE:
                        DoCast(SPELL_TORTURED_ENRAGE);
                        events.ScheduleEvent(EVENT_TORTURED_ENRAGE, 15000);
                        return;
                }
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_spectral_footmanAI(pCreature);
    }
};

class npc_tortured_rifleman : public CreatureScript
{
public:
    npc_tortured_rifleman() : CreatureScript("npc_tortured_rifleman") { }

    struct npc_tortured_riflemanAI  : public ScriptedAI
    {
        npc_tortured_riflemanAI(Creature *c) : ScriptedAI(c)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_SHOOT, 2000); // TODO: adjust timers
            events.ScheduleEvent(EVENT_CURSED_ARROW, 10000);
            events.ScheduleEvent(EVENT_FROST_TRAP, 1000);
            events.ScheduleEvent(EVENT_ICE_SHOT, 15000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_SHOOT:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_SHOOT);
                        events.ScheduleEvent(EVENT_SHOOT, 2000);
                        return;
                    case EVENT_CURSED_ARROW:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_CURSED_ARROW);
                        events.ScheduleEvent(EVENT_CURSED_ARROW, 10000);
                        return;
                    case EVENT_FROST_TRAP:
                        DoCast(SPELL_FROST_TRAP);
                        events.ScheduleEvent(EVENT_FROST_TRAP, 30000);
                        return;
                    case EVENT_ICE_SHOT:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_ICE_SHOT);
                        events.ScheduleEvent(EVENT_ICE_SHOT, 15000);
                        return;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_tortured_riflemanAI(pCreature);
    }
};

static Position DalaranInstanceTeleport =
{
    5807.911621f, 588.176147f, 660.939087f
};

#define DALARAN_MAP 571

class go_dalaran_hdr_portal : public GameObjectScript
{
public:
    go_dalaran_hdr_portal() : GameObjectScript("go_dalaran_hdr_portal") { }

    bool OnGossipHello(Player* pPlayer, GameObject* pGo)
    {
        InstanceScript* pInstance = pGo->GetInstanceScript();

        if (!pInstance)
            return false;

        pPlayer->TeleportTo(DALARAN_MAP,DalaranInstanceTeleport.GetPositionX(),DalaranInstanceTeleport.GetPositionY(),DalaranInstanceTeleport.GetPositionZ(),pPlayer->GetOrientation());
        return true;
    }
};

//202079
//UPDATE `gameobject_template` SET `ScriptName`='go_dalaran_hdr_portal' WHERE (`entry`='202079');

void AddSC_halls_of_reflection()
{
    new npc_jaina_and_sylvana_HRintro();
    new npc_jaina_and_sylvana_HRextro();
    new npc_lich_king_hr();
    new npc_frostworn_general();
    new npc_ghostly_priest();
    new npc_phantom_mage();
    new npc_phantom_hallucination();
    new npc_shadowy_mercenary();
    new npc_spectral_footman();
    new npc_tortured_rifleman();
    new npc_Spiritual_Reflection();
    new go_dalaran_hdr_portal();
}