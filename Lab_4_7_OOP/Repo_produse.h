#pragma once
#include "Produs.h"

#include<vector>
#include<string>
#include<ostream>

using std::vector;
using std::string;
using std::ostream;

class RepoP {
	vector<Produs> produse;
	/*
	* verifica daca exista produsul p in repo
	*/
	/*verfica daca exista p de tipul Produs in aplicatie
	* return:false, daca nu exista;true,altfel
	*/
	bool exista(const Produs& p) const;
public:
	
	RepoP() = default;
	//nu permitem copiere repo
	RepoP(const Produs& alt) = delete;
	/*Adauga p de tipul Produs in repo
	* return:none
	* arunca exceptie de tipul RepoP_exceptie daca exista deja un produs cu nume=p.nume si tip=p.tip
	*/
	virtual void adauga_repo(const Produs& p);
	/*Modifica atribut-ul producator si pret pentru p de tip Produs,daca exista
	* return:none
	* arunca exceptie de tipul RepoP_exceptie daca nu exista p de tipul Produs in aplicatie 
	*/
	virtual void modifica_repo(const Produs& p);
	/*Sterge produsul cu numele=nume si tip=tip, si ii seteaza atributul sters la 1
	* return:none
	* arunca exceptie de tipul RepoP_exceptie daca nu exista un produs cu numele nume si tipul tip in aplicatie 
	*/
	virtual void sterge_repo(const string& nume,const string& tip);
	/*Cauta produsul cu numele nume si tip-ul tip 
	* return:const Produs&-dace exista, arunca exceptie de tipul RepoP_exceptie, altfel
	*/
	const Produs& cauta(string nume, string tip) const;
    const vector<Produs>& get_all() const noexcept;
	
	

};
class RepoP_exceptie {
	string msg;
public:
	RepoP_exceptie(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const RepoP_exceptie& ex);
};

ostream& operator<<(ostream& out, const RepoP_exceptie& ex);

void testeRepo();