
#include "torreta.h"

#define SYSCLK 19200	//19.2MHz = 19200kHz
#define DIVISOR 192 	//100kHz
#define RANGO	2000	// 0 = OFF, T=2000=100%
#define T 20		// T=20ms -> f=50Hz

//Pin GPIO salida PWM
#define GPIO18 18	//eje y
#define GPIO19 19	//eje x

//SERVOMOTOR
#define INC 10		//Incremento cada vez que se pulsa una tecla
#define P_MAX 200	//Pulso maximo 2ms -> p_max=RANGO*2/T=200 -> Torreta en 180º -> Podemos usar 100 intervalos del total de RANGO
#define P_MIN 100	//Sin pulso, PWM off -> Torreta en 0º

//------------------------------------------------------
// PROCEDIMIENTOS DE INICIALIZACION DE LOS OBJETOS ESPECIFICOS
//------------------------------------------------------

void InicializaTorreta (TipoTorreta *p_torreta) {
	// A completar por el alumno...
	int pos_ini = ((P_MAX-P_MIN)/2)+P_MIN; // Posicion inicial en el punto medio -> 90º

	pinMode(GPIO19, PWM_OUTPUT);
	pinMode(GPIO18, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetRange(RANGO);
	pwmSetClock (DIVISOR);
	/*
			Establece la posicion inicial de la torreta
		*/
	p_torreta->posicion.x = pos_ini;
	p_torreta->servo_x.inicio = pos_ini;
	p_torreta->servo_x.incremento = INC;
	p_torreta->servo_x.minimo = P_MIN;
	p_torreta->servo_x.maximo = P_MAX;
	
	p_torreta->posicion.y = pos_ini;
	p_torreta->servo_y.inicio = pos_ini;
	p_torreta->servo_y.incremento = INC;
	p_torreta->servo_y.minimo = P_MIN;
	p_torreta->servo_y.maximo = P_MAX;

	pwmWrite(GPIO19, p_torreta->posicion.x);
	pwmWrite(GPIO18, p_torreta->posicion.y);
	
	
	
}

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaComienzo (fsm_t* this) {
	int result = 0;

	fprintf (stdout,"ESTADO --> START\n");
	
	if (flags_juego & FLAG_SYSTEM_START){
		printf ("Recibida senal START\n");
		result = 1;
	}
	
	return result;
}

int CompruebaJoystickUp (fsm_t* this) {
	int result = 0;
	
	fprintf (stdout,"ESTADO --> WAIT\n");
	
	if (flags_juego & FLAG_JOYSTICK_UP){
		fprintf (stdout, "Joystick -> UP\n");
		result = 1;
	}

	return result;
}

int CompruebaFinalJuego (fsm_t* this) {
	int result = 0;

	if (flags_juego & FLAG_SYSTEM_END){
		fprintf (stdout, "Recibida senal END\n");
		result = 1;
	}

	return result;
}

int NoComprueboNada (fsm_t* this) {
	fprintf (stdout, "\t\tNo compruebo nada\n");
	return 1;
}

//------------------------------------------------------
// FUNCIONES DE SALIDA O DE ACCION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

void ComienzaSistema (fsm_t* this) {
	// A completar por el alumno
	// ...
	
	TipoTorreta* torreta = (TipoTorreta*)(this->user_data);
	
	fprintf (stdout, "Iniciando Torreta...\n");
	flags_juego &= ~FLAG_SYSTEM_START; //Limpiamos flag
	fprintf (stdout, "Torreta operativa\n");
}

void MueveTorretaArriba (fsm_t* this) {
	// A completar por el alumno
	// ...
	
	int y_next = 0;
	TipoTorreta* torreta = (TipoTorreta*)(this->user_data);
	
	fprintf (stdout, "\t\tWAIT --> UP\n");
	fprintf (stdout, "Accion -> Torreta UP\n");
	
	y_next = torreta->posicion.y + torreta->servo_y.incremento;
	if (y_next <= torreta->servo_y.maximo) {
		torreta->posicion.y = y_next;
		pwmWrite(GPIO19, torreta->posicion.y);
	}
	else if(torreta->posicion.y < torreta->servo_y.maximo){
		torreta->posicion.y = torreta->servo_y.maximo;
		pwmWrite(GPIO19, torreta->posicion.y);
	}
	
	flags_juego &= ~FLAG_JOYSTICK_UP;
}

void MueveTorretaAbajo (fsm_t* this) {
	// A completar por el alumno
	// ...
	
	int y_next = 0;
	TipoTorreta* torreta = (TipoTorreta*)(this->user_data);
	
	fprintf (stdout, "\t\tWAIT --> DOWN\n");
	fprintf (stdout, "Accion -> Torreta DOWN\n");
	
	y_next = torreta->posicion.y - torreta->servo_y.incremento;
	if (y_next >= torreta->servo_y.minimo) {
		torreta->posicion.y = y_next;
		pwmWrite(GPIO19, torreta->posicion.y);
	}
	else if(torreta->posicion.y > torreta->servo_y.minimo){
		torreta->posicion.y = torreta->servo_y.minimo;
		pwmWrite(GPIO19, torreta->posicion.y);
	}
	
	flags_juego &= ~FLAG_JOYSTICK_DOWN;
	
}

void MueveTorretaIzquierda (fsm_t* this) {
	// A completar por el alumno
	// ...
	
	int x_next=0;
	TipoTorreta* torreta = (TipoTorreta*)(this->user_data);
	
	fprintf (stdout, "\t\tWAIT --> UP\n");
	fprintf (stdout, "Accion -> Torreta UP\n");
	
	x_next = torreta->posicion.x + torreta->servo_x.incremento;
	if (x_next <= torreta->servo_x.maximo) {
		torreta->posicion.x = x_next;
		pwmWrite(GPIO19, torreta->posicion.x);
	}
	else if(torreta->posicion.x > torreta->servo_x.maximo){
		torreta->posicion.x = torreta->servo_x.maximo;
		pwmWrite(GPIO19, torreta->posicion.x);
	}
	
	flags_juego &= ~FLAG_JOYSTICK_LEFT;
	
}

void MueveTorretaDerecha (fsm_t* this) {
	// A completar por el alumno
	// ...
	
	int x_next=0;
	TipoTorreta* torreta = (TipoTorreta*)(this->user_data);
	
	fprintf (stdout, "\t\tWAIT --> UP\n");
	fprintf (stdout, "Accion -> Torreta UP\n");
	
	x_next = torreta->posicion.x - torreta->servo_x.incremento;
	if (x_next >= torreta->servo_x.minimo) {
		torreta->posicion.x = x_next;
		pwmWrite(GPIO19, torreta->posicion.x);
	}
	else if(torreta->posicion.x < torreta->servo_x.minimo){
		torreta->posicion.x = torreta->servo_x.minimo;
		pwmWrite(GPIO19, torreta->posicion.x);
	}
	
	flags_juego &= ~FLAG_JOYSTICK_RIGHT;
	
}

void DisparoIR (fsm_t* this) {
	// A completar por el alumno
	// ...
}

void FinalDisparoIR (fsm_t* this) {
	// A completar por el alumno
	// ...
}

void ImpactoDetectado (fsm_t* this) {
	// A completar por el alumno
	// ...
}

void FinalizaJuego (fsm_t* this) {
	// A completar por el alumno
	// ...
}

void NoHagoNada(fsm_t* this) {
	fprintf (stdout, "No hago nada\n");
}

//------------------------------------------------------
// PROCEDIMIENTOS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void timer_duracion_disparo_isr (union sigval value) {
	// A completar por el alumno
	// ...
}
