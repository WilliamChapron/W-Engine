#pragma once

#include "pch.h"
#include "RenderStructures.h"

// Points Map
static const std::string colors[] = {
    "Rouge",    // Coin 0 -> Rouge (Red)
    "Vert",     // Coin 1 -> Vert (Green)
    "Bleu",     // Coin 2 -> Bleu (Blue)
    "Jaune",    // Coin 3 -> Jaune (Yellow)
    "Magenta",  // Coin 4 -> Magenta (Magenta)
    "Cyan",     // Coin 5 -> Cyan (Cyan)
    "Orange",   // Coin 6 -> Orange (Orange)
    "Violet"    // Coin 7 -> Violet (Purple)
};

// Faces Map
std::map<std::string, std::vector<int>> faces = {
    {"Front", {0, 1, 2, 3}},
    {"Back", {4, 5, 6, 7}},
    {"Left", {0, 3, 7, 4}},
    {"Right", {1, 2, 6, 5}},
    {"Top", {2, 3, 7, 6}},
    {"Bottom", {0, 1, 5, 4}}
};

std::map<std::string, std::string> faceColors = {
    {"Front", "Jaune"},
    {"Back", "Vert"},
    {"Left", "Bleu"},
    {"Right", "Rouge"},
    {"Top", "Cyan"},
    {"Bottom", "Magenta"}
};









