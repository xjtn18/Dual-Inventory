#include <iostream>
#include "debug.h"
#include "Inventory.h"
#include "Items.h"



int main(){
	Inventory* I = new Inventory();
	I->add(new Apple());
	log(I->getCurrentItem()->getName());
	return 0;
}
