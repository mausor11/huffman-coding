#include <stdio.h>
#include <stdlib.h>

#include "krokiet.h"
#include "tree.h"
#include "bitbajt.h"
#include "list.h"

void fillKrokiet(d_t tree, krokiet_t obiad[], int poziom, int what) {
	// jesteśmy w węźle - wszystkie kody znaków w nim dostają zero
	if(tree->counter == 0) {
		for(int i = 0; i < 256; i++)
			if(obiad[i].done != 1)
				obiad[i].kod[poziom] = what;
	}
	// znaleźliśmy liść - zakończyć dla tego znaku
	else {
		obiad[tree->znak].kod[poziom] = what;
		obiad[tree->znak].kod[poziom+1] = poziom;
		obiad[tree->znak].done = 1;
	}
	if(tree->left_node != NULL)
		fillKrokiet(tree->left_node, obiad, poziom+1, 0);
	if(tree->right_node != NULL)
		fillKrokiet(tree->right_node, obiad, poziom+1, 1);
}

void prepareKrokiet(krokiet_t obiad []) {
	for(int i = 0; i < 256; i++) {
		obiad[i].done = -1;
		for(int j = 0; j < 258; j++)
			obiad[i].kod[j] = -1;
	}
}

void printKrokiet(krokiet_t obiad[]) {
	printf("\n==printing krokiet==\nznak - kod\n\n");
	for(int i = 0; i < 256; i++)
		if(obiad[i].done == 1) {
			printf("%c - ", i);
			for(int j = 1; obiad[i].kod[j+1] >= 0; j++)
				printf("%d", obiad[i].kod[j]);
			printf("\n");
		}
}


void codeFile(krokiet_t obiad[], FILE *in, FILE *out, char *temp, char *cntr) {
	char *buf = malloc(100 * sizeof (*buf) );
	int liczba = bajt(buf, in, 100);
	while(liczba != 0) {
		for(int i = 0; i < liczba; i++) {
			int j = 1;
			while(obiad[*(buf+i)].kod[j+1] >= 0) {

				// zapełnienie temp
				if(*cntr == 8) {
					fwrite(temp, sizeof(char), 1, out);
//					printf("dodano do listy. %d, %c\n", lista->c, *temp);
//					printList(lista);
					*temp = 0;
					(*cntr) -= 8;
				}

				(*temp) <<= 1;
				(*temp) += obiad[*(buf+i)].kod[j++];
				(*cntr)++;
				//j++;
			}
		}

		liczba = bajt(buf, in, 100);	// kolejna dawka danych
	}
	free(buf);
}

/*

zostawiam zakomentarzowane jako przestrogę dla mnie z przyszłości
taki kod jest ble fuj

lista_t codeFile(krokiet_t obiad[], FILE *in, char *temp, char *cntr) {
	lista_t lista = NULL;
	char *buf = malloc(100 * sizeof (*buf) );
	int liczba = bajt(buf, in, 100);
	while(liczba != 0) {
		for(int i = 0; i < liczba; i++) {
			int j = 1;
			while(obiad[*(buf+i)].kod[j+1] >= 0) {

				// zapełnienie temp
				if(*cntr == 8) {
					lista = addToList(lista, *temp);
//					printf("dodano do listy. %d, %c\n", lista->c, *temp);
//					printList(lista);
					*temp = 0;
					(*cntr) -= 8;
				}

				(*temp) <<= 1;
				(*temp) += obiad[*(buf+i)].kod[j++];
				(*cntr)++;
				//j++;
			}
		}

		liczba = bajt(buf, in, 100);	// kolejna dawka danych
	}
	free(buf);
	return lista;
}
*/

void decodeFile() {

}

// while fread != 0 (/sczyt do listy true) && lista->next != NULL

char decode(d_t tree, lista_t *in, union eitbit *temp, char *cntr) {
	if(!(*cntr) ) {
		if(in == NULL) {
			
			(*cntr)--;
			return 0;
		}
		temp->A = (*in)->c;
		(*in) = (*in)->next;
		(*cntr) += 8;
	}
	if(tree->counter) {
		return tree->znak;
	}
	else {
		if(!bit(temp->A, 7) ) {
			temp->A <<= 7;
			(*cntr)--;
			return decode(tree->left_node, in, temp, cntr);
		}
		else {
			temp->A <<= 7;
			(*cntr)--;
			return decode(tree->right_node, in, temp, cntr);
		}
	}
}
