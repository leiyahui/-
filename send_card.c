#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARD_NUM				54
#define PER_USER_DEFAULT_CAR_NUM	17

int card[54];

void init_card()
{
	int i = 0;
	for (i = 8; i < TOTAL_CARD_NUM; i++) {		//assign value for 3-13
		card[i] = (i >> 2) + 1;
	}
	for (i = 0; i < 8; i++) {		//1 and 2 is assign to 14 and 15 for comparing value easily
		card[i] = (i >> 2) + 14;
	}

	card[52] = 16;		//black joker
	card[53] = 17;		//red joker
}

void swap_card(int card[], int i, int j)
{
	card[i] = card[i] ^ card[j];
	card[j] = card[i] ^ card[j];
	card[i] = card[i] ^ card[j];
}

void wash_card() {
	int i, j;
	srand(time(0));
	for (i = 0; i < TOTAL_CARD_NUM; i++) {
		j = rand() % TOTAL_CARD_NUM;
		swap_card(card, i, j);
	}
}

int get_landloard() {
	return rand() / 3;
}