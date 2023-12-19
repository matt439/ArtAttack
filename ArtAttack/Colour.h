#ifndef COLOUR_H
#define COLOUR_H

#include "MattMath.h"

namespace colour_consts
{	
	namespace html
	{
		const std::string ALICE_BLUE = "f0f8ff";
		const std::string ANTIQUE_WHITE = "faebd7";
		const std::string AQUA = "00ffff";
		const std::string AQUAMARINE = "7fffd4";
		const std::string AZURE = "f0ffff";
		const std::string BEIGE = "f5f5dc";
		const std::string BISQUE = "ffe4c4";
		const std::string BLACK = "000000";
		const std::string BLANCHED_ALMOND = "ffebcd";
		const std::string BLUE = "0000ff";
		const std::string BLUE_VIOLET = "8a2be2";
		const std::string BROWN = "a52a2a";
		const std::string BURLYWOOD = "deb887";
		const std::string CADET_BLUE = "5f9ea0";
		const std::string CHARTREUSE = "7fff00";
		const std::string CHOCOLATE = "d2691e";
		const std::string CORAL = "ff7f50";
		const std::string CORNFLOWER_BLUE = "6495ed";
		const std::string CORNSILK = "fff8dc";
		const std::string CRIMSON = "dc143c";
		const std::string CYAN = "00ffff";
		const std::string DARK_BLUE = "00008b";
		const std::string DARK_CYAN = "008b8b";
		const std::string DARK_GOLDENROD = "b8860b";
		const std::string DARK_GRAY = "a9a9a9";
		const std::string DARK_GREEN = "006400";
		const std::string DARK_GREY = "a9a9a9";
		const std::string DARK_KHAKI = "bdb76b";
		const std::string DARK_MAGENTA = "8b008b";
		const std::string DARK_OLIVE_GREEN = "556b2f";
		const std::string DARK_ORANGE = "ff8c00";
		const std::string DARK_ORCHID = "9932cc";
		const std::string DARK_RED = "8b0000";
		const std::string DARK_SALMON = "e9967a";
		const std::string DARK_SEA_GREEN = "8fbc8f";
		const std::string DARK_SLATE_BLUE = "483d8b";
		const std::string DARK_SLATE_GRAY = "2f4f4f";
		const std::string DARK_SLATE_GREY = "2f4f4f";
		const std::string DARK_TURQUOISE = "00ced1";
		const std::string DARK_VIOLET = "9400d3";
		const std::string DEEP_PINK = "ff1493";
		const std::string DEEP_SKY_BLUE = "00bfff";
		const std::string DIM_GRAY = "696969";
		const std::string DIM_GREY = "696969";
		const std::string DODGER_BLUE = "1e90ff";
		const std::string FIRE_BRICK = "b22222";
		const std::string FLORAL_WHITE = "fffaf0";
		const std::string FOREST_GREEN = "228b22";
		const std::string FUCHSIA = "ff00ff";
		const std::string GAINSBORO = "dcdcdc";
		const std::string GHOST_WHITE = "f8f8ff";
		const std::string GOLD = "ffd700";
		const std::string GOLDENROD = "daa520";
		const std::string GRAY = "808080";
		const std::string GREEN = "008000";
		const std::string GREEN_YELLOW = "adff2f";
		const std::string GREY = "808080";
		const std::string HONEYDEW = "f0fff0";
		const std::string HOT_PINK = "ff69b4";
		const std::string INDIAN_RED = "cd5c5c";
		const std::string INDIGO = "4b0082";
		const std::string IVORY = "fffff0";
		const std::string KHAKI = "f0e68c";
		const std::string LAVENDER = "e6e6fa";
		const std::string LAVENDER_BLUSH = "fff0f5";
		const std::string LAWN_GREEN = "7cfc00";
		const std::string LEMON_CHIFFON = "fffacd";
		const std::string LIGHT_BLUE = "add8e6";
		const std::string LIGHT_CORAL = "f08080";
		const std::string LIGHT_CYAN = "e0ffff";
		const std::string LIGHT_GOLDENROD_YELLOW = "fafad2";
		const std::string LIGHT_GRAY = "d3d3d3";
		const std::string LIGHT_GREEN = "90ee90";
		const std::string LIGHT_GREY = "d3d3d3";
		const std::string LIGHT_PINK = "ffb6c1";
		const std::string LIGHT_SALMON = "ffa07a";
		const std::string LIGHT_SEA_GREEN = "20b2aa";
		const std::string LIGHT_SKY_BLUE = "87cefa";
		const std::string LIGHT_SLATE_GRAY = "778899";
		const std::string LIGHT_SLATE_GREY = "778899";
		const std::string LIGHT_STEEL_BLUE = "b0c4de";
		const std::string LIGHT_YELLOW = "ffffe0";
		const std::string LIME = "00ff00";
		const std::string LIME_GREEN = "32cd32";
		const std::string LINEN = "faf0e6";
		const std::string MAGENTA = "ff00ff";
		const std::string MAROON = "800000";
		const std::string MEDIUM_AQUAMARINE = "66cdaa";
		const std::string MEDIUM_BLUE = "0000cd";
		const std::string MEDIUM_ORCHID = "ba55d3";
		const std::string MEDIUM_PURPLE = "9370db";
		const std::string MEDIUM_SEA_GREEN = "3cb371";
		const std::string MEDIUM_SLATE_BLUE = "7b68ee";
		const std::string MEDIUM_SPRING_GREEN = "00fa9a";
		const std::string MEDIUM_TURQUOISE = "48d1cc";
		const std::string MEDIUM_VIOLET_RED = "c71585";
		const std::string MIDNIGHT_BLUE = "191970";
		const std::string MINT_CREAM = "f5fffa";
		const std::string MISTY_ROSE = "ffe4e1";
		const std::string MOCCASIN = "ffe4b5";
		const std::string NAVAJO_WHITE = "ffdead";
		const std::string NAVY = "000080";
		const std::string OLD_LACE = "fdf5e6";
		const std::string OLIVE = "808000";
		const std::string OLIVE_DRAB = "6b8e23";
		const std::string ORANGE = "ffa500";
		const std::string ORANGE_RED = "ff4500";
		const std::string ORCHID = "da70d6";
		const std::string PALE_GOLDENROD = "eee8aa";
		const std::string PALE_GREEN = "98fb98";
		const std::string PALE_TURQUOISE = "afeeee";
		const std::string PALE_VIOLET_RED = "db7093";
		const std::string PAPAYA_WHIP = "ffefd5";
		const std::string PEACH_PUFF = "ffdab9";
		const std::string PERU = "cd853f";
		const std::string PINK = "ffc0cb";
		const std::string PLUM = "dda0dd";
		const std::string POWDER_BLUE = "b0e0e6";
		const std::string PURPLE = "800080";
		const std::string REBECCA_PURPLE = "663399";
		const std::string RED = "ff0000";
		const std::string ROSY_BROWN = "bc8f8f";
		const std::string ROYAL_BLUE = "4169e1";
		const std::string SADDLE_BROWN = "8b4513";
		const std::string SALMON = "fa8072";
		const std::string SANDY_BROWN = "f4a460";
		const std::string SEA_GREEN = "2e8b57";
		const std::string SEASHELL = "fff5ee";
		const std::string SIENNA = "a0522d";
		const std::string SILVER = "c0c0c0";
		const std::string SKY_BLUE = "87ceeb";
		const std::string SLATE_BLUE = "6a5acd";
		const std::string SLATE_GRAY = "708090";
		const std::string SLATE_GREY = "708090";
		const std::string SNOW = "fffafa";
		const std::string SPRING_GREEN = "00ff7f";
		const std::string STEEL_BLUE = "4682b4";
		const std::string TAN = "d2b48c";
		const std::string TEAL = "008080";
		const std::string THISTLE = "d8bfd8";
		const std::string TOMATO = "ff6347";
		const std::string TURQUOISE = "40e0d0";
		const std::string VIOLET = "ee82ee";
		const std::string WHEAT = "f5deb3";
		const std::string WHITE = "ffffff";
		const std::string WHITE_SMOKE = "f5f5f5";
		const std::string YELLOW = "ffff00";
		const std::string YELLOW_GREEN = "9acd32";
	}

	const MattMath::Colour ALICE_BLUE = { html::ALICE_BLUE };
	const MattMath::Colour ANTIQUE_WHITE = { html::ANTIQUE_WHITE };
	const MattMath::Colour AQUA = { html::AQUA };
	const MattMath::Colour AQUAMARINE = { html::AQUAMARINE };
	const MattMath::Colour AZURE = { html::AZURE };
	const MattMath::Colour BEIGE = { html::BEIGE };
	const MattMath::Colour BISQUE = { html::BISQUE };
	const MattMath::Colour BLACK = { html::BLACK };
	const MattMath::Colour BLANCHED_ALMOND = { html::BLANCHED_ALMOND };
	const MattMath::Colour BLUE = { html::BLUE };
	const MattMath::Colour BLUE_VIOLET = { html::BLUE_VIOLET };
	const MattMath::Colour BROWN = { html::BROWN };
	const MattMath::Colour BURLYWOOD = { html::BURLYWOOD };
	const MattMath::Colour CADET_BLUE = { html::CADET_BLUE };
	const MattMath::Colour CHARTREUSE = { html::CHARTREUSE };
	const MattMath::Colour CHOCOLATE = { html::CHOCOLATE };
	const MattMath::Colour CORAL = { html::CORAL };
	const MattMath::Colour CORNFLOWER_BLUE = { html::CORNFLOWER_BLUE };
	const MattMath::Colour CORNSILK = { html::CORNSILK };
	const MattMath::Colour CRIMSON = { html::CRIMSON };
	const MattMath::Colour CYAN = { html::CYAN };
	const MattMath::Colour DARK_BLUE = { html::DARK_BLUE };
	const MattMath::Colour DARK_CYAN = { html::DARK_CYAN };
	const MattMath::Colour DARK_GOLDENROD = { html::DARK_GOLDENROD };
	const MattMath::Colour DARK_GRAY = { html::DARK_GRAY };
	const MattMath::Colour DARK_GREEN = { html::DARK_GREEN };
	const MattMath::Colour DARK_GREY = { html::DARK_GREY };
	const MattMath::Colour DARK_KHAKI = { html::DARK_KHAKI };
	const MattMath::Colour DARK_MAGENTA = { html::DARK_MAGENTA };
	const MattMath::Colour DARK_OLIVE_GREEN = { html::DARK_OLIVE_GREEN };
	const MattMath::Colour DARK_ORANGE = { html::DARK_ORANGE };
	const MattMath::Colour DARK_ORCHID = { html::DARK_ORCHID };
	const MattMath::Colour DARK_RED = { html::DARK_RED };
	const MattMath::Colour DARK_SALMON = { html::DARK_SALMON };
	const MattMath::Colour DARK_SEA_GREEN = { html::DARK_SEA_GREEN };
	const MattMath::Colour DARK_SLATE_BLUE = { html::DARK_SLATE_BLUE };
	const MattMath::Colour DARK_SLATE_GRAY = { html::DARK_SLATE_GRAY };
	const MattMath::Colour DARK_SLATE_GREY = { html::DARK_SLATE_GREY };
	const MattMath::Colour DARK_TURQUOISE = { html::DARK_TURQUOISE };
	const MattMath::Colour DARK_VIOLET = { html::DARK_VIOLET };
	const MattMath::Colour DEEP_PINK = { html::DEEP_PINK };
	const MattMath::Colour DEEP_SKY_BLUE = { html::DEEP_SKY_BLUE };
	const MattMath::Colour DIM_GRAY = { html::DIM_GRAY };
	const MattMath::Colour DIM_GREY = { html::DIM_GREY };
	const MattMath::Colour DODGER_BLUE = { html::DODGER_BLUE };
	const MattMath::Colour FIRE_BRICK = { html::FIRE_BRICK };
	const MattMath::Colour FLORAL_WHITE = { html::FLORAL_WHITE };
	const MattMath::Colour FOREST_GREEN = { html::FOREST_GREEN };
	const MattMath::Colour FUCHSIA = { html::FUCHSIA };
	const MattMath::Colour GAINSBORO = { html::GAINSBORO };
	const MattMath::Colour GHOST_WHITE = { html::GHOST_WHITE };
	const MattMath::Colour GOLD = { html::GOLD };
	const MattMath::Colour GOLDENROD = { html::GOLDENROD };
	const MattMath::Colour GRAY = { html::GRAY };
	const MattMath::Colour GREEN = { html::GREEN };
	const MattMath::Colour GREEN_YELLOW = { html::GREEN_YELLOW };
	const MattMath::Colour GREY = { html::GREY };
	const MattMath::Colour HONEYDEW = { html::HONEYDEW };
	const MattMath::Colour HOT_PINK = { html::HOT_PINK };
	const MattMath::Colour INDIAN_RED = { html::INDIAN_RED };
	const MattMath::Colour INDIGO = { html::INDIGO };
	const MattMath::Colour IVORY = { html::IVORY };
	const MattMath::Colour KHAKI = { html::KHAKI };
	const MattMath::Colour LAVENDER = { html::LAVENDER };
	const MattMath::Colour LAVENDER_BLUSH = { html::LAVENDER_BLUSH };
	const MattMath::Colour LAWN_GREEN = { html::LAWN_GREEN };
	const MattMath::Colour LEMON_CHIFFON = { html::LEMON_CHIFFON };
	const MattMath::Colour LIGHT_BLUE = { html::LIGHT_BLUE };
	const MattMath::Colour LIGHT_CORAL = { html::LIGHT_CORAL };
	const MattMath::Colour LIGHT_CYAN = { html::LIGHT_CYAN };
	const MattMath::Colour LIGHT_GOLDENROD_YELLOW = { html::LIGHT_GOLDENROD_YELLOW };
	const MattMath::Colour LIGHT_GRAY = { html::LIGHT_GRAY };
	const MattMath::Colour LIGHT_GREEN = { html::LIGHT_GREEN };
	const MattMath::Colour LIGHT_GREY = { html::LIGHT_GREY };
	const MattMath::Colour LIGHT_PINK = { html::LIGHT_PINK };
	const MattMath::Colour LIGHT_SALMON = { html::LIGHT_SALMON };
	const MattMath::Colour LIGHT_SEA_GREEN = { html::LIGHT_SEA_GREEN };
	const MattMath::Colour LIGHT_SKY_BLUE = { html::LIGHT_SKY_BLUE };
	const MattMath::Colour LIGHT_SLATE_GRAY = { html::LIGHT_SLATE_GRAY };
	const MattMath::Colour LIGHT_SLATE_GREY = { html::LIGHT_SLATE_GREY };
	const MattMath::Colour LIGHT_STEEL_BLUE = { html::LIGHT_STEEL_BLUE };
	const MattMath::Colour LIGHT_YELLOW = { html::LIGHT_YELLOW };
	const MattMath::Colour LIME = { html::LIME };
	const MattMath::Colour LIME_GREEN = { html::LIME_GREEN };
	const MattMath::Colour LINEN = { html::LINEN };
	const MattMath::Colour MAGENTA = { html::MAGENTA };
	const MattMath::Colour MAROON = { html::MAROON };
	const MattMath::Colour MEDIUM_AQUAMARINE = { html::MEDIUM_AQUAMARINE };
	const MattMath::Colour MEDIUM_BLUE = { html::MEDIUM_BLUE };
	const MattMath::Colour MEDIUM_ORCHID = { html::MEDIUM_ORCHID };
	const MattMath::Colour MEDIUM_PURPLE = { html::MEDIUM_PURPLE };
	const MattMath::Colour MEDIUM_SEA_GREEN = { html::MEDIUM_SEA_GREEN };
	const MattMath::Colour MEDIUM_SLATE_BLUE = { html::MEDIUM_SLATE_BLUE };
	const MattMath::Colour MEDIUM_SPRING_GREEN = { html::MEDIUM_SPRING_GREEN };
	const MattMath::Colour MEDIUM_TURQUOISE = { html::MEDIUM_TURQUOISE };
	const MattMath::Colour MEDIUM_VIOLET_RED = { html::MEDIUM_VIOLET_RED };
	const MattMath::Colour MIDNIGHT_BLUE = { html::MIDNIGHT_BLUE };
	const MattMath::Colour MINT_CREAM = { html::MINT_CREAM };
	const MattMath::Colour MISTY_ROSE = { html::MISTY_ROSE };
	const MattMath::Colour MOCCASIN = { html::MOCCASIN };
	const MattMath::Colour NAVAJO_WHITE = { html::NAVAJO_WHITE };
	const MattMath::Colour NAVY = { html::NAVY };
	const MattMath::Colour OLD_LACE = { html::OLD_LACE };
	const MattMath::Colour OLIVE = { html::OLIVE };
	const MattMath::Colour OLIVE_DRAB = { html::OLIVE_DRAB };
	const MattMath::Colour ORANGE = { html::ORANGE };
	const MattMath::Colour ORANGE_RED = { html::ORANGE_RED };
	const MattMath::Colour ORCHID = { html::ORCHID };
	const MattMath::Colour PALE_GOLDENROD = { html::PALE_GOLDENROD };
	const MattMath::Colour PALE_GREEN = { html::PALE_GREEN };
	const MattMath::Colour PALE_TURQUOISE = { html::PALE_TURQUOISE };
	const MattMath::Colour PALE_VIOLET_RED = { html::PALE_VIOLET_RED };
	const MattMath::Colour PAPAYA_WHIP = { html::PAPAYA_WHIP };
	const MattMath::Colour PEACH_PUFF = { html::PEACH_PUFF };
	const MattMath::Colour PERU = { html::PERU };
	const MattMath::Colour PINK = { html::PINK };
	const MattMath::Colour PLUM = { html::PLUM };
	const MattMath::Colour POWDER_BLUE = { html::POWDER_BLUE };
	const MattMath::Colour PURPLE = { html::PURPLE };
	const MattMath::Colour REBECCA_PURPLE = { html::REBECCA_PURPLE };
	const MattMath::Colour RED = { html::RED };
	const MattMath::Colour ROSY_BROWN = { html::ROSY_BROWN };
	const MattMath::Colour ROYAL_BLUE = { html::ROYAL_BLUE };
	const MattMath::Colour SADDLE_BROWN = { html::SADDLE_BROWN };
	const MattMath::Colour SALMON = { html::SALMON };
	const MattMath::Colour SANDY_BROWN = { html::SANDY_BROWN };
	const MattMath::Colour SEA_GREEN = { html::SEA_GREEN };
	const MattMath::Colour SEASHELL = { html::SEASHELL };
	const MattMath::Colour SIENNA = { html::SIENNA };
	const MattMath::Colour SILVER = { html::SILVER };
	const MattMath::Colour SKY_BLUE = { html::SKY_BLUE };
	const MattMath::Colour SLATE_BLUE = { html::SLATE_BLUE };
	const MattMath::Colour SLATE_GRAY = { html::SLATE_GRAY };
	const MattMath::Colour SLATE_GREY = { html::SLATE_GREY };
	const MattMath::Colour SNOW = { html::SNOW };
	const MattMath::Colour SPRING_GREEN = { html::SPRING_GREEN };
	const MattMath::Colour STEEL_BLUE = { html::STEEL_BLUE };
	const MattMath::Colour TAN = { html::TAN };
	const MattMath::Colour TEAL = { html::TEAL };
	const MattMath::Colour THISTLE = { html::THISTLE };
	const MattMath::Colour TOMATO = { html::TOMATO };
	const MattMath::Colour TURQUOISE = { html::TURQUOISE };
	const MattMath::Colour VIOLET = { html::VIOLET };
	const MattMath::Colour WHEAT = { html::WHEAT };
	const MattMath::Colour WHITE = { html::WHITE };
	const MattMath::Colour WHITE_SMOKE = { html::WHITE_SMOKE };
	const MattMath::Colour YELLOW = { html::YELLOW };
	const MattMath::Colour YELLOW_GREEN = { html::YELLOW_GREEN };

	const MattMath::Colour TEAM_BLUE = { 6, 52, 204, 255 };
	const MattMath::Colour TEAM_YELLOW = { 255, 255, 0, 255 };
	const MattMath::Colour TEAM_ORANGE = { 255, 127, 0, 255 };
	const MattMath::Colour TEAM_PINK = { 255, 0, 127, 255 };
	const MattMath::Colour TEAM_GREEN = { 0, 255, 0, 255 };

	inline static MattMath::Colour colour_from_name(const std::string& name)
	{
		if (name == "ALICE_BLUE") return colour_consts::ALICE_BLUE;
		if (name == "ANTIQUE_WHITE") return colour_consts::ANTIQUE_WHITE;
		if (name == "AQUA") return colour_consts::AQUA;
		if (name == "AQUAMARINE") return colour_consts::AQUAMARINE;
		if (name == "AZURE") return colour_consts::AZURE;
		if (name == "BEIGE") return colour_consts::BEIGE;
		if (name == "BISQUE") return colour_consts::BISQUE;
		if (name == "BLACK") return colour_consts::BLACK;
		if (name == "BLANCHED_ALMOND") return colour_consts::BLANCHED_ALMOND;
		if (name == "BLUE") return colour_consts::BLUE;
		if (name == "BLUE_VIOLET") return colour_consts::BLUE_VIOLET;
		if (name == "BROWN") return colour_consts::BROWN;
		if (name == "BURLYWOOD") return colour_consts::BURLYWOOD;
		if (name == "CADET_BLUE") return colour_consts::CADET_BLUE;
		if (name == "CHARTREUSE") return colour_consts::CHARTREUSE;
		if (name == "CHOCOLATE") return colour_consts::CHOCOLATE;
		if (name == "CORAL") return colour_consts::CORAL;
		if (name == "CORNFLOWER_BLUE") return colour_consts::CORNFLOWER_BLUE;
		if (name == "CORNSILK") return colour_consts::CORNSILK;
		if (name == "CRIMSON") return colour_consts::CRIMSON;
		if (name == "CYAN") return colour_consts::CYAN;
		if (name == "DARK_BLUE") return colour_consts::DARK_BLUE;
		if (name == "DARK_CYAN") return colour_consts::DARK_CYAN;
		if (name == "DARK_GOLDENROD") return colour_consts::DARK_GOLDENROD;
		if (name == "DARK_GRAY") return colour_consts::DARK_GRAY;
		if (name == "DARK_GREEN") return colour_consts::DARK_GREEN;
		if (name == "DARK_GREY") return colour_consts::DARK_GREY;
		if (name == "DARK_KHAKI") return colour_consts::DARK_KHAKI;
		if (name == "DARK_MAGENTA") return colour_consts::DARK_MAGENTA;
		if (name == "DARK_OLIVE_GREEN") return colour_consts::DARK_OLIVE_GREEN;
		if (name == "DARK_ORANGE") return colour_consts::DARK_ORANGE;
		if (name == "DARK_ORCHID") return colour_consts::DARK_ORCHID;
		if (name == "DARK_RED") return colour_consts::DARK_RED;
		if (name == "DARK_SALMON") return colour_consts::DARK_SALMON;
		if (name == "DARK_SEA_GREEN") return colour_consts::DARK_SEA_GREEN;
		if (name == "DARK_SLATE_BLUE") return colour_consts::DARK_SLATE_BLUE;
		if (name == "DARK_SLATE_GRAY") return colour_consts::DARK_SLATE_GRAY;
		if (name == "DARK_SLATE_GREY") return colour_consts::DARK_SLATE_GREY;
		if (name == "DARK_TURQUOISE") return colour_consts::DARK_TURQUOISE;
		if (name == "DARK_VIOLET") return colour_consts::DARK_VIOLET;
		if (name == "DEEP_PINK") return colour_consts::DEEP_PINK;
		if (name == "DEEP_SKY_BLUE") return colour_consts::DEEP_SKY_BLUE;
		if (name == "DIM_GRAY") return colour_consts::DIM_GRAY;
		if (name == "DIM_GREY") return colour_consts::DIM_GREY;
		if (name == "DODGER_BLUE") return colour_consts::DODGER_BLUE;
		if (name == "FIRE_BRICK") return colour_consts::FIRE_BRICK;
		if (name == "FLORAL_WHITE") return colour_consts::FLORAL_WHITE;
		if (name == "FOREST_GREEN") return colour_consts::FOREST_GREEN;
		if (name == "FUCHSIA") return colour_consts::FUCHSIA;
		if (name == "GAINSBORO") return colour_consts::GAINSBORO;
		if (name == "GHOST_WHITE") return colour_consts::GHOST_WHITE;
		if (name == "GOLD") return colour_consts::GOLD;
		if (name == "GOLDENROD") return colour_consts::GOLDENROD;
		if (name == "GRAY") return colour_consts::GRAY;
		if (name == "GREEN") return colour_consts::GREEN;
		if (name == "GREEN_YELLOW") return colour_consts::GREEN_YELLOW;
		if (name == "GREY") return colour_consts::GREY;
		if (name == "HONEYDEW") return colour_consts::HONEYDEW;
		if (name == "HOT_PINK") return colour_consts::HOT_PINK;
		if (name == "INDIAN_RED") return colour_consts::INDIAN_RED;
		if (name == "INDIGO") return colour_consts::INDIGO;
		if (name == "IVORY") return colour_consts::IVORY;
		if (name == "KHAKI") return colour_consts::KHAKI;
		if (name == "LAVENDER") return colour_consts::LAVENDER;
		if (name == "LAVENDER_BLUSH") return colour_consts::LAVENDER_BLUSH;
		if (name == "LAWN_GREEN") return colour_consts::LAWN_GREEN;
		if (name == "LEMON_CHIFFON") return colour_consts::LEMON_CHIFFON;
		if (name == "LIGHT_BLUE") return colour_consts::LIGHT_BLUE;
		if (name == "LIGHT_CORAL") return colour_consts::LIGHT_CORAL;
		if (name == "LIGHT_CYAN") return colour_consts::LIGHT_CYAN;
		if (name == "LIGHT_GOLDENROD_YELLOW") return colour_consts::LIGHT_GOLDENROD_YELLOW;
		if (name == "LIGHT_GRAY") return colour_consts::LIGHT_GRAY;
		if (name == "LIGHT_GREEN") return colour_consts::LIGHT_GREEN;
		if (name == "LIGHT_GREY") return colour_consts::LIGHT_GREY;
		if (name == "LIGHT_PINK") return colour_consts::LIGHT_PINK;
		if (name == "LIGHT_SALMON") return colour_consts::LIGHT_SALMON;
		if (name == "LIGHT_SEA_GREEN") return colour_consts::LIGHT_SEA_GREEN;
		if (name == "LIGHT_SKY_BLUE") return colour_consts::LIGHT_SKY_BLUE;
		if (name == "LIGHT_SLATE_GRAY") return colour_consts::LIGHT_SLATE_GRAY;
		if (name == "LIGHT_SLATE_GREY") return colour_consts::LIGHT_SLATE_GREY;
		if (name == "LIGHT_STEEL_BLUE") return colour_consts::LIGHT_STEEL_BLUE;
		if (name == "LIGHT_YELLOW") return colour_consts::LIGHT_YELLOW;
		if (name == "LIME") return colour_consts::LIME;
		if (name == "LIME_GREEN") return colour_consts::LIME_GREEN;
		if (name == "LINEN") return colour_consts::LINEN;
		if (name == "MAGENTA") return colour_consts::MAGENTA;
		if (name == "MAROON") return colour_consts::MAROON;
		if (name == "MEDIUM_AQUAMARINE") return colour_consts::MEDIUM_AQUAMARINE;
		if (name == "MEDIUM_BLUE") return colour_consts::MEDIUM_BLUE;
		if (name == "MEDIUM_ORCHID") return colour_consts::MEDIUM_ORCHID;
		if (name == "MEDIUM_PURPLE") return colour_consts::MEDIUM_PURPLE;
		if (name == "MEDIUM_SEA_GREEN") return colour_consts::MEDIUM_SEA_GREEN;
		if (name == "MEDIUM_SLATE_BLUE") return colour_consts::MEDIUM_SLATE_BLUE;
		if (name == "MEDIUM_SPRING_GREEN") return colour_consts::MEDIUM_SPRING_GREEN;
		if (name == "MEDIUM_TURQUOISE") return colour_consts::MEDIUM_TURQUOISE;
		if (name == "MEDIUM_VIOLET_RED") return colour_consts::MEDIUM_VIOLET_RED;
		if (name == "MIDNIGHT_BLUE") return colour_consts::MIDNIGHT_BLUE;
		if (name == "MINT_CREAM") return colour_consts::MINT_CREAM;
		if (name == "MISTY_ROSE") return colour_consts::MISTY_ROSE;
		if (name == "MOCCASIN") return colour_consts::MOCCASIN;
		if (name == "NAVAJO_WHITE") return colour_consts::NAVAJO_WHITE;
		if (name == "NAVY") return colour_consts::NAVY;
		if (name == "OLD_LACE") return colour_consts::OLD_LACE;
		if (name == "OLIVE") return colour_consts::OLIVE;
		if (name == "OLIVE_DRAB") return colour_consts::OLIVE_DRAB;
		if (name == "ORANGE") return colour_consts::ORANGE;
		if (name == "ORANGE_RED") return colour_consts::ORANGE_RED;
		if (name == "ORCHID") return colour_consts::ORCHID;
		if (name == "PALE_GOLDENROD") return colour_consts::PALE_GOLDENROD;
		if (name == "PALE_GREEN") return colour_consts::PALE_GREEN;
		if (name == "PALE_TURQUOISE") return colour_consts::PALE_TURQUOISE;
		if (name == "PALE_VIOLET_RED") return colour_consts::PALE_VIOLET_RED;
		if (name == "PAPAYA_WHIP") return colour_consts::PAPAYA_WHIP;
		if (name == "PEACH_PUFF") return colour_consts::PEACH_PUFF;
		if (name == "PERU") return colour_consts::PERU;
		if (name == "PINK") return colour_consts::PINK;
		if (name == "PLUM") return colour_consts::PLUM;
		if (name == "POWDER_BLUE") return colour_consts::POWDER_BLUE;
		if (name == "PURPLE") return colour_consts::PURPLE;
		if (name == "REBECCA_PURPLE") return colour_consts::REBECCA_PURPLE;
		if (name == "RED") return colour_consts::RED;
		if (name == "ROSY_BROWN") return colour_consts::ROSY_BROWN;
		if (name == "ROYAL_BLUE") return colour_consts::ROYAL_BLUE;
		if (name == "SADDLE_BROWN") return colour_consts::SADDLE_BROWN;
		if (name == "SALMON") return colour_consts::SALMON;
		if (name == "SANDY_BROWN") return colour_consts::SANDY_BROWN;
		if (name == "SEA_GREEN") return colour_consts::SEA_GREEN;
		if (name == "SEASHELL") return colour_consts::SEASHELL;
		if (name == "SIENNA") return colour_consts::SIENNA;
		if (name == "SILVER") return colour_consts::SILVER;
		if (name == "SKY_BLUE") return colour_consts::SKY_BLUE;
		if (name == "SLATE_BLUE") return colour_consts::SLATE_BLUE;
		if (name == "SLATE_GRAY") return colour_consts::SLATE_GRAY;
		if (name == "SLATE_GREY") return colour_consts::SLATE_GREY;
		if (name == "SNOW") return colour_consts::SNOW;
		if (name == "SPRING_GREEN") return colour_consts::SPRING_GREEN;
		if (name == "STEEL_BLUE") return colour_consts::STEEL_BLUE;
		if (name == "TAN") return colour_consts::TAN;
		if (name == "TEAL") return colour_consts::TEAL;
		if (name == "THISTLE") return colour_consts::THISTLE;
		if (name == "TOMATO") return colour_consts::TOMATO;
		if (name == "TURQUOISE") return colour_consts::TURQUOISE;
		if (name == "VIOLET") return colour_consts::VIOLET;
		if (name == "WHEAT") return colour_consts::WHEAT;
		if (name == "WHITE") return colour_consts::WHITE;
		if (name == "WHITE_SMOKE") return colour_consts::WHITE_SMOKE;
		if (name == "YELLOW") return colour_consts::YELLOW;
		if (name == "YELLOW_GREEN") return colour_consts::YELLOW_GREEN;
		return colour_consts::WHITE;
	}
}

#endif // !COLOUR_H


//const std::map<std::string, std::string> HTML_COLOURS = {
	//	{"AliceBlue", "f0f8ff"},
	//	{"AntiqueWhite", "faebd7"},
	//	{"Aqua", "00ffff"},
	//	{"Aquamarine", "7fffd4"},
	//	{"Azure", "f0ffff"},
	//	{"Beige", "f5f5dc"},
	//	{"Bisque", "ffe4c4"},
	//	{"Black", "000000"},
	//	{"BlanchedAlmond", "ffebcd"},
	//	{"Blue", "0000ff"},
	//	{"BlueViolet", "8a2be2"},
	//	{"Brown", "a52a2a"},
	//	{"Burlywood", "deb887"},
	//	{"CadetBlue", "5f9ea0"},
	//	{"Chartreuse", "7fff00"},
	//	{"Chocolate", "d2691e"},
	//	{"Coral", "ff7f50"},
	//	{"CornflowerBlue", "6495ed"},
	//	{"Cornsilk", "fff8dc"},
	//	{"Crimson", "dc143c"},
	//	{"Cyan", "00ffff"},
	//	{"DarkBlue", "00008b"},
	//	{"DarkCyan", "008b8b"},
	//	{"DarkGoldenrod", "b8860b"},
	//	{"DarkGray", "a9a9a9"},
	//	{"DarkGreen", "006400"},
	//	{"DarkGrey", "a9a9a9"},
	//	{"DarkKhaki", "bdb76b"},
	//	{"DarkMagenta", "8b008b"},
	//	{"DarkOliveGreen", "556b2f"},
	//	{"DarkOrange", "ff8c00"},
	//	{"DarkOrchid", "9932cc"},
	//	{"DarkEed", "8b0000"},
	//	{"DarkSalmon", "e9967a"},
	//	{"DarkSeaGreen", "8fbc8f"},
	//	{"DarkSlateBlue", "483d8b"},
	//	{"DarkSlateGray", "2f4f4f"},
	//	{"DarkSlateGrey", "2f4f4f"},
	//	{"DarkTurquoise", "00ced1"},
	//	{"DarkViolet", "9400d3"},
	//	{"DeepPink", "ff1493"},
	//	{"DeepSkyBlue", "00bfff"},
	//	{"DimGray", "696969"},
	//	{"DimGrey", "696969"},
	//	{"DodgerBlue", "1e90ff"},
	//	{"FireBrick", "b22222"},
	//	{"FloralWhite", "fffaf0"},
	//	{"ForestGreen", "228b22"},
	//	{"Fuchsia", "ff00ff"},
	//	{"Gainsboro", "dcdcdc"},
	//	{"GhostWhite", "f8f8ff"},
	//	{"Gold", "ffd700"},
	//	{"Goldenrod", "daa520"},
	//	{"Gray", "808080"},
	//	{"Green", "008000"},
	//	{"GreenYellow", "adff2f"},
	//	{"Grey", "808080"},
	//	{"Honeydew", "f0fff0"},
	//	{"HotPink", "ff69b4"},
	//	{"IndianRed", "cd5c5c"},
	//	{"Indigo", "4b0082"},
	//	{"Ivory", "fffff0"},
	//	{"Khaki", "f0e68c"},
	//	{"Lavender", "e6e6fa"},
	//	{"LavenderBlush", "fff0f5"},
	//	{"LawnGreen", "7cfc00"},
	//	{"LemonChiffon", "fffacd"},
	//	{"LightBlue", "add8e6"},
	//	{"LightCoral", "f08080"},
	//	{"LightCyan", "e0ffff"},
	//	{"LightGoldenrodYellow", "fafad2"},
	//	{"LightGray", "d3d3d3"},
	//	{"LightGreen", "90ee90"},
	//	{"LightGrey", "d3d3d3"},
	//	{"LightPink", "ffb6c1"},
	//	{"LightSalmon", "ffa07a"},
	//	{"LightSeaGreen", "20b2aa"},
	//	{"LightSkyBlue", "87cefa"},
	//	{"LightSlateGray", "778899"},
	//	{"LightSlateGrey", "778899"},
	//	{"LightSteelBlue", "b0c4de"},
	//	{"LightYellow", "ffffe0"},
	//	{"Lime", "00ff00"},
	//	{"LimeGreen", "32cd32"},
	//	{"Linen", "faf0e6"},
	//	{"Magenta", "ff00ff"},
	//	{"Maroon", "800000"},
	//	{"MediumAquamarine", "66cdaa"},
	//	{"MediumBlue", "0000cd"},
	//	{"MediumOrchid", "ba55d3"},
	//	{"MediumPurple", "9370db"},
	//	{"MediumSeaGreen", "3cb371"},
	//	{"MediumSlateBlue", "7b68ee"},
	//	{"MediumSpringGreen", "00fa9a"},
	//	{"MediumTurquoise", "48d1cc"},
	//	{"MediumVioletRed", "c71585"},
	//	{"MidnightBlue", "191970"},
	//	{"MintCream", "f5fffa"},
	//	{"MistyRose", "ffe4e1"},
	//	{"Moccasin", "ffe4b5"},
	//	{"NavajoWhite", "ffdead"},
	//	{"Navy", "000080"},
	//	{"OldLace", "fdf5e6"},
	//	{"Olive", "808000"},
	//	{"OliveDrab", "6b8e23"},
	//	{"Orange", "ffa500"},
	//	{"OrangeRed", "ff4500"},
	//	{"Orchid", "da70d6"},
	//	{"PaleGoldenrod", "eee8aa"},
	//	{"PaleGreen", "98fb98"},
	//	{"PaleTurquoise", "afeeee"},
	//	{"PaleVioletRed", "db7093"},
	//	{"PapayaWhip", "ffefd5"},
	//	{"PeachPuff", "ffdab9"},
	//	{"Peru", "cd853f"},
	//	{"Pink", "ffc0cb"},
	//	{"Plum", "dda0dd"},
	//	{"PowderBlue", "b0e0e6"},
	//	{"Purple", "800080"},
	//	{"RebeccaPurple", "663399"},
	//	{"Red", "ff0000"},
	//	{"RosyBrown", "bc8f8f"},
	//	{"RoyalBlue", "4169e1"},
	//	{"SaddleBrown", "8b4513"},
	//	{"Salmon", "fa8072"},
	//	{"SandyBrown", "f4a460"},
	//	{"SeaGreen", "2e8b57"},
	//	{"Seashell", "fff5ee"},
	//	{"Sienna", "a0522d"},
	//	{"Silver", "c0c0c0"},
	//	{"SkyBlue", "87ceeb"},
	//	{"SlateBlue", "6a5acd"},
	//	{"SlateGray", "708090"},
	//	{"SlateGrey", "708090"},
	//	{"Snow", "fffafa"},
	//	{"SpringGreen", "00ff7f"},
	//	{"SteelBlue", "4682b4"},
	//	{"Tan", "d2b48c"},
	//	{"Teal", "008080"},
	//	{"Thistle", "d8bfd8"},
	//	{"Tomato", "ff6347"},
	//	{"Turquoise", "40e0d0"},
	//	{"Violet", "ee82ee"},
	//	{"Wheat", "f5deb3"},
	//	{"White", "ffffff"},
	//	{"WhiteSmoke", "f5f5f5"},
	//	{"Yellow", "ffff00"},
	//	{"YellowGreen", "9acd32"}
	//};