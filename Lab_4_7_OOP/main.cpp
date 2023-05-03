#include "Produs.h"
#include "Service_magazin.h"
#include "UI.h"
void test_all() {
	
	
	teste_service();

	testeRepo();
	testValidator();
}
int main() {
	test_all();

	RepoPFile repo{"in_2.txt"};
	ProdusValidator val;
	Cos cos{ val };
	ServiceP service{ repo,val,cos };
	UI ui{ service };
	ui.start();
	
	return 0;
}