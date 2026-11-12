// Port/BadgeEffects.h - badge accessories (native modding, not in the
// original): data/item/badges.txt in the game data or any enabled mod, lines
// "<item id> <effect>=<value> ...", '#' comments. While a player has such an
// item equipped its effects apply:
//   gravity, jump, speed  multipliers on the player module's fall/jump
//                         acceleration, jump launch speed and walk speed
//   defense               damage taken is divided by it
//   airControl=0          no steering in the air
//   oneHit=1              any damage kills the wearer
//   moonwalk=1            faces away from the walk direction
//   voicePitch            the wearer's voice pitch (1 = normal)
//   backdash, slide       multipliers on back dash and slide speed
//   speedSet, backdashSet, slideSet  the walk / back dash / slide bonus in %,
//                         replacing what the equipment gives (largest wins)
// The Unity remake difficulty mod (mods/unity_difficulty) uses it for the
// remake's Hell-clear badges.
#pragma once

struct BadgeEffects {
    float gravity;
    float jump;
    float speed;
    float defense;
    float voicePitch;
    int   airControl;   // 1 normal, 0 none
    int   oneHit;
    int   moonwalk;
    float backdash;     // back dash speed x (native modding)
    float slide;        // crouching slide speed x
    float speedSet;     // > 0: walk speed bonus in % in place of the equipment's own (a mod overriding an item)
    float backdashSet;  // > 0: back dash bonus in % in place of the equipment's own
    float slideSet;     // > 0: slide bonus in % in place of the equipment's own
};

// The effects of everything in an equipment block (PlayerObject::m_equipment).
void badgeEffectsForEquipment(void* equipment, BadgeEffects* out);

// PlayerObject::lateUpdate: remembers which equipment belongs to which player
// module object, for the module query below.
void badgeRegisterPlayer(const void* playerModule, void* equipment);

// Exported from the exe for the player modules (Dll/Player/PlayerBadge.cpp):
//   extern "C" void cvhdPlayerBadges(const void* playerModule, BadgeEffects* out)
