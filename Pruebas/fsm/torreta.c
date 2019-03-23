
#include "torreta.h"

//Frecuencia PWM = SYSCLK/(DIVISOR*RANGO)
#define SYSCLK 19200	//19.2MHz = 19200kHz
#define DIVISOR 192 	//100kHz
#define RANGO	2000		// 0 = OFF, T=2000=100%
#define T 20					// T=20ms -> f=50Hz

//Pin GPIO salida PWM
#define GPIO19 19

//SERVOMOTOR
#define INC 10			//Incremento cada vez que se pulsa una tecla
#define P_MAX 200	//Pulso maximo 2ms -> p_max=RANGO*2/T=200 -> Torreta en 180º
#define P_MIN 120	//Sin pulso, PWM off -> Torreta en 0º   CUIDADO QUE TOQUE!!!!!!! ERA 100 !!!!!!!!!!!!!!!!!!!!!

//------------------------------------------------------
// PROCEDIMIENTOS DE INICIALIZACION DE LOS OBJETOS ESPECIFICOS
//------------------------------------------------------

void InicializaTorreta (TipoTorreta *p_torreta) {
	// A completar por el alumno...
	// ...
	
	/*
		Establece la posicion inicial de la torreta
	*/
	
	int pulso = (P_MAX-P_MIN)/2+P_MIN; // Posicion inicial 90º
	wiringPiSetupGpio();
	pinMode (GPIO19, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetRange(RANGO);
	pwmSetClock (DIVISOR);
	
	p_torreta->posicion.x = pulso;
	p_torreta->posicion.y = 0;
	p_torreta->servo_x.inicio = 0;
	p_torreta->servo_x.incremento = 10;
	p_torreta->servo_x.minimo = P_MIN;
	p_torreta->servo_x.maximo = P_MAX;
	
	pwmWrite(GPIO19, p_torreta->posicion.x);
	
}

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------

int CompruebaComienzo (fsm_t* this) {
	int result = 0;
	int ope=0;
	// A completar por el alumno
	// ...
	printf( "entra a compruebo. Flag: %x \n",flags_juego );
	ope = (flags_juego & FLAG_SYSTEM_START);
	printf( "Ope. %x \n",ope );
	if (ope==FLAG_SYSTEM_START){
		printf ("Recibida senal START");
		result = 1;
	}
	printf( "salgo de compruebo. Flag: %x \n",flags_juego );
	return result;
}

int CompruebaJoystickUp (fsm_t* this) {
	int result = 0;
	
	/*TipoTorreta* p = (TipoTorreta*)(this->user_data);

    p-> */
	
	// A completar por el alumno
	// ...
	printf( "entra a muevo UP. Flags %x: \n", flags_juego); 
	if ((flags_juego & FLAG_JOYSTICK_UP)==FLAG_JOYSTICK_UP){
		fprintf (stdout, "Joystick -> UP");
		result = 1;
	}

	return result;
}

int CompruebaFinalJuego (fsm_t* this) {
	int result = 0;

	// A completar por el alumno
	// ...
	
	if (flags_juego & FLAG_SYSTEM_END){
		fprintf (stdout, "Recibida senal END");
		flags_juego &= ~FLAG_SYSTEM_END;
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
	
	TipoTorreta* torreta = (TipoTorreta*)(this->user_data);
	
	fprintf (stdout, "Iniciando Torreta...");
	InicializaTorreta(torreta);
	fprintf (stdout, "Torreta operativa");

	flags_juego &= ~FLAG_SYSTEM_START; //Limpiamos flag
	
}

void MueveTorretaArriba (fsm_t* this) {
	// A completar por el alumno
	// ...
	
	TipoTorreta* torreta = (TipoTorreta*)(this->user_data);
	
	fprintf (stdout, "Accion -> Torreta UP");
	torreta->posicion.x += torreta->servo_x.incremento;
	pwmWrite(GPIO19, torreta->posicion.x);
	
	flags_juego &= ~FLAG_JOYSTICK_UP;
	
}

void FinalizaJuego (fsm_t* this) {
	// A completar por el alumno
	// ...
	
	fprintf (stdout, "Desactivando Torreta...");
	//Aqui podriamos hacer que la torreta mire al suelo
	fprintf (stdout, "Torreta OFF");

	flags_juego &= ~FLAG_SYSTEM_END;
}

//------------------------------------------------------
// PROCEDIMIENTOS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------

void timer_duracion_disparo_isr (union sigval value) {
	// A completar por el alumno
	// ...
}
