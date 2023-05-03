#pragma once
#include"Produs.h"
#include"RepoPFile.h"

class Actiune_undo {
public:
	virtual void do_undo() = 0;
	virtual ~Actiune_undo() = default;
};
class undo_adauga : public Actiune_undo {
	Produs p_adaugat;
	RepoPFile& repo;
public:
	undo_adauga(Produs p_adaugat, RepoPFile& repo) :repo{ repo }, p_adaugat{ p_adaugat } {}
	void do_undo() override {
		repo.sterge_repo(p_adaugat.get_nume(),p_adaugat.get_tip());
	}
};
class undo_sterge : public Actiune_undo {
	Produs p_adaugat;
	RepoPFile& repo;
public:
	undo_sterge(Produs p_adaugat, RepoPFile& repo) :repo{ repo }, p_adaugat{ p_adaugat } {}
	void do_undo() override {

		repo.adauga_repo(p_adaugat);
		
		
	}
};
class undo_mod : public Actiune_undo {
	Produs p_adaugat;
	RepoPFile& repo;
public:
	undo_mod(Produs p_adaugat, RepoPFile& repo) :repo{ repo }, p_adaugat{ p_adaugat } {}
	void do_undo() override {
		repo.modifica_repo(p_adaugat);
	}
};
