#include "src/Quaternion.h"
#include <cmath>
#include <iostream>
using namespace std;

int main(int, char**) {
	Vector* axis = new Vector(0, 1, 0);
	Vector* patient = new Vector(1, 0, 0);

	*patient = Quaternion(*axis, acos(-1)).Transform(*patient);
	cout << patient->ToString() << endl;

	delete axis;
	delete patient;
	return 0;
}
