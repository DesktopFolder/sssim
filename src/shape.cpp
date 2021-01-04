#include "shape.hpp"

#include "graphics.hpp"

sssim::Triangle::Triangle(Coordinate p1, Coordinate p2, Coordinate p3)
{
    sssim::Triangle::CoordType vertices[] = {p1.first, p1.second, 0.0f,      p2.first, p2.second,
                                             0.0f,     p3.first,  p3.second, 0.0f};
    glGenBuffers(1, &VBOid_);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
