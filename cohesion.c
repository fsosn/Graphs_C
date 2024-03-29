#include "cohesion.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cohesion(int x, int y, double arr[x * y][x * y], int n) {

	int a = x * y;

	double(*dystans) = calloc(a, sizeof * dystans);
	double(*przodek) = calloc(a, sizeof * przodek);
	double(*odwiedzone) = calloc(a, sizeof * odwiedzone);
	int(*edge) = calloc(a, sizeof * edge);

	int zlicz, nastepca, i, j, rand_start, rand_end, dzielnik1, dzielnik2, zamiennik, tura;
	double mindystans;
	int w;
	w = 0;

	if(dystans == NULL){
		fprintf(stderr, "%s", "Nieudana alokacja pamieci\n");
		exit(EXIT_FAILURE);
	}

	if(przodek == NULL){
		fprintf(stderr, "%s", "Nieudana alokacja pamieci\n");
		exit(EXIT_FAILURE);
	}

	if(odwiedzone == NULL){
		fprintf(stderr, "%s", "Nieudana alokacja pamieci\n");
		exit(EXIT_FAILURE);
	}

	if(edge == NULL){
		fprintf(stderr, "%s", "Nieudana alokacja pamieci\n");
		exit(EXIT_FAILURE);
	}



	dzielnik1 = x;
	dzielnik2 = 0;
	tura = 0;

	srand(time(NULL));

	while ((tura < n - 1) && w < 999999) {
		for (i = 0; i < a; i++) {
			edge[i] = 0;
			for (j = 0; j < a; j++) {
				if (arr[i][j] == 1) {
					edge[i]++;
				}
			}
		}

		rand_start = rand() % a;

		while ((edge[rand_start] == 4 || edge[rand_start] == 0 || rand_start < ((x * y) - dzielnik1) || rand_start > ((x * y)-dzielnik2-1) || rand_start == ((x * y) - dzielnik2-1)) && w < 999999 ) {
			rand_start = rand() % a;
		}

		rand_end = rand() % a;

		while ((edge[rand_end] == 4 || edge[rand_end] == 0 || rand_end < ((x * y) - dzielnik1) || rand_end > ((x * y) - dzielnik2 - 1) || rand_end < rand_start || rand_end == rand_start) && w < 999999) {
			rand_end = rand() % a;
			w++;
		}

		for (i = 0; i < a; i++)
			for (j = 0; j < a; j++)
				if (arr[i][j] == 0)
					arr[i][j] = 9999999;

		for (i = 0; i < a; i++) {
			dystans[i] = arr[rand_start][i];
			przodek[i] = rand_start;
			odwiedzone[i] = 0;
		}

		dystans[rand_start] = 0;
		odwiedzone[rand_start] = 1;
		zlicz = 1;

		while (zlicz < a - 1) {

			mindystans = 9999999;

			for (i = 0; i < a; i++)
				if (dystans[i] < mindystans && !odwiedzone[i]) {
					mindystans = dystans[i];
					nastepca = i;
				}

			odwiedzone[nastepca] = 1;
			for (i = 0; i < a; i++)
				if (!odwiedzone[i])
					if (mindystans + arr[nastepca][i] < dystans[i]) {
						dystans[i] = mindystans + arr[nastepca][i];
						przodek[i] = nastepca;
					}
			zlicz++;
		}

		for (i = rand_end; i < rand_end + 1; i++)
			if (i != rand_start)
			{
				j = i;
				do
				{
					zamiennik = j;
					j = przodek[j];
					arr[zamiennik][j] = 0;
					arr[j][zamiennik] = 0;
				} while (j != rand_start);

				for (i = 0; i < a; i++) {
					arr[rand_start][i] = 0;
					arr[i][rand_start] = 0;

				}
			}
		dzielnik1 = dzielnik1 + x;
		dzielnik2 = dzielnik2 + x;
		tura++;

	}

	for (i = 0; i < a; i++) {
		for (j = 0; j < a; j++) {
			if (arr[i][j] == 9999999) {
				arr[i][j] = 0;
			}
		}
	}

	free(dystans);
	free(przodek);
	free(odwiedzone);
	free(edge);
}
