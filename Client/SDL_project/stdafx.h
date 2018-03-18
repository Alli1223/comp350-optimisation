// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <SDL_image.h>
#include <SDL.h>






// Additional headers
#include <iostream>
#include <memory>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <set>
#include <list>
#include <math.h>
#include <fstream>
#include <thread>
#include <numeric>
#include <random>
#include <glm.hpp>
#include <unordered_map>

#define PI 3.14159265



//SDL TTF for writing to screen
#include <SDL_ttf.h>


// json parser
#include "json.hpp"
using json = nlohmann::json;