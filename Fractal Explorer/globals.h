#ifndef GLOBALS_H
#define GLOBALS_H

#include <thread>
#include <mutex>
#include <chrono>
#include <SFML\Config.hpp>
#include <condition_variable>
#include <complex>

using std::thread;
using std::mutex;
using std::unique_lock;
using std::lock;
using std::condition_variable;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::complex;

//global constants
const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_THREADS = 5;

//extern definitions
extern complex<double> k; //k variable for julia set
extern int maxIterations;
extern sf::Uint8 computedImage[WIDTH * HEIGHT * 4]; //Global variable to store the completed image to use as a texture in SFML. 32bpp RGBA, each pixel is 4 elements in the array
extern bool isRunning;
extern bool newJob;
extern condition_variable waitOnJob;
extern mutex jobCreator;
extern mutex iterationLock;

#endif