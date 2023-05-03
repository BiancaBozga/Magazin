#include "Service_magazin.h"
#include<iostream>
#include<filesystem>
#include<string>
#include<assert.h>
#include<map>


vector<Produs> ServiceP::generalSort(bool(*maiMicF)(const Produs&, const Produs&)) {
	vector<Produs> v{ repo.get_all() };//fac o copie	
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (maiMicF!=nullptr && !maiMicF(v[i], v[j])) {
				//interschimbam
				Produs aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}
vector<Produs> ServiceP::sorteaza_dupa_nume() {
	return generalSort(Cmp_nume);
}
vector<Produs>ServiceP::filtrare_producator(string producator) {
	return filtreaza([producator](const Produs& p) {return p.get_producator() == producator; });
}

vector<Produs> ServiceP::filtreaza(function<bool(const Produs&)> fct) {
	vector<Produs> rez;
	for ( const auto&  p : repo.get_all())
		if (fct(p))
			rez.push_back(p);
	return rez;
}
vector<Produs> ServiceP::filtrare_nume(string nume) {
	return filtreaza([nume](const Produs& p) {return p.get_nume() == nume; });
}
vector<Produs> ServiceP::filtrare_pret(float pret)  {
	return filtreaza([pret](const Produs& p) {return p.get_pret() > pret; });
}
vector<Produs> ServiceP::sorteaza_dupa_nume_si_tip() {
	return generalSort([](const Produs& p1, const Produs& p2) {
		if (p1.get_nume() == p2.get_nume()) {
			return Cmp_tip(p1,p2);
		}
		return p1.get_nume() < p2.get_nume();
		});

}

void ServiceP::undo() {
	if (undo_actiuni.empty())
		throw RepoP_exceptie("Nu se mai poate face undo!!");
	undo_actiuni.back()->do_undo();
	undo_actiuni.pop_back();
}
vector<Produs> ServiceP::sorteaza_dupa_pret() {
	return generalSort(Cmp_pret);
}
void ServiceP::adauga_service(const string& nume, const string& tip, const string& producator, float pret) {
	const Produs& p{ nume,tip,producator,pret };
	val.validare(p);
	repo.adauga_repo(p);
	undo_actiuni.push_back(std::make_unique<undo_adauga>(p, repo));
	
}
bool ServiceP::cauta_produs(const string& nume, const string& tip) {
	repo.cauta(nume, tip);
	return true;
}
void ServiceP::modifica_service(const string& nume, const string& tip, float pret, const string& producator) {
	Produs d = repo.cauta(nume, tip);
	Produs p{ nume,tip,producator,pret };
	val.validare(p);
	undo_actiuni.push_back(std::make_unique<undo_mod>(d, repo));
	repo.modifica_repo(p);
}
void ServiceP::sterge_service(const string& nume, const string& tip) {
	Produs p = repo.cauta(nume, tip);
	undo_actiuni.push_back(std::make_unique<undo_sterge>(p, repo));
	repo.sterge_repo(nume, tip);
	

}
void ServiceP::adauga_cos_service(string nume, string tip) {
	Produs p=repo.cauta(nume, tip);
	
	cos.adauga_produs_in_cos(p);

}


std::map<std::string, int> ServiceP::cate_produse() {
	std::map<std::string, int> dictionar;
	for (auto i : this->get_all_cos())
		dictionar[i.get_tip()] = 0;
	for (auto i : this->get_all_cos())
		dictionar[i.get_tip()] += i.get_cantitate();
	return dictionar;

}
size_t ServiceP::adauga_produse_random_service(int cate_p) {
	cos.adauga_produse_random(repo.get_all(), cate_p);
	return cos.get_all().size();
}

void teste_adauga() {
	RepoPFile rep{ "C:\\Users\\BOZGA\\source\\repos\\Lab_4_7_OOP - Copy\\Lab_4_7_OOP\\in.txt" };
	ProdusValidator val;

	Cos cos{ val};
	ServiceP ctr{ rep,val,cos };
	ctr.adauga_service("aa", "aa", "bb",6);
	
	assert(ctr.get_all_service().size() == 1);
	assert(ctr.get_all_service()[0].get_sters() == 0);
	//adaug ceva invalid
	try {
		ctr.adauga_service("", "", "", - 1);
		//assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	//incerc sa adaug ceva ce existadeja
	try {
		ctr.adauga_service("aa", "aa", "ff", - 1);
		//assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}



	assert(ctr.cauta_produs("aa", "aa") == true);
	ctr.modifica_service("aa", "aa", 900,"ff");
	assert(ctr.get_all_service()[0].get_producator () == "ff");
	ctr.adauga_cos_service("aa", "aa");
	assert(ctr.get_all_cos()[0].get_cantitate() == 1);
	ctr.adauga_cos_service("aa", "aa");
	assert(ctr.get_all_cos()[0].get_cantitate() == 1);
	assert(cos.get_setrs() == 0);
	ctr.sterge_cos();
	assert(cos.get_setrs() == 1);
	ctr.sterge_service("aa", "aa");
	assert(ctr.get_all_service().size() == 0);
	std::map<std::string, int> dictionar = ctr.cate_produse();
	ctr.undo();
	rep.goleste_fisier();
}
void testFiltrare() {

	RepoPFile rep{ "C:\\Users\\BOZGA\\source\\repos\\Lab_4_7_OOP - Copy\\Lab_4_7_OOP\\in.txt" };
	
	ProdusValidator val;
	Cos cos{ val };
	ServiceP ctr{ rep,val,cos };
	ctr.adauga_service("a", "a", "c",6);
	ctr.adauga_service("b", "a", "c",60);
	ctr.adauga_service("a", "d", "c",600);
	assert(ctr.filtrare_pret(70).size() == 1);
	assert(ctr.filtrare_pret(800).size() == 0);
	assert(ctr.filtrare_nume("a").size() == 2);
	assert(ctr.filtrare_producator("c").size() == 3);
	

	ctr.adauga_produse_random_service(15);
	assert(ctr.get_all_cos().size() == 15);
	ctr.undo();
	rep.goleste_fisier();
}

void testSortare(){
     std::string file_name = "in.txt";
	 
	RepoPFile rep{ "C:\\Users\\BOZGA\\source\\repos\\Lab_4_7_OOP - Copy\\Lab_4_7_OOP\\in.txt" };

	ProdusValidator val;
	Cos cos{ val };
	ServiceP ctr{ rep,val ,cos};
	ctr.adauga_service("z", "a", "c", 6);
	ctr.adauga_service("a", "a", "c", 60);
	ctr.adauga_service("a", "d", "c", 600);

	auto firstP = ctr.sorteaza_dupa_nume()[2];
	assert(firstP.get_nume() == "z");

	firstP = ctr.sorteaza_dupa_pret()[0];
	assert(firstP.get_pret() == 6);

	firstP = ctr.sorteaza_dupa_nume_si_tip()[0];
	assert(firstP.get_pret() == 60);
	assert(firstP.get_nume() == "a");
	assert(firstP.get_tip() == "a");
	rep.goleste_fisier();

}
void teste_service() {
	
	
	testSortare();
	testFiltrare();
	
	teste_adauga();
}