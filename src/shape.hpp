#ifndef SSSIM_SHAPE
#define SSSIM_SHAPE

#include <utility>

namespace sssim
{
class Triangle
{
public:
    using CoordType  = double;
    using Coordinate = std::pair<CoordType, CoordType>;

public:
    Triangle(Coordinate, Coordinate, Coordinate);

private:
    unsigned int VBOid_;
};

}  // namespace sssim

#endif  // SSSIM_SHAPE
