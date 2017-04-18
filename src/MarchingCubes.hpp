#ifndef MatchingCubes_HPP
#define MatchingCubes_HPP

#define NUM_EDGES 12

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <glm/glm.hpp>

class MarchingCubes {
public:
	MarchingCubes();
	void init();

	float implicitFunction(float x, float y, float z);
	bool insideSurface(float x, float y, float z);
	int getCubeIndex(float x, float y, float z);
	glm::vec3 getPoint(float vertIdx);
	glm::vec3 getVertInterp(int vert1Idx, int vert2Idx);
	void setVertList(int edgeTableVal);

	std::vector<glm::vec3> getVertices();
	glm::vec3 getCenter();
	glm::vec3 getGridSize();

private:
	std::vector<glm::vec3> vertices;
	float X_SIZE;
	float Y_SIZE;
	float Z_SIZE;
	
	float cx, cy, cz;
	float inc;
	float isoVal;
	float radius;
	
	std::vector<glm::vec3> vertList;
	glm::vec3 currPoint;
};
  
#endif





