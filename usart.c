#include "spi-conn.h"

void send_fitness(float fitness[], int size_population){
	int i;

	for(i = 0; i < size_population; i++){
		SPI_transfer_float(fitness[i]);
	}
}

void rcve_fitness(float fitness[], int size_population){
	int i;
	for(i = 0; i < size_population; i++){
		fitness[i] = SPI_transfer_float(0);
	}
}

void send_population(unsigned int population[][N], int size_population){

	int i,j;
	for(i = 0; i < size_population; i++){
		for(j = 0; j < N; j++){
			SPI_transfer_int(population[i][j]);
		}
	}
}

void rcve_population(unsigned int population[][N], int size_population){
	int i,j;

	for(i = 0; i < size_population; i++){
		for(j = 0; j < N; j++){
			population[i][j] = SPI_transfer_int(0);
		}
	}
}

void float_to_int(float f, uint32_t *i){
	my_union float_u;

	float_u.f = f;
	*i = float_u.i;
}

void int_to_float(uint32_t i, float *f){
	my_union int_u;

	int_u.i = i;
	*f = int_u.f;
}

uint32_t SPI_transfer_int(uint32_t send){
	uint32_t rcve = 0;
	unsigned char tmp = 0;
	// envia dado byte por byte
	int i;
	for(i = 0; i < 4; i++){

		SPDR = send;
		while(!(SPSR & (1<<SPIF)));
		tmp = SPDR;

		rcve |= (tmp << 8*i);
		send = (send >> 8);
	}

	return rcve;
}

float SPI_transfer_float(float data){
	uint32_t int_send, int_rcve;
	float float_rcve;
	uint32_t  tmp = 0;

	float_to_int(data, &int_send);
	int i;

	for(i = 0; i < 4; i++){
		SPDR = int_send & MASK;

		while(!(SPSR & (1 << SPIF)));
		tmp = SPDR;

		int_rcve |= (tmp << 8*i);
		int_send = (int_send >> 8);
	}

	int_to_float(int_rcve, &float_rcve);

	return float_rcve;
}

unsigned char SPI_transfer_char(unsigned char send){
	SPDR = send;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
usart
