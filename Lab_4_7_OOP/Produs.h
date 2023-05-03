#pragma once
#include<iostream>
#include<string>
using std::string;
using std::cout;
 
class Produs {
private:
	std::string nume;
	std::string tip;
	std::string producator;
	float pret;
	bool sters = 0;//folosit pentru a marca produsul ca sters,fara a il sterge in mod real
	int cantitate = 1;
	
public:
	/*seteaza cantitatea curenta la cantitate_noua
	*/
	void set_cantitate(int cantitate_noua) noexcept {
		cantitate = cantitate_noua;
	}
	/*seteaza pretul curent la pret_nou*/
	void set_pret(float pret_nou) noexcept{
		pret = pret_nou;
	}
	/*seteaza producatorul curent la producator_nou*/
	void set_producator(string producator_nou) {
		producator = producator_nou;
	}
	/*seteaza atributul sters la valoarea lui sters_nou*/
	void set_sters(bool sters_nou) noexcept{
		sters = sters_nou;
	}
	Produs(const string n, const string t, const string pr, float pri) :nume{ n }, tip{ t }, producator{ pr }, pret{ pri }{}
	
	 Produs(const Produs& alt):tip{alt.tip},nume{alt.nume},producator{alt.producator},pret{alt.pret}{
		// cout << "!!!!!!!!!!!!!!!!!!!!\n";
	}
	
	bool get_sters() const noexcept {
		return sters;
	}
	string get_nume() const {
		return nume;
	}
	string get_producator() const {
		return producator;
	}
	string get_tip() const {
		return tip;
	}
	float get_pret() const noexcept {
		return pret;
	}
	int get_cantitate()const noexcept {
		return cantitate;
	}
};
/*
* Compara dupa nume
* returneaza true daca p1.nume<p2.nume
*/
bool Cmp_nume(const Produs& p1, const Produs& p2);
/*
* Compara dupa pret
* returneaza true daca p1.pret<p2.pret
*/
bool Cmp_pret(const Produs& p1, const Produs& p2) noexcept;
/*
* Compara dupa tip
* returneaza true daca p1.tip<p2.tip
*/
bool Cmp_tip(const Produs& p1, const Produs& p2);