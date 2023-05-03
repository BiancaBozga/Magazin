#include "Cos.h"
using std::shuffle;
void Cos::sterge_cos() noexcept {
	set_sters(1);
}
void Cos::adauga_produs_in_cos(Produs d) {
	val.validare(d);
	set_sters(0);
	produse_cos.push_back(d);
	set_total(get_total() + d.get_pret());
	   
		/*bool produs_gasit = false;
		for (auto& p : produse_cos) {
			if (p.get_nume() == d.get_nume() && p.get_tip() == d.get_tip())
			{
				produs_gasit = true;
				
				p.set_pret(p.get_pret() + p.get_pret() / p.get_cantitate());
				p.set_cantitate(p.get_cantitate() + 1);
				
				set_total(get_total() + p.get_pret() / p.get_cantitate());
				
				break;
			}
			
		}
		if (!produs_gasit) {
			//cout << d.get_nume() << " ";
			//d.set_cantitate(1);
			produse_cos.push_back(d);
			set_total(get_total() + d.get_pret());
		}*/
		
	
}
void Cos::adauga_produse_random(std::vector<Produs> produse_existente, int numar_produse) {
	shuffle(produse_existente.begin(), produse_existente.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (produse_cos.size() < numar_produse ) {
	    set_sters(0);
		adauga_produs_in_cos(produse_existente.back());
		shuffle(produse_existente.begin(), produse_existente.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul
		
	}
}


