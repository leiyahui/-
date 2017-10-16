#include <stdio.h>
#include <stdlib.h>

#define TOTAL_CARD_NUM				54
#define PER_USER_DEFAULT_CAR_NUM	17

void swap_card(int card[], int i, int j)
{
	int tmp;
	
	tmp = card[i];
	card[i] = card[j];
	card[j] = tmp;
}

void wash_card(int card[], int card_num) {
	int i, j;
	for (i = 0; i < TOTAL_CARD_NUM; i++) {
		j = rand() / TOTAL_CARD_NUM;
		swap_card(card, i, j);
	}
}

int get_landloard() {
	return rand() / 3;
}
