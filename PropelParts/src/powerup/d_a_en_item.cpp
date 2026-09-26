#include <kamek.h>
#include <game/bases/d_a_player.hpp>
#include <game/bases/d_a_en_item.hpp>

// Fix "Mushroom if small" behavior
kmWrite32(0x80A2BE98, 0x28000003);
kmWrite32(0x80A28598, 0x28000003);

// Inject hammer item brres string
kmWritePointer(0x80AF0FA8, "g3d/I_hammer.brres");

// Inject hammer item arc name
kmWritePointer(0x80AF0ECC, "I_hammer");

// Inject hammer item model name
kmWritePointer(0x80AF1000, "I_hammer");

// Allow EN_ITEM to transform players into custom powers

// Return values matter here
// 0 = no custom powerup was checked
// 1 = the player has the powerup currently checked
// 2 = player was given powerup (failed)
// 3 = player was given powerup (success)
int PowerupCheck_Custom(int enItem_power, int player_power, dAcPy_c *player) {
    if (enItem_power == 5) { // Hammer suit
        if (player_power == POWERUP_HAMMER_SUIT) {
            // Player already has hammer suit
            return 1;
        }
        if (player->fn_80145c00(POWERUP_HAMMER_SUIT)) {
            return 3;
        } else {
            return 2;
        }
    }
    return 0;
}

extern "C" void PowerupCheck_Custom__FiiP7dAcPy_c(void);

// No need to adjust this, all the logic is handled in the function above
kmCallDefAsm(0x80A285FC) {
    stwu sp, -0x10(sp)
    mflr r0
    stw r0, 0x14(sp)

    mr r5, r30
    bl PowerupCheck_Custom__FiiP7dAcPy_c

    cmpwi r3, 0
    beq NoCustomPowerup

    cmpwi r3, 1
    beq AlreadyHasPowerup

    cmpwi r3, 2
    beq CustomPowerupSet_return

    li r29, 1
    b CustomPowerupSet_return

    AlreadyHasPowerup:
    li r28, 0
    li r29, 2
    b CustomPowerupSet_return

    NoCustomPowerup:
    CustomPowerupSet_return:
    // End of function
    lwz r0, 0x14(sp)
    mtlr r0
    addi sp, sp, 0x10
    
    // Leftover instruction from what we replaced to add the bl
    cmpwi r29, 0
    blr
}

// Allow EN_ITEM to be a custom powerup

/*
    EN_ITEM ID VALUES
    0x0 = Mushroom
    0x1 = Fire Flower
    0x2 = Star
    0x3 = Coin
    0x4 = Ice Flower
    0x6 = 1-UP
    0xB = Propeller
    0xD = Mini Mushroom
    0xE = Penguin
    0xF = Mega Mushroom (unused, does nothing, loads model from I_big_kinoko)
    0x10 = Big Coin (unused, adds 10 coins to coin counter)

    NEW ITEMS
    0x5 = Hammer Suit
*/

// daEnItem_c::setInternalType()
kmBranchDefCpp(0x80A2C030, NULL, void, daEnItem_c *this_) {
    this_->mInternalType = daEnItem_c::TYPE_MUSHROOM;
    switch (this_->mItemType) {
        case 1:
            this_->mInternalType = daEnItem_c::TYPE_STAR;
            break;
        case 6: // New
            this_->mInternalType = daEnItem_c::TYPE_HAMMER_SUIT;
            break;
        case 7:
            this_->mInternalType = daEnItem_c::TYPE_1UP;
            break;
        case 9:
            this_->mInternalType = daEnItem_c::TYPE_FIRE_FLOWER;
            break;
        case 14:
            this_->mInternalType = daEnItem_c::TYPE_ICE_FLOWER;
            break;
        case 17:
            this_->mInternalType = daEnItem_c::TYPE_PENGUIN;
            break;
        case 21:
            this_->mInternalType = daEnItem_c::TYPE_PROPELLER;
            break;
        case 25:
            this_->mInternalType = daEnItem_c::TYPE_MINI_MUSHROOM;
            break;
    }
}

// daEnItem_c::setInternalTypeSpecific()
kmBranchDefCpp(0x80A2BEE0, NULL, void, daEnItem_c *this_, int isDropMove) {
    this_->setInternalTypeSpecific(isDropMove);
}

// Similar to setInternalType(), however it covers more cases and will force
// some powerups to always spawn regardless of player state (for the Red Ring)
void daEnItem_c::setInternalTypeSpecific(int isDropMove) {
    mInternalType = TYPE_MUSHROOM;
    switch (mItemType) {
        case 0:
            if (chkItemValid() == 1) {
                mInternalType = TYPE_FIRE_FLOWER;
            }
            break;
        case 1:
            mInternalType = TYPE_STAR;
            break;
        case 2:
        case 4:
            mInternalType = TYPE_COIN;
            break;
        case 6: // New
            if ((isDropMove == 0) && (mIsDropMove == 0)) {
                if (chkItemValid() == 1) {
                    mInternalType = TYPE_HAMMER_SUIT;
                }
            } else {
                mInternalType = TYPE_HAMMER_SUIT;
            }
            break;
        case 7:
            mInternalType = TYPE_1UP;
            break;
        case 9:
            mInternalType = TYPE_FIRE_FLOWER;
            break;
        case 14:
            if ((isDropMove == 0) && (mIsDropMove == 0)) {
                if (chkItemValid() == 1) {
                    mInternalType = TYPE_ICE_FLOWER;
                }
            } else {
                mInternalType = TYPE_ICE_FLOWER;
            }
            break;
        case 17:
            if ((isDropMove == 0) && (mIsDropMove == 0)) {
                if (chkItemValid() == 1) {
                    mInternalType = TYPE_PENGUIN;
                }
            } else {
                mInternalType = TYPE_PENGUIN;
            }
            break;
        case 21:
            if ((isDropMove == 0) && (mIsDropMove == 0)) {
                if (chkItemValid() == 1) {
                    mInternalType = TYPE_PROPELLER;
                }
            } else {
                mInternalType = TYPE_PROPELLER;
            }
            break;
        case 25:
            mInternalType = TYPE_MINI_MUSHROOM;
            break;
    }
}

// Load the "wait" animation for custom powerups
kmCallDefAsm(0x80A27CE4) {
    cmplwi r4, 5 // Hammer Suit
    beqlr
    cmplwi r4, 6 // 1-up
    beqlr
    // Neither of those succeeded
    crclr 4*cr0+eq
    blr
}

// Custom movement types for custom items
extern "C" void daEnItem_c__doWaitMove1(void);
kmBranchDefAsm(0x80a28b34, 0x80a28b3c) {
    cmplwi r0, 2 // Star
    beq isStarOrHammer
    cmplwi r0, 5 // Hammer
    beq isStarOrHammer

    b daEnItem_c__doWaitMove1

    isStarOrHammer:
    blr
}

extern "C" void daEnItem_c__doWaitMove2(void);
kmBranchDefAsm(0x80a28a58, 0x80a28a60) {
    cmplwi r0, 2 // Star
    beq isStarOrHammer
    cmplwi r0, 5 // Hammer
    beq isStarOrHammer

    b daEnItem_c__doWaitMove2

    isStarOrHammer:
    blr
}

extern "C" void daEnItem_c__doPropellerMove(void);
kmBranchDefAsm(0x80a27aa4, 0x80a27aac) {
    cmplwi r0, 2 // Star
    beq isStarOrHammer
    cmplwi r0, 5 // Hammer
    beq isStarOrHammer

    b daEnItem_c__doPropellerMove

    isStarOrHammer:
    blr
}

// Only play star sounds in StarMove if the current actor is a star
extern "C" void startSound__14SndObjctCmnMapFUlRCQ34nw4r4math4VEC2Ul(void);
kmBranchDefAsm(0x80a2a3ac, 0x80a2a3b0) {
    lhz r12, 0xdca(r31)
    cmplwi r12, 2
    bne dontPlayStarSound

    bl startSound__14SndObjctCmnMapFUlRCQ34nw4r4math4VEC2Ul

    dontPlayStarSound:
    blr
}