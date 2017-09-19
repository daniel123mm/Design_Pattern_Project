#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

std::list<Shape *> shapesList;
Rectangle rect(0, 0, 5, 5, "rect");
Circle cir0(0, 0, 5, "cir0");
Triangle tri(vertex{2, 0}, vertex{0, 3}, vertex{0, 1}, "tri");

void init(){
	shapesList.push_back(&cir0);
	shapesList.push_back(&rect);
	shapesList.push_back(&tri);
}

TEST (Sort, sortByIncreasingPerimeter) {
	init();
	
	Sort::sortByIncreasingPerimeter(&shapesList);

	std::list<Shape *>::iterator it;
	it = shapesList.begin();
	ASSERT_EQ(&tri,  *it++);
	ASSERT_EQ(&rect, *it++);
	ASSERT_EQ(&cir0, *it);
}

TEST (Sort, sortByDecreasingPerimeter) {
	Sort::sortByDecreasingPerimeter(&shapesList);

	std::list<Shape *>::iterator it;
	it = shapesList.begin();
	ASSERT_EQ(&cir0, *it++);
	ASSERT_EQ(&rect, *it++);
	ASSERT_EQ(&tri, *it);
}

TEST (Sort, sortByIncreasingArea) {
	Sort::sortByIncreasingArea(&shapesList);

	std::list<Shape *>::iterator it;
	it = shapesList.begin();
	ASSERT_EQ(&tri, *it++);
	ASSERT_EQ(&rect, *it++);
	ASSERT_EQ(&cir0, *it);
}

TEST (Sort, sortByDecreasingArea) {
	Sort::sortByDecreasingArea(&shapesList);

	std::list<Shape *>::iterator it;
	it = shapesList.begin();
	ASSERT_EQ(&cir0, *it++);
	ASSERT_EQ(&rect, *it++);
	ASSERT_EQ(&tri, *it);
}

TEST (Sort, sortByIncreasingCompactness) {
	Sort::sortByIncreasingCompactness(&shapesList);
	
	std::list<Shape *>::iterator it;
	it = shapesList.begin();
	ASSERT_EQ(&tri, *it++);
	ASSERT_EQ(&rect, *it++);
	ASSERT_EQ(&cir0, *it);
}

#endif
