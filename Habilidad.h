#pragma once
#include "Items.h"
#include "Cancha.h"
using namespace System::Drawing;

class CHabilidad {
	int i;
	int j;

	int indiceX;
	int indiceY;
	
	int tipoHabilidad;
	bool ubicado;

public:
	CHabilidad();
	~CHabilidad();

	void dibujar(Graphics^ g, Bitmap^ bmpHabilidad, const CanchaArray& cancha);
	void animar();
	/*void accionhabilidades(CJugador* jugador, std::vector<CBomba*>& bombas, int totalBombas, int& rangoExplosion);*/
	int getHabilidad();
};
