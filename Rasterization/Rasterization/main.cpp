#include<iostream>

class vec2 {
protected:
	float x, y;
public:
	vec2(float x, float y) : x(x), y(y) {};
	static float cross(vec2 a,vec2 b) {
		return a.x*b.y-a.y*b.x;
	}
	vec2 operator -(vec2 v) {
		return vec2(x - v.x, y - v.y);
	}
};

bool insiderTriangle(vec2 p, vec2 a, vec2 b, vec2 c) {
	float cross1 = vec2::cross((b - a),(p - a));
	float cross2 = vec2::cross((c - b), (p - b));
	float cross3 = vec2::cross((a - c), (p - c));
	return (cross1 > 0 && cross2 > 0 && cross3 > 0) || (cross1 < 0 && cross2 < 0 && cross3 < 0);
}

int main() {
	vec2 a(0, 0);
	vec2 b(1, 0);
	vec2 c(0, 1);
	vec2 p(0.5, 0.5);
	std::cout << insiderTriangle(p, a, b, c) << std::endl;
	return 0;
}