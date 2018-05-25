#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Geometry/LineSegment.h"
#include "Vector/Vector.h"

using namespace mhe;

int main(void)
{
	Vec3f a(0, 0, 0);
	Vec3f b(1, 1, 1);
	LineSegment<Vec3f> ls(a, b);

	std::cout << ls.length() << std::endl;

	system("pause");
	return 0;
}