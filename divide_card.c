#include <stdio.h>
#include <stdlib.h>


typedef struct card_divede_t {
	int single[15];
	int two[15];
	int tree[15];
	int four[15];
	int single_even[2];
	int single_even[4];
}card_divide_t;


int *turn_card_into_15_len_array(int card[], int num)
{
	int i, card_value;
	int *new_card_array;
	

	new_card_array = (char*)malloc(sizeof(int) * num);
	for (i = 0; i < num; i++) {
		new_card_array[i] = 0;
	}

	for (i = 0; i < num; i++) {
		card_value = card[i];
		new_card_array[card_value] += 1;
	}

	return new_card_array;
}

