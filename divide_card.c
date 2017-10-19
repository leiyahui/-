#include <stdio.h>
#include <stdlib.h>
#include "send_card.h"
#include "log.h"

typedef struct _node_t{
	int value;
	int count;
	int confict;
	char *ptr_one;
	char *ptr_two;
	char *ptr_three;
	char *ptr_four;
	char *ptr_single_even[3];
}node_t;

typedef struct _even_t {
	int start_value;
	int end_value;
	node_t *ptr[15];
}even_t;

typedef struct card_divede_t {
	node_t *single[17];
	node_t *two[17];
	node_t *three[17];
	node_t *four[17];
	int without[17];
	int single_even_count;
	even_t single_even[3];
	even_t even_on[3];
}card_divide_t;


node_t *		base_node[15];
card_divide_t	*card_divide, *tmp_card_divide;
int g_call_level;


card_divide_t *create_card_divide() {
	int i;
	card_divide_t *divide;

	divide = (card_divide_t *)malloc(sizeof(card_divide_t));
	for (i = 0; i <= 17; i++) {
		divide->without[i] = 0;
		divide->single[i] = NULL;
		divide->three[i] = NULL;
		divide->four[i] = NULL;
	}
	divide->single_even_count = 0;
	return divide;
}

void init_base_node()
{
	int i;
	for (i = 0; i <= 17; i++) {
		base_node[i] = malloc(sizeof(node_t));
		base_node[i]->value = i;
	}
	card_divide = create_card_divide();
	tmp_card_divide = create_card_divide();
}

int *turn_card_into_17_len_array(int card[], int num)
{
	int i, card_value;
	int *new_card_array;
	

	new_card_array = (char*)malloc(sizeof(int) * 18);
	for (i = 0; i < 18; i++) {
		new_card_array[i] = 0;
	}

	for (i = 0; i < num; i++) {
		card_value = card[i];
		new_card_array[card_value] += 1;
	}

	return new_card_array;
}

int get_min_hand(int card_array[], int total_begin, int total_end)
{
	int i, j, m, n, t, start, end, tmp_hand_num, hand_num, single_even_start, single_even_end;

	int new_card_array[18];
	i = 3;
	hand_num = 0;

	while (total_begin <= 17 && card_array[total_begin] == 0) {
		total_begin++;
	}
	for (i = 3; i <= total_end; i++) {
		if (card_array[i] != 0) {
			hand_num++;
		}
	}
	tmp_hand_num = hand_num;
	start = total_begin;

	if (hand_num <= 4) {
		return hand_num;
	}
	g_call_level++;
	
	for (i = total_begin; i <= total_end; i++) {
		if (card_array[i] == 0 || i == total_end) {
			if (i == total_end) {
				i++;
			}
			if (i - start >= 5) {
				if (g_call_level == 1) {
					log_debug("may have array start :%d,end :%d", start, i - 1);
				}
				else if (g_call_level == 2) {
					log_debug("        may have array start :%d,end :%d", start, i - 1);
				}
				else {
					log_debug("                    may have array start :%d,end :%d", start, i - 1);
				}
				single_even_start = single_even_end = 0;
				for (m = start; m <= i - 5; m++) {
					for (n = m + 4; n < i; n++) {
						if (g_call_level == 1) {
							log_debug("    possible single even :%d,end :%d", start, n);
						}
						else if (g_call_level == 2) {
							log_debug("          possible single even :%d,end :%d", start, n);
						}
						else {
							log_debug("                       possible single even :%d,end :%d", start, n);
						}
						for (t = 0; t < 18; t++) {
							new_card_array[t] = card_array[t];
						}
						for (t = m; t <= n; t++) {
							new_card_array[t] = card_array[t] - 1;
						}
						tmp_hand_num = get_min_hand(new_card_array, start, i - 1);
						if (tmp_hand_num + 1 < hand_num) {
							hand_num = tmp_hand_num + 1;
							single_even_start = m;
							single_even_end = n;
						}
					}
				}
				if (single_even_end != 0 && single_even_start != 0) {
					card_divide->single_even[card_divide->single_even_count].start_value = single_even_start;
					card_divide->single_even[card_divide->single_even_count].end_value = single_even_end;
					card_divide->single_even_count++;
					if (g_call_level == 1) {
						log_debug("single even is:%d, %d", single_even_start, single_even_end);
					}
					else if (g_call_level == 2) {
						log_debug("        single even is : %d, %d", single_even_start, single_even_end);
					}
					else {
						log_debug("                    single even is : %d, %d", single_even_start, single_even_end);
					}
				}
			}
			if (g_call_level == 1) {
				start = i + 1;
			}
			else {
				start = i + 1;
			}
		}
	}
	g_call_level--;
	return hand_num;
}

void divide_card(int card_array[])
{
	int i, j, start, end, conflict_count, hand_num;
	
	for (i = 3; i < 18; i++) {
		if (card_array[i] == 4) {
			card_divide->four[i] = base_node[i];
		}
		else if (card_array[i] == 3) {
			card_divide->three[i] = base_node[i];
		}
		else if (card_array[i] == 2) {
			card_divide->two[i] = base_node[i];
		}
		else if (card_array[i] == 1) {
			card_divide->single[i] = base_node[i];
		}
		else {
			card_divide->without[i] = 1;
		}
	}
	g_call_level = 0;
	get_min_hand(card_array, 3, 14);
}

void main()
{
	int i;
	int *card_array;
	init_logfile_fd(1000000);
	init_card();
	wash_card();
	card[0] = 10;
	card[1] = 9;
	card[2] = 5;
	card[3] = 3;
	card[4] = 4;
	card[5] = 5;
	card[6] = 6;
	card[7] = 7;
	card[8] = 8;
	card[9] = 9;
	card[10] = 10;
	card[11] = 11;
	card[12] = 12;
	card[13] = 13;
	card[14] = 14;
	card[15] = 7;
	card[16] = 8;
	card_array = turn_card_into_17_len_array(card, 17);
	for (i = 3; i < 18; i++) {
		printf("%d:%d ", i, card_array[i]);
	}
	printf("\n");
	init_base_node();
	divide_card(card_array);
	printf("single: \n");
	for (i = 3; i < 18; i++) {
		if (card_divide->single[i] != NULL) {
			printf("%d ", i);
		}
	}
	printf("\ntwo: \n");
	for (i = 3; i < 18; i++) {
		if (card_divide->two[i] != NULL) {
			printf("%d ", i);
		}
	}
	printf("\nthree: \n");
	for (i = 3; i < 18; i++) {
		if (card_divide->three[i] != NULL) {
			printf("%d ", i);
		}
	}
	printf("\nfour: \n");
	for (i = 3; i < 18; i++) {
		if (card_divide->four[i] != NULL) {
			printf("%d ", i);
		}
	}
	printf("\n");
	for (i = 0; i < card_divide->single_even_count; i++) {
		printf("single even: %d, %d\n", card_divide->single_even[i].start_value, card_divide->single_even[i].end_value);
	}
}
