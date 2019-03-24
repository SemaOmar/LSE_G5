
#include "piTankGo_1.h"

int flags_juego = 0;
int flags_player = 0;
int flags_system = 0;

//------------------------------------------------------
// FUNCIONES DE CONFIGURACION/INICIALIZACION
//------------------------------------------------------

// int ConfiguracionSistema (TipoSistema *p_sistema): procedimiento de configuracion del sistema.
// Realizará, entra otras, todas las operaciones necesarias para:
// configurar el uso de posibles librerías (e.g. Wiring Pi),
// configurar las interrupciones externas asociadas a los pines GPIO,
// configurar las interrupciones periódicas y sus correspondientes temporizadores,
// crear, si fuese necesario, los threads adicionales que pueda requerir el sistema
int ConfiguraSistema (TipoSistema *p_sistema) {
	int result = 0;
	// A completar por el alumno...
	// ...

	return result;
}

// int InicializaSistema (TipoSistema *p_sistema): procedimiento de inicializacion del sistema.
// Realizará, entra otras, todas las operaciones necesarias para:
// la inicializacion de los diferentes elementos de los que consta nuestro sistema,
// la torreta, los efectos, etc.
// igualmente arrancará el thread de exploración del teclado del PC
int InicializaSistema (TipoSistema *p_sistema) {
	int result = 0;

	// A completar por el alumno...
	// ...

	// Lanzamos thread para exploracion del teclado convencional del PC
	result = piThreadCreate (thread_explora_teclado_PC);

	if (result != 0) {
		printf ("Thread didn't start!!!\n");
		return -1;
	}

	return result;
}

//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

PI_THREAD (thread_explora_teclado_PC) {
	int teclaPulsada;

	while(1) {
		delay(10); // Wiring Pi function: pauses program execution for at least 10 ms

		piLock (STD_IO_BUFFER_KEY);

		if(kbhit()) {
			teclaPulsada = kbread();

			switch(teclaPulsada) {
				// A completar por el alumno...
				// ...
				case 's':
					// A completar por el alumno...
					// ...
					
					/*
						DUDA JOSE -> No se muy bien como funcionan las interrupciones, supongo que este hilo se encarga 
						de monitorizar el teclado y activa un flag si detecata que se ha pulsado una tecla

						Por ahora dos interrupciones:
							Tecla S -> start -> inicia las maquinas de estado
							Tecla Q -> quit  -> Finaliza mauqinas de estado, termina el programa
					*/
					printf("Tecla S pulsada!\n");
					flags_system = FLAG_SYSTEM_START; //Borramos los flags que puedieran estar activos antes de iniciar el sistema
					flags_juego |= FLAG_SYSTEM_START;
					printf("Flag juego %x\n", flags_juego);			

					fflush(stdout);
					break;
					
					
				case 'w': // simular Joystick con teclado hasta tener hecha esa parte para comprobar el funcionamiento de la FSM
					printf("Tecla UP pulsada!\n");
					flags_juego |= FLAG_JOYSTICK_UP;
					printf("Flag juego %x\n", flags_juego);
					fflush(stdout);
					break;

				case 'q':
					flags_system |= FLAG_SYSTEM_END;
					flags_juego |= FLAG_SYSTEM_END;
					exit(0);
					break;

				default:
					printf("INVALID KEY!!!\n");
					break;
			}
		}

		piUnlock (STD_IO_BUFFER_KEY);
	}
}


// wait until next_activation (absolute time)
void delay_until (unsigned int next) {
	unsigned int now = millis();
	if (next > now) {
		delay (next - now);
	}
}

int main ()
{
	TipoSistema sistema;
	unsigned int next;

	// Configuracion e inicializacion del sistema
	ConfiguraSistema (&sistema);

	InicializaSistema (&sistema);

	// A completar por el alumno...
	// ...
	
	fsm_trans_t torreta[] = {
		{ WAIT_START, CompruebaComienzo, WAIT_MOVE, ComienzaSistema },
		{ WAIT_MOVE, CompruebaJoystickUp, JOYSTICK_UP, MueveTorretaArriba },
		/*{ WAIT_MOVE, CompruebaJoystickRight, JOYSTICK_RIGHT, MueveTorretaDerecha }, // estados aun no implementados
		{ WAIT_MOVE, CompruebaJoystickDown, JOYSTICK_DOWN, MueveTorretaAbajo },
		{ WAIT_MOVE, CompruebaJoystickLeft, JOYSTICK_LEFT, MueveTorretaIzquierda },
		{ WAIT_MOVE, CompruebaTriggerButton, TRIGGER_BUTTON, DisparoIR },*/
		{ WAIT_MOVE, CompruebaFinalJuego, WAIT_END, FinalizaJuego },
		{ JOYSTICK_UP, NoComprueboNada, WAIT_MOVE, NoHagoNada },
		/*{ JOYSTICK_RIGHT, 1, WAIT_MOVE, NULL },
		{ JOYSTICK_DOWN, 1, WAIT_MOVE, NULL },
		{ JOYSTICK_LEFT, 1, WAIT_MOVE, NULL },
		{ TRIGGER_BUTTON, CompruebaImpacto, WAIT_MOVE, ImpactoDetectado },
		{ TRIGGER_BUTTON, CompruebaTimeOutDisparo, WAIT_MOVE, FinalDisparoIR },*/
		{-1, NULL, -1, NULL },
	};
	
	fsm_t* torreta_fsm = fsm_new (WAIT_START, torreta, &(sistema.torreta));

	next = millis();
	while (1) {
		//fsm_fire (player_fsm);
		// A completar por el alumno...
		// ...
		
		fsm_fire (torreta_fsm);

		next += CLK_MS;
		delay_until (next);
	}

	return 0;
}
