#pragma once
#include "validator.h"
#include"RepoPFile.h"
#include "Cos.h"
#include"Undo.h"
#include<vector>
#include<string>
#include<functional>
#include<map>
using std::vector;
using std::string;
using std::function;
using std::unique_ptr;

class ServiceP {
	
	RepoPFile& repo;
	ProdusValidator& val;
	vector<Produs> generalSort(bool(*maiMicF)(const Produs&, const Produs&));
	std::vector<unique_ptr<Actiune_undo>> undo_actiuni;
	Cos& cos;
public:
	
	ServiceP(RepoPFile& repo, ProdusValidator& val, Cos& cos) noexcept :repo{ repo }, val{ val }, cos{ cos } {}
	ServiceP(const ServiceP& alt) = delete;
	
	const vector<Produs>& get_all_service() noexcept {
		return repo.get_all();
	}
	const vector<Produs>& get_all_cos() noexcept {
		return cos.get_all();
	}
	float get_total() noexcept{
		return cos.get_total();
	}
	bool get_sters_cos() noexcept{
		return cos.get_setrs();
	}
	void sterge_cos() noexcept{
		cos.sterge_cos();
	}
	void undo();
	void adauga_service(const string& nume, const string& tip, const string& producator, float pret);
	void modifica_service(const string& nume, const string& tip, float pret, const string& producator);
	void sterge_service(const string& nume, const string& tip);
	bool cauta_produs(const string& nume, const string& tip);
	/*
	Sorteaza dupa pret
	*/
	vector<Produs> sorteaza_dupa_pret();

	/*
	Sorteaza dupa nume
	*/
	vector<Produs> sorteaza_dupa_nume();


	/*
	Sorteaza dupa nume+tip
	*/
	vector<Produs> sorteaza_dupa_nume_si_tip();
	vector<Produs> filtreaza(function<bool(const Produs&)> fct);
	vector<Produs> filtrare_pret(float pret) ;
	vector<Produs> filtrare_nume(string nume);
	vector<Produs> filtrare_producator(string producator);
	void adauga_cos_service(string nume, string tip);
	std::map<std::string, int> cate_produse();
	size_t adauga_produse_random_service(int cate_p);
};
void teste_service();