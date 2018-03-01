/*Copyright reserved by KenLee@2017 ken4000kl@gmail.com*/
#ifndef GEOMETRY_H
#define GEOMETRY_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "Shape.h"
#include <cmath>
#include <vector>
#include <unordered_map>
#include <memory>

//
//	�����ࣨShape ��Ĺ����ࣩ
//
class Geometry {
public:
    // ����һ������(UV��)
    static std::unique_ptr<Shape> createUVSphere();
    // ����һ������(20����ϸ�ַ�)
    static std::unique_ptr<Shape> createIcoSphere(const int level);
    // ����һ��������
    static std::unique_ptr<Shape> createCube();
    // ����һ��������(Ĭ����XoZƽ����)
    static std::unique_ptr<Shape> createQuad(const GLfloat width = 1.0f, const GLfloat height = 1.0f);
private:
    // createIcoSphere ����
    static int createIcoSphere_GetMiddle(std::unordered_map<long long int, GLuint> &vertexHash,
                         std::vector<glm::vec3> &vertices, int index1, int index2);

};

#endif
