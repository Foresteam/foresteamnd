#include "src/Quaternion.h"
#include "src/Matrix.h"
#include <cmath>
#include <iostream>
using namespace std;

void Test(string prefix, string a, string b, int& passed, int& total) {
	total++;
	bool ok = a.compare(b.c_str()) == 0;
	passed += ok;
	printf("%s: \u001b[37;1m%s\u001b[0m \u001b[36mVs\u001b[0m \u001b[37;1m%s\u001b[0m. %s\n", prefix.c_str(), a.c_str(), b.c_str(), ok ? "\u001b[32mOk\u001b[0m" : "\u001b[31mFailed\u001b[0m");
}

int main(int, char**) {
	Vector axis = Vector(0, 1, 0);
	Vector target = Vector(1, 0, 0);
	Quaternion q = Quaternion(axis, acos(0));

	printf("*Tests*\n");
	int total = 0, passed = 0;
	Test("'axis'", axis.ToString().c_str(), "Vector3D(0, 1, 0)", passed, total);
	Test("'target'", target.ToString().c_str(), "Vector3D(1, 0, 0)", passed, total);
	Test("'q'", q.ToString().c_str(), "Quaternion(0, 0.707107, 0, 0.707107)", passed, total);
	target = (q * target);
	Test("'target', rotated around 'axis' 90deg", target.ToString().c_str(), "Vector3D(0, 0, -1)", passed, total);
	Test("'target', rotated back 90deg", (target * Quaternion(axis, -acos(0))).ToString().c_str(), "Vector3D(1, 0, 0)", passed, total);

	printf("%sTests completed\u001b[0m. %i of %i passed.\n", passed == total ? "\u001b[32m" : "\u001b[33m", passed, total);

	return 0;
}
