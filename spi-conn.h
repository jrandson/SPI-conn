/************************************************************************/
/* PORTA are used to syncronize the slavers
/* PORTC are used as select slave
/************************************************************************/

void send_population(unsigned int population[][N], int size_population);
void rcve_population(unsigned int population[][N], int size_population);
void rcve_fitness(float fitness[], int size_population);
void send_fitness(float fitness[], int size_population);
unsigned char SPI_transfer_char(unsigned char send);
void float_to_int(float f, uint32_t *i);
void int_to_float(uint32_t i, float *f);
uint32_t SPI_transfer_int(uint32_t send);
float SPI_transfer_float(float data);


#define MASK  0b11111111

typedef union{
	float f;
	long long int i;
} my_union;
