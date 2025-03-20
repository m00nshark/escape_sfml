#pragma once

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

int clamp(int x, int a, int b)
{
	return MAX(MIN(x, b), a);
}