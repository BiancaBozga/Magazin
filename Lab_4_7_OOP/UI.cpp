#include "UI.h"
#include "Produs.h"
#include<iostream>
#include<string>
#include <iomanip>
using std::cin;
using std::cout;

void UI::tipareste(const vector<Produs>& produse) {
	cout << "Produse:\n";
	cout  << "NUME" << std::setw(12) << "TIP" << std::setw(12) << "PRODUCATOR" << std::setw(12) << "PRET" << std::setw(12) << "CANTITATE" << std::endl;
	
	for (const auto& p : produse) {
		if(p.get_sters()==0)
			cout << p.get_nume()<< std::setw(12) << p.get_tip() << std::setw(12) << p.get_producator() << std::setw(12) << p.get_pret() << std::setw(12) <<p.get_cantitate()<<'\n';

	}

}
void UI::cauta_ui() {
	string nume, tip;
	cout << "Dati nume:";
	cin >> nume;
	cout << "Dati tip:";
	cin >> tip;
	service.cauta_produs(nume, tip);
	cout << "Produs gasit in aplicatie!\n";
}
void UI::sterge_ui() {
	string nume, tip;	
	cout << "Dati nume:";
	cin >> nume;
	cout << "Dati tip:";
	cin >> tip;
	service.sterge_service(nume, tip);
	cout << "Produs sters cu succes!\n";
}
void UI::adauga_ui() {
	string nume, producator, tip;
	float pret;
	cout << "Dati nume:";
	cin >> nume;
	cout << "Dati tip:";
	cin >> tip;
	cout << "Dati producator:";
	cin >> producator;
	cout << "Dati pret:";
	cin >> pret;
	service.adauga_service(nume, tip, producator, pret);
	cout << "Produs adaugat cu succes!\n";

}
void UI::filtru() {
	string criteriu;
	cout << "Dati criteriul dupa care sa filtreze:";
	cin >> criteriu;
	if (criteriu == "pret") {
		float pret;
		cout << "Dati pret:";
		cin >> pret;
		tipareste(service.filtrare_pret(pret));
	}
	if (criteriu == "nume") {
		string nume;
		cout << "Dati nume:";
		cin >> nume;
		tipareste(service.filtrare_nume(nume));
	}
	if (criteriu == "producator") {
		string producator;
		cout << "Dati producator:";
		cin >> producator;
		tipareste(service.filtrare_producator(producator));
	}
}
void UI::sortare_ui() {
	string criteriu;
	cout << "Dati criteriu:";
	cin >> criteriu;
	if (criteriu == "nume")
		tipareste(service.sorteaza_dupa_nume());
	if (criteriu == "pret")
		
			tipareste(service.sorteaza_dupa_pret());
	if (criteriu == "nume+tip")
		tipareste(service.sorteaza_dupa_nume_si_tip());
}
void UI::modifica_ui() {
	string nume, producator, tip;
	float pret;
	cout << "Dati numele prdusului de modificat:";
	cin >> nume;
	cout << "Dati tipul produsului de modificat:";
	cin >> tip;
	cout << "Dati producatorul nou:";
	cin >> producator;
	cout << "Dati pretul nou:";
	cin >> pret;
	service.modifica_service(nume, tip, pret,producator);
	cout << "Produs modificat cu succes!\n";
}
void UI::adauga_cos() {
	string nume, tip;
	cout << "Dati numele prdusului de adaugat in cos:";
	cin >> nume;
	cout << "Dati tipul produsului de adaugat in cos:";
	cin >> tip;
	service.adauga_cos_service(nume, tip);
	cout << "Produs adaugat in cos cu succes !\n";
}
void UI::vizulizare_cos() {
	if (service.get_sters_cos() == 0) {
		tipareste(service.get_all_cos());
		cout << "TOTAL COS: " << service.get_total() << "\n";
	}
	else
		cout << "COSUL ESTE GOL!\n";
}
void UI::sterge_cos_ui() {
	service.sterge_cos();
	cout << "Cos golit cu succes!\n";
}
void UI::cantitati_cos() {
	std::map<std::string, int> dict = service.cate_produse();
	for (auto i : dict)
		cout << "Produsele cu tipul " << i.first << " au cantitatea :" << i.second<<"\n";
}
void UI::adauga_produse_cos_random() {
	int cate;
	cout << "Cate produse sa se adauge in cos?";
	cin >> cate;


	try {
		const size_t cate_adaugate= service.adauga_produse_random_service(cate);
		cout << "S-au adaugat " << cate_adaugate << " produse in cos." << std::endl;
	}
	catch (const RepoP_exceptie&  re) {
		cout << re;
	}
}
void UI::undo_ui() {
	
    service.undo();
	cout << "Undo realizat cu succes!\n";
}
void UI::start() {
	while (true) {
		cout << "Meniu:\n";
		cout << "1 adauga\n2 vizualizare produse\n3 modifica\n4 sterge\n5 cauta\n6 sortare\n7 Filtrare\n8 Adauga cos\n9 Vizualizare cos\n10 Sterge cos\n11 Cantitati cos\n12 Adauga produse random\n13 Undo\n0 Iesire\nDati comanda:";
		int cmd;
		cin >> cmd;
		try {
			switch (cmd) {
			case 1:
				adauga_ui();
				break;
			case 2:
				tipareste(service.get_all_service());
				break;
			case 3:
				modifica_ui();
				break;
			case 4:
				sterge_ui();
				break;
			case 5:
				cauta_ui();
				break;
			case 6:
				sortare_ui();
				break;
			case 7:
				filtru();
				break;
			case 8:
				adauga_cos();
				break;
			case 9:
				vizulizare_cos();
				break;
			case 10:
				sterge_cos_ui();
				break;
			case 11:
				cantitati_cos();
				break;
			case 12:
				adauga_produse_cos_random();
				break;
			case 13:
				undo_ui();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida\n";
			}
		}
		catch (const RepoP_exceptie& ex) {
			cout << ex << '\n';
		}
		catch (const ValidateException& ex) {
			cout << ex << '\n';
		}
	}
}
