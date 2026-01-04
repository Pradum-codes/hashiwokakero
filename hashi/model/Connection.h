#pragma once
enum class Orientation { HORIZONTAL, VERTICAL };

struct Connection {
    int islandA;
    int islandB;
    Orientation orientation;
    int bridges; // 0,1,2
};
