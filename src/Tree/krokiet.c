#include <stdio.h>
#include <stdlib.h>

#include "krokiet.h"
#include "tree.h"
#include "bitbajt.h"

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
			for(int j = 1; ( (obiad[i].kod[j] == 0) || (obiad[i].kod[j] == 1) ) && obiad[i].kod[j+1] >= 0; j++)
				printf("%d", obiad[i].kod[j]);
			printf("\n");
		}
}


void codeFile(krokiet_t obiad[], FILE *in, FILE *out, unsigned char *temp, char *cntr) {
	unsigned char *buf = malloc(100 * sizeof (*buf) );
	int liczba = bajt(buf, in, 100);
	while(liczba != 0) {
		for(int i = 0; i < liczba; i++) {
			int j = 1;
			while( (obiad[*(buf+i)].kod[j] == 0) || (obiad[*(buf+i)].kod[j] == 1) && obiad[*(buf+i)].kod[j+1] >= 0 ) {

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



// // // // // // // // //

// spójrz na tremp, bo nie działa

d_t decodeFile(d_t tree, FILE *in, FILE *out, union eitbit *temp, char *cntr) {
	int liczba, whatBit, i;
	unsigned char recieved;
	unsigned char *buf = malloc(100 * sizeof(*buf) ), *cahr = NULL;
	d_t tremp;
//	liczba = fread(buf, sizeof(char), 100, in);
	while((liczba = fread(buf, sizeof(char), 100, in) ) ) {
		i = 0;
		while(i < liczba) {
			cahr = NULL;
			tremp = tree;
			while(cahr == NULL) {
				if((*cntr) == 0) {
					if(i < liczba) {
						temp->B = *(buf + i++);
//						printf("\t");
//						printBits(temp->A, 8);
//						printf(" ");
//						printBits(temp->B, 8);
//						printf("\n");
						(*cntr) += 8;
					}
					else
						break;		// jeżeli to, to ostatni bajt jest w temp->A
				}
				tremp = decode(tremp, temp, cntr);
//				writeTree(tremp, 0);
//				printf("\n\n");
				if((tremp->counter) ) {
					cahr = &recieved;
					recieved = tremp->znak;
//					printf("got a char! %c\n", recieved);
					fwrite(cahr, sizeof(char), 1, out);
				}
			}
		}

		// ostatni znak, patrz na istotne bity
		// dorobić else
		// ^nei
//		if(( liczba = fread(buf, sizeof(char), 100, in) ) == 0) {
	}
//	*temp = buf[liczba-1];
	if(cahr != NULL)
		tremp = tree;
//	*cntr += 8;
	free(buf);
	return tremp;
}



d_t decode(d_t tree, union eitbit *temp, char *cntr) {
	d_t trer = tree;
	while(*cntr){
		if(!bit(temp->A, 7) ){
			temp->ab <<= 1;
			(*cntr)--;
			trer = trer->left_node;
			if(trer->counter)
				return trer;
		}
		else {
			temp->ab <<= 1;
			(*cntr)--;
			trer = trer->right_node;
			if(trer->counter)
				return trer;
		}
	}
//	writeTree(trer, 0);
//	printf("\n");
	return trer;
}

