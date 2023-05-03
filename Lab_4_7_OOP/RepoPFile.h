#include<string>
#ifndef RepoPFile_h
#define RepoPFile_h
#include"Repo_produse.h"
class RepoPFile : public RepoP {
private:
	std::string fName;
	//incarca datele din fisier
	void loadFromFile();
	//transfera datele in fisier
	void writeToFile();
public:
	RepoPFile(std::string fName) :RepoP(), fName{ fName } {
		loadFromFile();//incarcam datele din fisier
	}

	void adauga_repo(const Produs& p) override {
		RepoP::adauga_repo(p);//apelam metoda din clasa de baza
		writeToFile();
	}
	void sterge_repo(const string& nume, const string& tip) override {
		RepoP::sterge_repo(nume,tip);//apelam metoda din clasa de baza
		writeToFile();
	}
	void modifica_repo(const Produs& p_nou) override {
		
		RepoP::modifica_repo(p_nou);
		writeToFile();
	}
	//sterge continutul fisierului cu numele fNume
	void goleste_fisier();
	
};
#endif