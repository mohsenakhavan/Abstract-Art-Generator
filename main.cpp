#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstdint>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"  // این هدر را دانلود و در کنار فایل C++ قرار دهید

const int WIDTH = 800;
const int HEIGHT = 600;

struct Color {
    uint8_t r, g, b;
};

Color randomColor() {
    return { static_cast<uint8_t>(rand() % 256), static_cast<uint8_t>(rand() % 256), static_cast<uint8_t>(rand() % 256) };
}

void drawRectangle(std::vector<Color>& pixels, int x, int y, int width, int height, Color color) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int px = x + j;
            int py = y + i;
            if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                pixels[py * WIDTH + px] = color;
            }
        }
    }
}

void drawCircle(std::vector<Color>& pixels, int cx, int cy, int radius, Color color) {
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            if (x*x + y*y <= radius*radius) {
                int px = cx + x;
                int py = cy + y;
                if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                    pixels[py * WIDTH + px] = color;
                }
            }
        }
    }
}

void drawLine(std::vector<Color>& pixels, int x0, int y0, int x1, int y1, Color color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    while (true) {
        if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT) {
            pixels[y0 * WIDTH + x0] = color;
        }
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

void drawPattern(std::vector<Color>& pixels) {
    int numShapes = 20 + rand() % 30;
    for (int i = 0; i < numShapes; ++i) {
        int shapeType = rand() % 3;
        Color color = randomColor();
        if (shapeType == 0) {
            // Draw Rectangle
            int width = 30 + rand() % 70;
            int height = 30 + rand() % 70;
            int x = rand() % WIDTH;
            int y = rand() % HEIGHT;
            drawRectangle(pixels, x, y, width, height, color);
        } else if (shapeType == 1) {
            // Draw Circle
            int radius = 20 + rand() % 50;
            int cx = rand() % WIDTH;
            int cy = rand() % HEIGHT;
            drawCircle(pixels, cx, cy, radius, color);
        } else {
            // Draw Line
            int x0 = rand() % WIDTH;
            int y0 = rand() % HEIGHT;
            int x1 = rand() % WIDTH;
            int y1 = rand() % HEIGHT;
            drawLine(pixels, x0, y0, x1, y1, color);
        }
    }
}

void createPNG(const std::string& filename, const int width, const int height, const std::vector<Color>& pixels) {
    std::vector<uint8_t> imageData(width * height * 3);
    for (int i = 0; i < width * height; ++i) {
        imageData[i * 3 + 0] = pixels[i].r;
        imageData[i * 3 + 1] = pixels[i].g;
        imageData[i * 3 + 2] = pixels[i].b;
    }
    stbi_write_png(filename.c_str(), width, height, 3, imageData.data(), width * 3);
}

void createAbstractArt() {
    std::vector<Color> pixels(WIDTH * HEIGHT, Color{255, 255, 255});
    drawPattern(pixels);
    createPNG("abstract_art.png", WIDTH, HEIGHT, pixels);
    std::cout << "Abstract art created: abstract_art.png" << std::endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    createAbstractArt();
    return 0;
}
