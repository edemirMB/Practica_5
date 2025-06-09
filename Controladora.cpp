#include "Controladora.h"
#include "Jugador.h"

CControladora::CControladora() {
	cancha = new CCancha();
	jugador = new CJugador(ANCHOIMAGEN, ALTOIMAGEN);
	bombas = new CColeccionBomba();
	habilidades = new CColeccionHabilidad();
	enemigos = new CColeccionEnemigo();
	nivel = 3;
    juegoTerminado = false;
}

int CControladora::getNivel() {
	return nivel;
}

void CControladora::inicializar() {
	cancha->Inicializar();
}

void CControladora::Dibujar() {
	cancha->Inicializar();
};
void CControladora::reiniciarJuego() {
    // Reiniciar el jugador
    delete jugador;
    jugador = new CJugador(ANCHOIMAGEN, ALTOIMAGEN);

    // Reiniciar la cancha
    delete cancha;
    cancha = new CCancha();
    cancha->Inicializar();

    // Limpiar bombas
    delete bombas;
    bombas = new CColeccionBomba();

    // Reiniciar habilidades
    delete habilidades;
    habilidades = new CColeccionHabilidad();
    crearHabilidades();

    // Reiniciar enemigos
    delete enemigos;
    enemigos = new CColeccionEnemigo();
    crearEnemigos();

    juegoTerminado = false;
}

void CControladora::verificarColisionExplosion() {
    // Obtener la posición del jugador
    int jugadorX = jugador->getX();
    int jugadorY = jugador->getY();

    // Crear el rectángulo de colisión del jugador
    Rectangle jugadorRect = Rectangle(jugadorX, jugadorY,
        ANCHOJUGADOR * FACTORZOOM,
        ALTOJUGADOR * FACTORZOOM);

    // Iterar sobre todas las bombas para verificar explosiones
    for (CBomba* bomba : bombas->getBombas()) {
        if (bomba->getEstado() == EBomba::explosion) {
            // Obtener las coordenadas de la bomba
            int bombaX = bomba->getX();
            int bombaY = bomba->getY();
            int cellX = bomba->getCellX();
            int cellY = bomba->getCellY();

            const int newAnchoImagen = ANCHOIMAGEN - 10;
            const int newAltoImagen = ALTOIMAGEN - 10;

            // Verificar colisión con el centro de la explosión
            Rectangle centroExplosion = Rectangle(bombaX, bombaY, newAnchoImagen, newAltoImagen);
            if (jugadorRect.IntersectsWith(centroExplosion)) {
                jugador->disminuirVida();
                return; // Solo quitar una vida por explosión
            }

            // Verificar colisión con explosión hacia la izquierda
            if (cellX > 0 && cancha->getCancha()[cellY][cellX - 1]->getTipo() != EElementos::paredes) {
                Rectangle izquierda = Rectangle(bombaX - newAnchoImagen, bombaY, newAnchoImagen, newAltoImagen);
                if (jugadorRect.IntersectsWith(izquierda)) {
                    jugador->disminuirVida();
                    return;
                }
            }

            // Verificar colisión con explosión hacia la derecha
            if (cellX < COLUMNAS - 1 && cancha->getCancha()[cellY][cellX + 1]->getTipo() != EElementos::paredes) {
                Rectangle derecha = Rectangle(bombaX + newAnchoImagen, bombaY, newAnchoImagen, newAltoImagen);
                if (jugadorRect.IntersectsWith(derecha)) {
                    jugador->disminuirVida();
                    return;
                }
            }

            // Verificar colisión con explosión hacia arriba
            if (cellY > 0 && cancha->getCancha()[cellY - 1][cellX]->getTipo() != EElementos::paredes) {
                Rectangle arriba = Rectangle(bombaX, bombaY - newAltoImagen, newAnchoImagen, newAltoImagen);
                if (jugadorRect.IntersectsWith(arriba)) {
                    jugador->disminuirVida();
                    return;
                }
            }

            // Verificar colisión con explosión hacia abajo
            if (cellY < FILAS - 1 && cancha->getCancha()[cellY + 1][cellX]->getTipo() != EElementos::paredes) {
                Rectangle abajo = Rectangle(bombaX, bombaY + newAltoImagen, newAnchoImagen, newAltoImagen);
                if (jugadorRect.IntersectsWith(abajo)) {
                    jugador->disminuirVida();
                    return;
                }
            }
        }
    }
}


void CControladora::dibujarCancha(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpIrrompible, Bitmap^ bmpRrompible, Bitmap^ bmpHabilidad) {
    habilidades->dibujar(g, bmpHabilidad, cancha->getCancha());
    cancha->PintarCancha(g, bmpPiso);
	cancha->PintarMatriz(g, bmpIrrompible, bmpRrompible);
	
};

void CControladora::dibujarJugador(Graphics^ g, Bitmap^ bmpJugador) {
	jugador->dibujar(g, bmpJugador, cancha->getCancha());
}
void CControladora::dibujarVidas(Graphics^ g, Bitmap^ bmpVida) {
    jugador->dibujarVidas(g, bmpVida);
}
void CControladora::adicionarBomba() {
	bombas->crearBomba(jugador->getX(), jugador->getY());
}

void CControladora::moverJugador(Graphics^ g, Bitmap^ bmpJugador, Bitmap^ bmpBomba, Bitmap^ bmpExplosion, Bitmap^ bmpEnemigo, Bitmap^ bmpVida) {
    if (!juegoTerminado) {
        bombas->dibujarBomba(g, bmpBomba, bmpExplosion, jugador->getX(), jugador->getY(), cancha->getCancha());
        jugador->actualizarInvulnerabilidad();

        // Verificar colisiones
        verificarColisionExplosion();

        // Verificar si el jugador perdió todas las vidas
        if (!jugador->estaVivo()) {
            juegoTerminado = true;
            // Reiniciar el juego después de un breve delay
            reiniciarJuego();
        }

        jugador->mover(g, bmpJugador, cancha->getCancha());
        enemigos->dibujar(g, bmpEnemigo, cancha->getCancha());
    }
    dibujarVidas(g, bmpVida);
}
CJugador* CControladora::getJugador() {
	return jugador;
}

void CControladora::crearHabilidades() {
	while (habilidades->getHabilidades().size() < nivel) {
	  habilidades->crearHabilidad();
	}
}

void CControladora::crearEnemigos() {
	//enemigos->buscarEspacioLibre(cancha->getCancha());
	while (enemigos->getEnemigos().size() < nivel) {
		enemigos->crearEnemigo();
	}
}

CColeccionHabilidad* CControladora::getColeccionHabilidades() {
	return habilidades;
}

CColeccionEnemigo* CControladora::getColeccionEnemigos() {
	return enemigos;
}
