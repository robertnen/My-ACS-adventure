#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

// Functia get_operations intializeaza vectorul de operatii

void get_operations(void **operations);

// Functia read_sensor citeste vectorul de senzori dintr-un fisier

void read_sensor(sensor *senzori, FILE *fisier_in, int nr_senzori)
{
	// In timp ce citim din fisier vom si ordona vectorul in functie de
	// tipul senzorului
	// Pentru sortare ne vom folosi de o variabila last_index_pmu care
	// retine ultima pozitie a vectorului in care retinem un senzor de
	// tip pmu
	int j = 0, i = 0, last_index_pmu = 0, k = 0;
	for (i = 0; i < nr_senzori; i++) {
		fread(&senzori[i].sensor_type, sizeof(int), 1, fisier_in);
		// Daca senzorul este de tip tire il adaugam la finalul vectorului
		if (senzori[i].sensor_type == 0) {
			tire_sensor *sensor_data =
					(tire_sensor *)malloc(1 * sizeof(tire_sensor));
			fread(sensor_data, sizeof(tire_sensor), 1, fisier_in);
			senzori[i].sensor_data = sensor_data;
			fread(&senzori[i].nr_operations, sizeof(int), 1, fisier_in);
			senzori[i].operations_idxs =
					(int *)malloc(senzori[i].nr_operations * sizeof(int));
			for (j = 0; j < senzori[i].nr_operations; j++) {
				fread(&senzori[i].operations_idxs[j],
						sizeof(int), 1, fisier_in);
			}
		} else {
			// Daca senzorul este de tip pmu il inseram pe pozitia
			// last_index_pmu
			if (i != last_index_pmu) {
				for (k = i; k > last_index_pmu; k--) {
					senzori[k] = senzori[k-1];
				}
			}
			power_management_unit *sensor_data =
			(power_management_unit *)malloc(1 * sizeof(power_management_unit));
			fread(sensor_data, sizeof(power_management_unit), 1, fisier_in);
			senzori[last_index_pmu].sensor_type = 1;
			senzori[last_index_pmu].sensor_data = sensor_data;
			fread(&senzori[last_index_pmu].nr_operations,
					sizeof(int), 1, fisier_in);
			senzori[last_index_pmu].operations_idxs =
			(int *)malloc(senzori[last_index_pmu].nr_operations * sizeof(int));
			for (j = 0; j < senzori[last_index_pmu].nr_operations; j++) {
				fread(&senzori[last_index_pmu].operations_idxs[j],
						sizeof(int), 1, fisier_in);
			}
			last_index_pmu++;
		}
	}
}

// Functia print afiseaza pe ecran senzorul de la un index dat

void print(sensor *senzori, int index, int nr_senzori)
{
	// Daca indexul dat nu se afla intre 0 si numarul de senzori atunci
	// se afiseaza pe ecran "Index not in range!"
	if (index < 0 || index >= nr_senzori) {
		printf("Index not in range!\n");
		return;
	}
	// Daca senzorul este de tip tire atunci afisam pe ecran caracteristicile
	// specifice senzorului
	if (senzori[index].sensor_type == 0) {
		tire_sensor *tire = (tire_sensor *)senzori[index].sensor_data;
		printf("Tire Sensor\n");
		printf("Pressure: %.2f\n", tire->pressure);
		printf("Temperature: %.2f\n", tire->temperature);
		printf("Wear Level: %d%%\n", tire->wear_level);
		if (tire->performace_score <= 0) {
			printf("Performance Score: Not Calculated\n");
		} else {
			printf("Performance Score: %d\n", tire->performace_score);
		}
	} else {
		// Daca senzorul este de tip pmu atunci afisam pe ecran
		// caracteristicile specifice senzorului
		power_management_unit *pmu =
				(power_management_unit *)senzori[index].sensor_data;
		printf("Power Management Unit\n");
		printf("Voltage: %.2f\n", pmu->voltage);
		printf("Current: %.2f\n", pmu->current);
		printf("Power Consumption: %.2f\n", pmu->power_consumption);
		printf("Energy Regen: %d%%\n", pmu->energy_regen);
		printf("Energy Storage: %d%%\n", pmu->energy_storage);
	}
}

// Functia analyze apeleaza functiile din vectorul operations_idx

void analyze(sensor *senzori, int index, int nr_senzori)
{
	// Daca indexul nu se afla intre 0 si numarul de senzori atunci
	// pe ecran se afiseaza mesajul "Index not in range!"
	if (index < 0 || index >= nr_senzori) {
		printf("Index not in range!\n");
		return;
	}
	int i = 0, k = 0;
	void *operatii[8];
	// Initializam vectorul cu operatii
	get_operations(operatii);
	for (i = 0; i < senzori[index].nr_operations; i++) {
		k = senzori[index].operations_idxs[i];
		((void (*) (void *))operatii[k])(senzori[index].sensor_data);
	}
}

// Functia verify_tire_sensor verifica daca senzorul de tip tire este valid

int verify_tire_sensor(tire_sensor *tire)
{
	if (tire->pressure < 19 || tire->pressure > 28) {
		return 0;
	}
	if (tire->temperature < 0 || tire->temperature > 120) {
		return 0;
	}
	if (tire->wear_level < 0 || tire->wear_level > 100) {
		return 0;
	}
	return 1;
}

// Functia verify_pmu_sensor verifica daca senzorul de tip pmu este valid

int verify_pmu_sensor(power_management_unit *pmu)
{
	if (pmu->voltage < 10 || pmu->voltage > 20) {
		return 0;
	}
	if (pmu->current < -100 || pmu->current > 100) {
		return 0;
	}
	if (pmu->power_consumption < 0 || pmu->power_consumption > 1000) {
		return 0;
	}
	if (pmu->energy_regen < 0 || pmu->energy_regen > 100) {
		return 0;
	}
	if (pmu->energy_storage < 0 || pmu->energy_storage > 100) {
		return 0;
	}
	return 1;
}

// Functia clear elimina vectorii care sunt invalizi

sensor* clear(sensor *senzori, int index, int nr_senzori)
{
	int i = 0;
  sensor tmp;
	for (i = index; i < nr_senzori - 1; i++) {
    tmp = senzori[i];
		senzori[i] = senzori[i+1];
    senzori[i+1] = tmp;
  }
  free(senzori[nr_senzori - 1].sensor_data);
	free(senzori[nr_senzori - 1].operations_idxs);
	// Realocam dinamic vectorul de senzori
	senzori = realloc(senzori, (nr_senzori - 1) * sizeof(sensor));
  return senzori;
}

// Functia free_sensor elibereaza memoria din vector

void free_sensor(sensor *senzori, int nr_senzori)
{
	int i = 0;
	for (i = 0; i < nr_senzori; i++) {
		free(senzori[i].sensor_data);
		free(senzori[i].operations_idxs);
	}
	free(senzori);
}

int main(int argc, char const *argv[])
{
	FILE *fisier_in;
	int nr_senzori = 0, i = 0;
	// Deschidem fisierul
	fisier_in = fopen(argv[1], "rb");
	// Citim numarul de senzori din fisier
	fread(&nr_senzori, sizeof(int), 1, fisier_in);
	sensor *senzori = (sensor *)malloc(nr_senzori * sizeof(sensor));
	read_sensor(senzori, fisier_in, nr_senzori);
	// Alocam dinamic un pointer care sa retina comanda data
	char *comanda = (char *)malloc(30 * sizeof(char));
	fgets(comanda, 30, stdin);
	// Executam comenzile pana cand primim comanda exit
	while (strstr(comanda, "exit") == 0) {
		if (strstr(comanda, "print")) {
			char *p = strtok(comanda, " \n");
			p = strtok(NULL, " \n");
			int index = atoi(p);
			print(senzori, index, nr_senzori);
		}
		if (strstr(comanda, "analyze")) {
			char *p = strtok(comanda, " \n");
			p = strtok(NULL, " \n");
			int index = atoi(p);
			analyze(senzori, index, nr_senzori);
		}
		if (strstr(comanda, "clear")) {
			// Verificam pentru fiecare cuvant daca este valid sau nu
			for (i = 0; i < nr_senzori; i++) {
				if (senzori[i].sensor_type == 0) {
					if (verify_tire_sensor(senzori[i].sensor_data) == 0) {
						senzori = clear(senzori, i, nr_senzori);
						nr_senzori--;
						i--;
					}
				} else {
					if (verify_pmu_sensor(senzori[i].sensor_data) == 0) {
					senzori = clear(senzori, i, nr_senzori);
					nr_senzori--;
					i--;
					}
				}
			}
		}
		fgets(comanda, 30, stdin);
	}
	free(comanda);
	free_sensor(senzori, nr_senzori);
	fclose(fisier_in);
	return 0;
}