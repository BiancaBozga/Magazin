
#include"RepoPFile.h"
#include <fstream>
void RepoPFile::loadFromFile() {
	
	std::ifstream in(fName);
	if (!in.is_open()) {
		//verify if the stream is opened
		throw RepoP_exceptie("Error open:" + fName);
	}
	while (!in.eof()) {
		std::string nume;
		in >> nume;
		//poate am linii goale
		if (in.eof()) break;
		std::string tip;
		in >> tip;
		std::string producator;
		in >> producator;
		float price;
		in >> price;
		Produs p{ nume.c_str(),tip.c_str(),producator.c_str(), price };
		RepoP::adauga_repo(p);
	}
	in.close();
}
void RepoPFile::writeToFile() {
	std::ofstream out(fName);
	if (!out.is_open()) {
		
			//verify if the stream is opened
			std::string msg("Error open file");
		throw RepoP_exceptie(msg);
	}
	for (auto& p : get_all()) {
		if (p.get_sters() != 1) {
			out << p.get_nume();
			out << std::endl;
			out << p.get_tip();
			out << std::endl;
			out << p.get_producator();
			out << std::endl;
			out << p.get_pret();
			out << std::endl;
		}
	}
	out.close();
}
void RepoPFile::goleste_fisier() {
	std::ofstream out;
	out.open(fName, std::ofstream::out | std::ofstream::trunc);
	
	out.close();
}

