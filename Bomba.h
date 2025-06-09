#pragma once
#include "Items.h"
#include "Cancha.h"
#include <vector>
#include <utility>

#define ANCHOBOMBA 24
#define ALTOBOMBA 24
#define ANCHOEXPLOSION 20
#define ALTOEXPLOSION 20
#define TIEMPOEXPLOSION 9

using namespace System::Drawing;
using namespace std;
enum EBomba {
	puesto,
	explosion,
	explotado
};

class CBomba {
	int x;
	int y;
	int indiceX;
	int tiempoExplosion;
	int cellX, cellY;
	EBomba estado;

	// explosion
	int indiceEX;
	int indiceEY;
	vector<pair<int, int>> bloquesDestruidos;
public:
	CBomba(int x, int y);

	EBomba getEstado();
	int getX() { return x; }
	int getY() { return y; }
	int getCellX() { return cellX; }
	int getCellY() { return cellY; }
	void animarExplosion();
	bool verificarLugar(int i, int j, const CanchaArray& cancha);
	void dibujar(Graphics^ g, Bitmap^ bmpBomba, int jugadorX, int jugadorY, const CanchaArray& cancha);		
	void animar();
	void dibujarExplosion(Graphics^ g, Bitmap^ bmpExplosion, const CanchaArray& cancha);

};