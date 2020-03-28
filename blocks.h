#include <stdlib.h>

#define CLASSIC_AIR 0
#define CLASSIC_ROCK 1
#define CLASSIC_GRASS 2
#define CLASSIC_DIRT 3
#define CLASSIC_STONE 4
#define CLASSIC_WOOD 5
#define CLASSIC_SHRUB 6
#define CLASSIC_BLACKROCK 7
#define CLASSIC_WATER 8
#define CLASSIC_WATERSTILL 9
#define CLASSIC_LAVA 10
#define CLASSIC_LAVASTILL 11
#define CLASSIC_SAND 12
#define CLASSIC_GRAVEL 13
#define CLASSIC_GOLDROCK 14
#define CLASSIC_IRONROCK 15
#define CLASSIC_COAL 16
#define CLASSIC_TRUNK 17
#define CLASSIC_LEAF 18
#define CLASSIC_SPONGE 19
#define CLASSIC_GLASS 20
#define CLASSIC_RED 21
#define CLASSIC_ORANGE 22
#define CLASSIC_YELLOW 23
#define CLASSIC_LIGHTGREEN 24
#define CLASSIC_GREEN 25
#define CLASSIC_AQUAGREEN 26
#define CLASSIC_CYAN 27
#define CLASSIC_LIGHTBLUE 28
#define CLASSIC_BLUE 29
#define CLASSIC_PURPLE 30
#define CLASSIC_LIGHTPURPLE 31
#define CLASSIC_PINK 32
#define CLASSIC_DARKPINK 33
#define CLASSIC_DARKGREY 34
#define CLASSIC_LIGHTGREY 35
#define CLASSIC_WHITE 36
#define CLASSIC_YELLOWFLOWER 37
#define CLASSIC_REDFLOWER 38
#define CLASSIC_MUSHROOM 39
#define CLASSIC_REDMUSHROOM 40
#define CLASSIC_GOLDSOLID 41
#define CLASSIC_IRON 42
#define CLASSIC_STAIRCASEFULL 43
#define CLASSIC_STAIRCASESTEP 44
#define CLASSIC_BRICK 45
#define CLASSIC_TNT 46
#define CLASSIC_BOOKCASE 47
#define CLASSIC_STONEVINE 48
#define CLASSIC_OBSIDIAN 49

/*IDs from 1.15.2 data exports*/
#define MODERN_AIR 0
#define MODERN_AIR_STATE 0
#define MODERN_STONE 1 /*TODO: Check if cobblestone or smooth stone*/
#define MODERN_STONE_STATE 1
#define MODERN_GRASS_BLOCK 8
#define MODERN_GRASS_BLOCK_STATE 8
#define MODERN_DIRT 9
#define MODERN_DIRT_STATE 10
#define MODERN_COBBLESTONE 12 /*TODO: Check if cobblestone or smooth stone*/
#define MODERN_COBBLESTONE_STATE 14
#define MODERN_OAK_PLANKS 13
#define MODERN_OAK_PLANKS_STATE 15
#define MODERN_OAK_SAPLING 19
#define MODERN_OAK_SAPLING_STATE 21 /*TODO: Check if grow-trees works*/
#define MODERN_BEDROCK 25
#define MODERN_BEDROCK_STATE 33
#define MODERN_WATER 26 /*TODO: Check*/
#define MODERN_WATERSTILL 26 /*TODO: Check*/
#define MODERN_WATER_STATE 49 /*TODO: Check*/
#define MODERN_LAVA 27 /*TODO: Check*/
#define MODERN_LAVASTILL 27 /*TODO: Check*/
#define MODERN_LAVA_STATE 65/*TODO: Check*/
#define MODERN_SAND 28
#define MODERN_SAND_STATE 66
#define MODERN_GRAVEL 30
#define MODERN_GRAVEL_STATE 68
#define MODERN_GOLD_ORE 31
#define MODERN_GOLD_ORE_STATE 69
#define MODERN_IRON_ORE 32
#define MODERN_IRON_ORE_STATE 70
#define MODERN_COAL_ORE 33
#define MODERN_COAL_ORE_STATE 71
#define MODERN_OAK_LOG 34
#define MODERN_OAK_LOG_STATE 73 /*TODO: Check axis*/
#define MODERN_OAK_LEAVES 58
#define MODERN_OAK_LEAVES_STATE 144 /*TODO: Check peristent*/
#define MODERN_SPONGE 64
#define MODERN_SPONGE_STATE 228
#define MODERN_GLASS 66
#define MODERN_GLASS_STATE 230
#define MODERN_RED_WOOL 115
#define MODERN_RED_WOOL_STATE 1397
#define MODERN_ORANGE_WOOL 102
#define MODERN_ORANGE_WOOL_STATE 1384
#define MODERN_YELLOW_WOOL 105
#define MODERN_YELLOW_WOOL_STATE 1387
#define MODERN_LIME_WOOL 106
#define MODERN_LIME_WOOL_STATE 1388
#define MODERN_GREEN_WOOL 114
#define MODERN_GREEN_WOOL_STATE 1396
#define MODERN_CYAN_WOOL 110
#define MODERN_CYAN_WOOL_STATE 1392
#define MODERN_LIGHT_BLUE_WOOL 104
#define MODERN_LIGHT_BLUE_WOOL_STATE 1386
#define MODERN_BLUE_WOOL 112
#define MODERN_BLUE_WOOL_STATE 1394
#define MODERN_PURPLE_WOOL 111
#define MODERN_PURPLE_WOOL_STATE 1393
#define MODERN_BLACK_WOOL 116 /*TODO: Not a correct conversion*/
#define MODERN_BLACK_WOOL_STATE 1398
#define MODERN_PINK_WOOL 107
#define MODERN_PINK_WOOL_STATE 1389
#define MODERN_MAGENTA_WOOL 103
#define MODERN_MAGENTA_WOOL_STATE 1385
#define MODERN_GRAY_WOOL 108
#define MODERN_GRAY_WOOL_STATE 1390
#define MODERN_LIGHT_GRAY_WOOL 109
#define MODERN_LIGHT_GRAY_WOOL_STATE 1391
#define MODERN_WHITE_WOOL 101
#define MODERN_WHITE_WOOL_STATE 1383
#define MODERN_DANDELION 118
#define MODERN_DANDELION_STATE 1411
#define MODERN_POPPY 119
#define MODERN_POPPY_STATE 1412
#define MODERN_BROWN_MUSHROOM 131
#define MODERN_BROWN_MUSHROOM_STATE 1424
#define MODERN_RED_MUSHROOM 132
#define MODERN_RED_MUSHROOM_STATE 1425
#define MODERN_GOLD_BLOCK 133
#define MODERN_GOLD_BLOCK_STATE 1426
#define MODERN_IRON_BLOCK 134
#define MODERN_IRON_BLOCK_STATE 1427
#define MODERN_SMOOTH_STONE_SLAB 451
#define MODERN_SMOOTH_STONE_SLAB_LOWER_STATE 7807 /*TODO: Check state*/
#define MODERN_SMOOTH_STONE_SLAB_DOUBLE_STATE 7808 /*TODO: Check state*/
#define MODERN_BRICKS 135
#define MODERN_BRICKS_STATE 1428
#define MODERN_TNT 136
#define MODERN_TNT_STATE 1430 /*TODO: Check unstable state (true here)*/
#define MODERN_BOOKSHELF 137
#define MODERN_BOOKSHELF_STATE 1431
#define MODERN_MOSSY_COBBLESTONE 138
#define MODERN_MOSSY_COBBLESTONE_STATE 1432
#define MODERN_OBSIDIAN 139
#define MODERN_OBSIDIAN_STATE 1433

#define CLASSIC_BLOCKS 255
#define MODERN_BLOCKS 1024
#define MODERN_STATES 16384 /*TODO: See if this can be contracted*/

int16_t CLASSIC_MODERNBLOCK[CLASSIC_BLOCKS];
int16_t CLASSIC_MODERNSTATE[CLASSIC_BLOCKS];
int8_t MODERN_CLASSICBLOCK[MODERN_BLOCKS][MODERN_STATES]; 

int initialise_mappings();
