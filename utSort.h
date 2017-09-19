#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

TEST (Sort, sortByIncreasingPerimeter) {
	Rectangle rect(0, 0, 5, 5, "rect");

	Circle cir0(0, 0, 5, "cir0");

	Triangle tri(vertex{2, 0}, vertex{0, 3}, vertex{0, 1}, "tri");

	std::list<Shape *> shapesList;
	shapesList.push_back(&cir0);
	shapesList.push_back(&rect);
	shapesList.push_back(&tri);

	Sort::sortByIncreasingPerimeter(&shapesList);

	std::list<Shape *>::iterator it;
	it = shapesList.begin();
	ASSERT_EQ(&tri,  *it++);
	ASSERT_EQ(&rect, *it++);
	ASSERT_EQ(&cir0, *it);
}

TEST (Sort, sortByDecreasingPerimeter) {
	Rectangle rect(0, 0, 5, 5, "rect");

	Circle cir0(0, 0, 5, "cir0");


	Triangle tri(vertex{ 2, 0 }, vertex{ 0, 3 }, vertex{ 0, 1 }, "tri");


	std::list<Shape *> shapesList;
	shapesList.push_back(&cir0);
	shapesList.push_back(&rect);
	shapesList.push_back(&tri);

	Sort::sortByDecreasingPerimeter(&shapesList);

	std::list<Shape *>::iterator it;
	it = shapesList.begin();
	ASSERT_EQ(&cir0, *it++);
	ASSERT_EQ(&rect, *it++);
	ASSERT_EQ(&tri, *it);
}

TEST (Sort, sortByIncreasingArea) {
	Rectangle rect(0, 0, 5, 5, "rect");

	Circle cir0(0, 0, 5, "cir0");

	Triangle tri(vertex{ 2, 0 }, vertex{ 0, 3 }, vertex{ 0, 1 }, "tri");


	std::list<Shape *> shapesList;
	shapesList.push_back(&cir0);
	shapesList.push_back(&rect);
	shapesList.push_back(&tri);

	Sort::sortByIncreasingArea(&shapesList);

	std::list<Shape *>::iterator it;
	it = shapesList.begin();
	ASSERT_EQ(&tri, *it++);
	ASSERT_EQ(&rect, *it++);
	ASSERT_EQ(&cir0, *it);
}

TEST (Sort, sortByDecreasingArea) {
	Rectangle rect(0, 0, 5, 5, "rect");

	Circle cir0(0, 0, 5, "cir0");


	Triangle tri(vertex{ 2, 0 }, vertex{ 0, 3 }, vertex{ 0, 1 }, "tri");


	std::list<Shape *> shapesList;
	shapesList.push_back(&cir0);
	shapesList.push_back(&rect);
	shapesList.push_back(&tri);

	Sort::sortByDecreasingArea(&shapesList);

	std::list<Shape *>::iterator it;
	it = shapesList.begin();
	ASSERT_EQ(&cir0, *it++);
	ASSERT_EQ(&rect, *it++);
	ASSERT_EQ(&tri, *it);
}

TEST (Sort, sortByIncreasingCompactness) {
	Rectangle rect(0, 0, 5, 5, "rect");

	Circle cir0(0, 0, 5, "cir0");


	Triangle tri(vertex{ 2, 0 }, vertex{ 0, 3 }, vertex{ 0, 1 }, "tri");

	std::list<Shape *> shapesList;
	shapesList.push_back(&cir0);
	shapesList.push_back(&rect);
	shapesList.push_back(&tri);

	Sort::sortByIncreasingCompactness(&shapesList);

	std::list<Shape *>::iterator it;
	it = shapesList.begin();
	ASSERT_EQ(&tri, *it++);
	ASSERT_EQ(&rect, *it++);
	ASSERT_EQ(&cir0, *it);
}

#endif
