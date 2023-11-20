#ifndef __PATH_H__
#define __PATH_H__

#include <vector>

struct Path
{
	std::vector<USVec2D> PointList;
};

bool ReadPathFromFile(const char* filename, Path& path);

#endif