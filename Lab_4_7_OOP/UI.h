#pragma once
#include "Produs.h"
#include "Service_magazin.h"

class UI {
	ServiceP& service;
	void adauga_ui();
	void modifica_ui();
	void sterge_ui();
	void cauta_ui();
	void sortare_ui();
	void filtru();
	void tipareste(const vector<Produs>& produse);
	void adauga_cos();
	void vizulizare_cos();
	void sterge_cos_ui();
	void cantitati_cos();
	void undo_ui();
public:
	UI(ServiceP&  service) noexcept: service{service}{}
	UI(const UI& alt) = delete;
	void start();
	void adauga_produse_cos_random();
};