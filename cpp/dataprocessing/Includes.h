/**
\file Includes.h

A file containing all the requirement dependencies for all the classes, to simplify the include structure. 
All the headers should use #pragma once, as this file uses, so that everything is included only exactly once and there are no double definition errors.
*/
#ifndef HOMEPATH
#define HOMEPATH "/home/jiri/TPX3_Visualization/tpx3_datavisualizationserver/app/"
#endif

#ifndef DATAPATH
#define DATAPATH "/data/tpx3-visualization-data/"
#endif

#pragma once
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <limits.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdint.h>
#include <algorithm>
#include <unordered_set>
#ifdef _WIN32
	#include <Windows.h>
#else
	#include <ctime>
	#include <unistd.h>
#endif
#include "TimeUtils.h"
#include "Tools.h"