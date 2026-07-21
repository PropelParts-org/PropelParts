#pragma once

#include <constants/message_list.h>

enum NEW_BMG_GROUPS_e {
    BMG_CATEGORY_PICTUREFONT_ICONS = 0x00,
    BMG_CATEGORY_NEWER_FILE_SELECT = 0x01,
    BMG_CATEGORY_MESSAGE_BOX_TITLE = 0x02,
    BMG_CATEGORY_MESSAGE_BOX_TEXT = 0x03,
    BMG_CATEGORY_LEVEL_NAMES = 0x100,
    BMG_CATEGORY_WORLD_NAMES = 0x200,
    BMG_CATEGORY_KOOPATLAS = 0x300,
    BMG_CATEGORY_WORLD_NUMBERS = 0x400,
    BMG_CATEGORY_LEVEL_ICONS = 0x401,
    BMG_CATEGORY_KP_WORLD_NAMES = 0x402,
};

// Koopatlas category layout:
// 0x00 -- Completion messages
// 0x10 -- Star Coins Menu
// 0x20/0x30 -- Hard Mode ON / OFF
// 0x40/0x50 -- Replay ON / OFF
// 0x60 -- Collision Debug ON
// 0x80 -- Collision Debug OFF

// level names use format:
// category: BMG_CATEGORY_LEVEL_NAMES + world number
// ID: level number

// World names use format:
// Category: BMG_CATEGORY_WORLD_NAMES
// ID: world number