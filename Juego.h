#pragma once
#include "Controladora.h";

namespace Bomberman {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Juego
	/// </summary>
	public ref class Juego : public System::Windows::Forms::Form
	{
	public:
		CControladora* controladora = new CControladora();
		Bitmap^ bmpPiso = gcnew Bitmap("Imagenes\\piso1.png");
		Bitmap^ bmpIrrompible = gcnew Bitmap("Imagenes\\irrompible1.png");
		Bitmap^ bmpRrompible = gcnew Bitmap("Imagenes\\rrompible1.png");
		Bitmap^ bmpJugador = gcnew Bitmap("Imagenes\\protagonista1.png");
		Bitmap^ bmpBomba = gcnew Bitmap("Imagenes\\bomba.png");
		Bitmap^ bmpExplosion = gcnew Bitmap("Imagenes\\explosion.png");
		Bitmap^ bmpHabilidad = gcnew Bitmap("Imagenes\\habilidades.png");
		Bitmap^ bmpEnemigo = gcnew Bitmap("Imagenes\\enemigos.png");
		Bitmap^ bmpVida = gcnew Bitmap("Imagenes\\heart.png");
		
		Juego(void)
		{
			bmpJugador->MakeTransparent(bmpJugador->GetPixel(0, 0));
			bmpBomba->MakeTransparent(bmpBomba->GetPixel(0, 0));
			bmpVida->MakeTransparent(bmpVida->GetPixel(0, 0));
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Juego()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>

	private: System::Windows::Forms::Label^ lblNivel;
	private: System::Windows::Forms::ProgressBar^ Carga;
	private: System::Windows::Forms::Timer^ tcarga;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->lblNivel = (gcnew System::Windows::Forms::Label());
			this->Carga = (gcnew System::Windows::Forms::ProgressBar());
			this->tcarga = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Juego::timer1_Tick);
			// 
			// lblNivel
			// 
			this->lblNivel->AutoSize = true;
			this->lblNivel->Font = (gcnew System::Drawing::Font(L"Wide Latin", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblNivel->ForeColor = System::Drawing::Color::White;
			this->lblNivel->Location = System::Drawing::Point(212, 237);
			this->lblNivel->Name = L"lblNivel";
			this->lblNivel->Size = System::Drawing::Size(163, 34);
			this->lblNivel->TabIndex = 0;
			this->lblNivel->Text = L"Nivel :";
			this->lblNivel->Click += gcnew System::EventHandler(this, &Juego::lblNivel_Click);
			// 
			// Carga
			// 
			this->Carga->Location = System::Drawing::Point(218, 283);
			this->Carga->Name = L"Carga";
			this->Carga->Size = System::Drawing::Size(186, 32);
			this->Carga->TabIndex = 1;
			// 
			// tcarga
			// 
			this->tcarga->Enabled = true;
			this->tcarga->Interval = 1500;
			this->tcarga->Tick += gcnew System::EventHandler(this, &Juego::tcarga_Tick);
			// 
			// Juego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->ClientSize = System::Drawing::Size(448, 394);
			this->Controls->Add(this->Carga);
			this->Controls->Add(this->lblNivel);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"Juego";
			this->Text = L"Juego";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &Juego::FormLoad);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::TeclaKeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Juego::TeclaKeyUp);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);
		controladora->dibujarCancha(buffer->Graphics, bmpPiso, bmpIrrompible, bmpRrompible, bmpHabilidad);
		controladora->moverJugador(buffer->Graphics, bmpJugador, bmpBomba, bmpExplosion, bmpEnemigo, bmpVida);
		
		buffer->Render(g);

		delete buffer, espacio, g;
	}
	private: System::Void FormLoad(System::Object^ sender, System::EventArgs^ e) {
		controladora->Dibujar();
		controladora->crearHabilidades();
		controladora->crearEnemigos();
	}

	private: System::Void TeclaKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::Up:
			controladora->getJugador()->setDireccion(EDireccion::Arriba);
			break;
		case Keys::Down:
			controladora->getJugador()->setDireccion(EDireccion::Abajo);
			break;
		case Keys::Left:
			controladora->getJugador()->setDireccion(EDireccion::Izquierda);
			break;
		case Keys::Right:
			controladora->getJugador()->setDireccion(EDireccion::Derecha);
			break;
		}
	}
	private: System::Void TeclaKeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::Space:
			controladora->adicionarBomba();
			break;
		default:
			controladora->getJugador()->setDireccion(EDireccion::Ninguna);
			break;
		}
	}
private: System::Void tcarga_Tick(System::Object^ sender, System::EventArgs^ e) {
	lblNivel->Text = "Nivel : " + controladora->getNivel();
	Carga->Increment(10);
	if (controladora->getColeccionHabilidades()->getHabilidades().size() < controladora->getNivel()) {
		controladora->crearHabilidades();
	}
	if (Carga->Value >= 100) {
		tcarga->Enabled = false;
		timer1->Enabled = true;
		lblNivel->Visible = false;
		lblNivel->Enabled = false;
		Carga->Visible = false;
		Carga->Enabled = false;
	}
}
private: System::Void lblNivel_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
