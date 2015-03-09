#ifndef GLOBALS_H
#define GLOBALS_H

#include <thread>
#include <mutex>
#include <SFML\Config.hpp>

using std::thread;
using std::mutex;

const int WIDTH = 800;
const int HEIGHT = 600;

extern mutex iterationLock;
extern int maxIterations;
extern sf::Uint8 computedImage[WIDTH * HEIGHT * 4]; //Global variable to store the completed image to use as a texture in SFML. 32bpp RGBA, each pixel is 4 elements in the array

#endif