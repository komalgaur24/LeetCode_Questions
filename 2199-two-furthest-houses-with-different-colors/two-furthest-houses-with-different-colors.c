int maxDistance(int* colors, int colorsSize) {
    for (int i = 0; i < colorsSize + 1 / 2; i++) {
        if (colors[0] != colors[colorsSize - 1 - i] || colors[colorsSize - 1] != colors[i]) {
            return colorsSize - 1 - i;
        }
    }
    return 0; // avoid compiler warning
}