#include <list>
#include "Shapes.h"

class Sort {

  public :static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList);

		  static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList);
		  
		  static void sortByIncreasingArea(std::list<Shape *> * shapeList);
		  
		  static void sortByDecreasingArea(std::list<Shape *> * shapeList);
		  
		  static void sortByIncreasingCompactness(std::list<Shape *> * shapeList);

  
};

bool compareIncreasePerimeter(Shape const * first, Shape const * second){
	return first->perimeter() < second->perimeter();
}

bool compareDecreasePerimeter(Shape const * first, Shape const * second){
	return first->perimeter() > second->perimeter();
}

bool compareIecreaseArea(Shape const * first, Shape const * second){
	return first->area() < second->area();
}

bool compareDecreaseArea(Shape const * first, Shape const * second){
	return first->area() > second->area();
}

bool compareIncreasingCompactness(Shape const * first, Shape const * second){
	return first->area() < second->area();
}

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
	shapeList->sort(compareIncreasePerimeter);
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
	shapeList->sort(compareDecreasePerimeter);
}
void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList){
	shapeList->sort(compareIecreaseArea);
}
void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList){
	shapeList->sort(compareDecreaseArea);
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList){
	shapeList->sort(compareIncreasingCompactness);
}
