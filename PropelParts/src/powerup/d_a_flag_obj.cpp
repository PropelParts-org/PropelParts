#include <kamek.h>
#include <constants/game_constants.h>

// Allow IF Event sprite to check for Hammer Suit when set to 6
kmWrite16(0x80936C9A, POWERUP_HAMMER_SUIT);
