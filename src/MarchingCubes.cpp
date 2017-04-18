#include "MarchingCubes.hpp"
#include "MarchingCubeTables.hpp"

void printVector(glm::vec3 toPrint) {
    std::cout << toPrint.x << " ";
    std::cout << toPrint.y << " ";
    std::cout << toPrint.z << " ";
    std::cout << std::endl;
}

MarchingCubes::MarchingCubes() {
    X_SIZE = 50.0f;
    Y_SIZE = 50.0f;
    Z_SIZE = 50.0f;
    inc = 0.5f;
    isoVal = 0.0f;

    cx = X_SIZE/2;
    cy = Y_SIZE/2;
    cz = Z_SIZE/2;

    radius = X_SIZE/2;
    
    init();
}

bool MarchingCubes::insideSurface(float x, float y, float z) {
    if (implicitFunction(x, y, z) <= isoVal) {
        return true;
    }
    else {
        return false;
    }
}

void MarchingCubes::init() {

    for (int i = 0; i < NUM_EDGES; i++) {
        vertList.push_back(glm::vec3(0));
    }
    for (float y = 0; y < Y_SIZE; y +=inc) {
        for (float z = 0; z < Z_SIZE; z +=inc) {
            for (float x = 0; x < X_SIZE; x +=inc) {
                int cubeIndex = getCubeIndex(x, y, z);
                currPoint = glm::vec3(x, y, z); 
                if (cubeIndex) { 
                    if (edgeTable[cubeIndex] != 0) {   
                        setVertList(edgeTable[cubeIndex]);        
                        // std::cout << std::endl;      
                        for (int i = 0; triTable[cubeIndex][i] != -1; i++) {
                            int triTableIdx = triTable[cubeIndex][i];
                            // if (addPoint) {                            
                                glm::vec3 vertex = vertList[triTableIdx];
                                // std::cout << triTableIdx << ": " ;
                                // std::cout << " pt: ";
                                // printVector(vertex);
                                vertices.push_back(vertex);
                            // }
                        }
                    }
                }
            } 
        }        
    }
}

/* takes in lower left back corner of cube (vertice 0) */
int MarchingCubes::getCubeIndex(float x, float y, float z) {
    int cubeIndex = 0;
    if (insideSurface(x, y, z)) {
        cubeIndex |= 1;
    }
    if (insideSurface(x + inc, y, z)) {
        cubeIndex |= 2;
    }
    if (insideSurface(x + inc, y, z + inc)) {
        cubeIndex |= 4;
    }
    if (insideSurface(x, y, z + inc)) {
        cubeIndex |= 8;
    }
    if (insideSurface(x, y + inc, z)) {
        cubeIndex |= 16;
    }
    if (insideSurface(x + inc, y + inc, z)) {
        cubeIndex |= 32;
    }
    if (insideSurface(x + inc, y + inc, z + inc)) {
        cubeIndex |= 64;
    }
    if (insideSurface(x, y + inc, z + inc)) {
        cubeIndex |= 128;
    }
    return cubeIndex;
}

glm::vec3 MarchingCubes::getPoint(float vertIdx) {
    // printf("vertIdx: %f\n", vertIdx);
    glm::vec3 point = currPoint;
    // printVec(currPoint);
    if (vertIdx == 1) {
        point.x += inc;
    }
    if (vertIdx == 2) {
        point.x += inc;
        point.z += inc;
    }
    if (vertIdx == 3) {
        point.z += inc;
    }
    if (vertIdx == 4) {
        point.y += inc;
    }
    if (vertIdx == 5) {
        point.y += inc;
        point.x += inc;
    }
    if (vertIdx == 6) {
        point.y += inc;
        point.x += inc;
        point.z += inc;
    }
    if (vertIdx == 7) {
        point.y += inc;
        point.z += inc;
    }
    // printf("point: \n");
    // printVec(point);
    return point;
}

glm::vec3 MarchingCubes::getVertInterp(int vert1Idx, int vert2Idx) {
    // printf("idx: %d %d\n", vert1Idx, vert2Idx);
    glm::vec3 toReturn;
    glm::vec3 p1, p2;
    float v1, v2, mu;

    p1 = getPoint(vert1Idx);
    p2 = getPoint(vert2Idx);

    // printVec(p1);
    // printVec(p2);

    v1 = implicitFunction(p1.x, p1.y, p1.z);
    v2 = implicitFunction(p2.x, p2.y, p2.z);

    if (abs(isoVal - v1) < 0.00001f) {
        return p1;
    }
    if (abs(isoVal - v2) < 0.00001f) {
        return p2;
    }
    if (abs(v1 - v2) < 0.00001f) {
        return p1;
    }

    mu = (isoVal - v1) / (v2 - v1);
    toReturn.x = p1.x + mu * (p2.x - p1.x);
    toReturn.y = p1.y + mu * (p2.y - p1.y);
    toReturn.z = p1.z + mu * (p2.z - p1.z);

    return toReturn;
}

void MarchingCubes::setVertList(int edgeTableVal) {
    if (edgeTableVal & 1) {
        vertList[0] = getVertInterp(0, 1);
    }
    if (edgeTableVal & 2) {
        vertList[1] = getVertInterp(1, 2);
    }
    if (edgeTableVal & 4) {
        vertList[2] = getVertInterp(2, 3);
    }
    if (edgeTableVal & 8) {
        vertList[3] = getVertInterp(3, 0);
    }
    if (edgeTableVal & 16) {
        vertList[4] = getVertInterp(4, 5);
    }
    if (edgeTableVal & 32) {
        vertList[5] = getVertInterp(5, 6);
    }
    if (edgeTableVal & 64) {
        vertList[6] = getVertInterp(6, 7);
    }
    if (edgeTableVal & 128) {
        vertList[7] = getVertInterp(7, 4);
    }
    if (edgeTableVal & 256) {
        vertList[8] = getVertInterp(0, 4);
    }
    if (edgeTableVal & 512) {
        vertList[9] = getVertInterp(1, 5);
    }
    if (edgeTableVal & 1024) {
        vertList[10] = getVertInterp(2, 6);
    }
    if (edgeTableVal & 2048) {
        vertList[11] = getVertInterp(3, 7);
    }
}



float MarchingCubes::implicitFunction(float x, float y, float z) {
    float xComp, yComp, zComp, outPut;
    xComp = pow(x - cx, 2);
    yComp = pow(y - cy, 2);
    zComp = pow(z - cz, 2);

    return xComp + yComp + zComp - (radius * radius);

    // // return ((x*x + y*y -1) * (x*x + y*y -1) * (x*x + y*y -1)) -(x*x*y*y*y);
    // // return sin(x+y) - cos(x*y) + z;
    // // return x*x*x-3*x -2*y*y;
    // // return z*y -x*x;
    // // return cos(x+y)-z*sin(x-y)-4;

    // glm::vec3 Pos = glm::vec3(x, y, z);
    // glm::vec3 P = Pos * 3.0f;
    // return sinf(P.x * P.y + P.x * P.z + P.y * P.z) + sinf(P.x * P.y) + sinf(P.y * P.z) + sinf(P.x * P.z) - 1.0f;
}


std::vector<glm::vec3> MarchingCubes::getVertices() {
    return vertices;
}

glm::vec3 MarchingCubes::getCenter() {
    return glm::vec3(X_SIZE/2, Y_SIZE/2, Z_SIZE/2);
}

glm::vec3 MarchingCubes::getGridSize() {
    return glm::vec3(X_SIZE, Y_SIZE, Z_SIZE);
}