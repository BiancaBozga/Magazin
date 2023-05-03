#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "Produs.h"
#include "validator.h"
#include<random>
using std::string;

class Cos {
private:
	std::vector<Produs> produse_cos;
	ProdusValidator& val;
	float total=0;
	bool sters = 0;
public:
	friend class ServiceP;
	Cos(ProdusValidator& val)noexcept :val{ val }{}
	//actualizeaza total la total_nou
	void set_total(float total_nou) noexcept{
		total = total_nou;
	}
	float get_total() noexcept{
		return total;
	}
	void set_sters(bool sters1) noexcept{
		sters = sters1;
	}
	bool get_setrs() noexcept{
		return sters;
	}
	//marcheaza cosul ca sters
	void sterge_cos() noexcept;
	//adauga produsul p la cos, p-Produs
	void adauga_produs_in_cos(Produs p);
	//returneaza produsele existente in cos
	const vector<Produs>& get_all() const noexcept {
		return produse_cos;
	}
	//return: size_t-numarul de produse din cos
	size_t get_size() noexcept{
		return produse_cos.size();
	}
	/*
	* genereaza random produse din aplicatie
	* numar_produse-nr produse de generat
	* produse_existente-produse de tipul Produs existente in aplicatie
	*/
	void adauga_produse_random(std::vector<Produs> produse_existente, int numar_produse);
};
