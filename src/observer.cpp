#include "observer.h"
#include <vector>

// Adds an observer to the list of observers
void Observable::addObserver(Observer* observer) {
	observers.push_back(observer);
};

// Notifies all observers of an update
void Observable::notifyUpdate() {
	for (auto& observer : observers){
		observer->update();  // Calls the update method on each observer
	}
};
