
#include "torreta.h"

//------------------------------------------------------
// PROCEDIMIENTOS DE INICIALIZACION DE LOS OBJETOS ESPECIFICOS
//------------------------------------------------------

void InicializaTorreta (TipoTorreta *p_torreta) {
	// A completar por el alumno...
	int pos_ini = ((P_MAX-P_MIN)/2)+P_MIN; // Posicion inicial en el punto medio -> 90º

	pinMode (GPIO19, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetRange(RANGO);
	pwmSetClock (DIVISOR);
	/*
			Establece la posicion inicial de la torreta
		*/
	p_torreta->posicion.x = pos_ini;
	p_torreta->posicion.y = pos_ini;
	p_torreta->servo_x.inicio = 0;
	p_torreta->servo_x.incremento = 10;
	p_torreta->servo_x.minimo = P_MIN;
	p_torreta->servo_x.maximo = P_MAX;

	pwmWrite(GPIO19, p_torreta->posicion.x);
	// ...
	
	
	
}

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaComienzo (fsm_t* this) {
	int result = 0;
	// A completar por el alumno
	// ...
	
	/*
		Si se aprieta cualquir boton, que empice a funcionar la torreta
	*/
	if (flags_system == FLAG_SYSTEM_START){
		printf (stdout, "Recibida senal START"); 
		flags_system &= ~FLAG_SYSTEM_START //Limpiamos flag
		result = 1;
	}

	return result;
}

int CompruebaJoystickUp (fsm_t* this) {
	int result = 0;

	// A completar por el alumno
	// ...
	
	if (flags_juego == FLAG_JOYSTICK_UP){
		printf (stdout, "Joystick -> UP");
		result = 1;
	}

	return result;
}

int CompruebaJoystickDown (fsm_t* fsm_player){
	int result = 0;

	// A completar por el alumno
	// ...
	
	if (flags_juego == FLAG_JOYSTICK_DOWN){
		printf (stdout, "Joystick -> Down");
		result = 1;
	}

	return result;
}

int CompruebaJoystickLeft (fsm_t* this) {
	int result = 0;

	// A completar por el alumno
	// ...
	
	if (flags_juego == FLAG_JOYSTICK_LEFT){
		printf (stdout, "Joystick -> Left");
		result = 1;
	}

	return result;
}

int CompruebaJoystickRight (fsm_t* this) {
	int result = 0;

	// A completar por el alumno
	// ...
	
	if (flags_juego == FLAG_JOYSTICK_RIGHT){
		printf (stdout, "Joystick -> Right");
		result = 1;
	}

	return result;
}

int CompruebaTimeoutDisparo (fsm_t* this) {
	int result = 0;

	// A completar por el alumno
	// ...
	
	if (flags_juego == FLAG_SHOOT_TIMEOUT){
		printf (stdout, "Timeout -> Disparo");
		result = 1;
	}

	return result;
}

int CompruebaImpacto (fsm_t* this) {
	int result = 0;

	// A completar por el alumno
	// ...
	
	if (flags_juego == FLAG_TARGET_DONE){
		printf (stdout, "Impacto");
		result = 1;
	}


	return result;
}

int CompruebaTriggerButton (fsm_t* this) {
	int result = 0;

	// A completar por el alumno
	// ...
	
	if (flags_juego == FLAG_TRIGGER_BUTTON){
		printf (stdout, "Joystick -> !Fuego!");
		result = 1;
	}

	return result;
}

int CompruebaFinalJuego (fsm_t* this) {
	int result = 0;

	// A completar por el alumno
	// ...
	
	if (flags_system == FLAG_SYSTEM_END){
		printf (stdout, "Fin");
		result = 1;
	}

	return result;
}

//------------------------------------------------------
// FUNCIONES DE SALIDA O DE ACCION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

void ComienzaSistema (fsm_t* this) {
	// A completar por el alumno
	// ...
	
	InicializaTorreta(sistema.torreta);
}

void MueveTorretaArriba (fsm_t* this) {
	// A completar por el alumno
	// ...
}

void MueveTorretaAbajo (fsm_t* this) {
	// A completar por el alumno
	// ...
}

void MueveTorretaIzquierda (fsm_t* this) {
	// A completar por el alumno
	// ...
}

void MueveTorretaDerecha (fsm_t* this) {
	// A completar por el alumno
	// ...
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

//------------------------------------------------------
// PROCEDIMIENTOS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void timer_duracion_disparo_isr (union sigval value) {
	// A completar por el alumno
	// ...
}
