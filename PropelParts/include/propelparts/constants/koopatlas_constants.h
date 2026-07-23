#pragma once
#include <types.h>

#define CAMERA_MAX_PAN_ZOOM 4.5f ///< Maximum zoom allowed while the camera is panning for path unlocks

#define CAMERA_MIN_PAN_ZOOM 2.0f ///< Minimum zoom allowed while the camera is panning for path unlocks

#define CAMERA_ZOOM 2.8f ///< Default camera zoom level. Higher values are further zoomed out

#define CAMERA_WARP_ZONE_ZOOM 3.4f ///< Zoom level used in the Warp Zone map

#define PATH_ALPHA_INC 3 ///< Amount added to the path alpha each frame, during path unlocks

#define PATH_LOCK_ALPHA 0 ///< Alpha of a path when locked

#define PATH_OPEN_ALPHA 255 ///< Alpha of a path when unlocked

#define SHOP_ITEM_COUNT 12 /// < The number of items present in the Shop window

// World/Course IDs are NOT zero-indexed here

#define YOSHI_HOUSE_WORLD 1
#define YOSHI_HOUSE_STAGE 41

#define COURSE_ID_SHOP 99 ///< Course ID that will be overridden with Shop behavior

#define WORLD_ID_NO_DRAW 80 ///< Course nodes with this ID will not be rendered. Used for the ending cutscene

#define GAME_COMPLETE_TITLE_WORLD 4 ///< World ID for the 100% Completion titlescreen
#define GAME_COMPLETE_TITLE_STAGE 11 ///< Level ID for the 100% Completion titlescreen

#define BOWSER_CLEAR_TITLE_WORLD 4 ///< World ID for the Bowser Defeated titlescreen
#define BOWSER_CLEAR_TITLE_STAGE 10 ///< Level ID for the Bowser Defeated titlescreen

// TODO: Fill in all (most) of the hardcoded data here
