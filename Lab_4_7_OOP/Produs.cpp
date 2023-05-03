#include "Produs.h"

bool Cmp_nume(const Produs& p1, const Produs& p2) {
	return p1.get_nume() < p2.get_nume();
}
bool Cmp_pret(const Produs& p1, const Produs& p2) noexcept{
	return p1.get_pret() < p2.get_pret();
}
bool Cmp_tip(const Produs& p1, const Produs& p2) {
	return p1.get_tip() < p2.get_tip();
}