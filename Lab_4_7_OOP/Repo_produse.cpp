#include "Repo_produse.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;
/*
*/
bool RepoP::exista(const Produs& p) const {
	
	try {
		cauta(p.get_nume(), p.get_tip());
		return true;
	}
	catch (RepoP_exceptie& ) {
		return false;}

}
void RepoP::sterge_repo(const string& nume, const string& tip) {
	int ok = 0, poz = 0;
	for (auto& p : produse)
	{
		
		if (p.get_nume() == nume && p.get_tip() == tip)
		{
			ok = 1;
			p.set_sters(1);
			break;

		}
		poz++;
	}
	if (ok == 1)
		produse.erase(produse.begin()+poz);
	if (ok != 1)
		throw RepoP_exceptie("Nu exista produsul tip:" + tip + " si numele:" + nume);
}
void RepoP::modifica_repo(const Produs& p_nou) {
	int ok =0;
	for (auto& p : produse) 
		if (p.get_nume() == p_nou.get_nume() && p.get_tip() ==p_nou.get_tip())
		{
			ok = 1;
			p.set_pret(p_nou.get_pret());
			p.set_producator(p_nou.get_producator());

		}
		if(ok!=1)
			throw RepoP_exceptie("Nu exista produsul tip:" + p_nou.get_tip() + " si numele:" + p_nou.get_nume());
	    
}
/*
*/
void RepoP::adauga_repo(const Produs& p) {
	
	if (exista(p)) {
		
			throw RepoP_exceptie("Exista deja produsul tip:" + p.get_tip() + " si numele:" + p.get_nume());
	
	}
	produse.push_back(p);
	
}
const Produs& RepoP::cauta(string nume, string tip) const{
	for (const auto& p : produse) {
		if (p.get_nume() == nume && p.get_tip() == tip && p.get_sters()==0)
			return p;
	}
	throw RepoP_exceptie("Nu exista produsul cautat!\n");}
/*
*/
const vector<Produs>& RepoP::get_all() const noexcept {
	return produse;
}

ostream& operator<<(ostream& out, const RepoP_exceptie& ex) {
	out << ex.msg;
	return out;
}
void test_adauga() {
	RepoP repo;
	constexpr float pret = 33;
	const Produs p{ "aa","bb","Avon",pret };
	repo.adauga_repo(p);
	assert(repo.get_all().size() == 1);
	assert(repo.cauta(p.get_nume(), p.get_tip()).get_nume() == "aa");
	try {
		repo.adauga_repo(p);
		//assert(false);
	}
	catch (const RepoP_exceptie&) {
		assert(true);
	}
	
}
void test_cauta() {
	
	RepoP rep;
	rep.adauga_repo(Produs{ "aa","bb","cc",40 });
	rep.adauga_repo(Produs{ "dd","ee","ff",77.5 });

	auto& p = rep.cauta("aa", "bb");
	assert(p.get_nume() == "aa");
	assert(p.get_tip() == "bb");
	try {
		rep.sterge_repo("aa", "ee");
		//assert(false);
	}
	catch (RepoP_exceptie&) {
		assert(true);
	}
	 Produs c{ "aa", "ee" ,"ww",23 };
	try {
		rep.modifica_repo(c);
		//assert(false);
	}
	catch (RepoP_exceptie&) {
		assert(true);
	}
	//arunca exceptie daca nu gaseste
	try {
		rep.cauta("aa", "ee");
		//assert(false);
	}
	catch (RepoP_exceptie&) {
		assert(true);
	}
	
	
}

void testeRepo() {
	test_adauga();
	test_cauta();
	
}