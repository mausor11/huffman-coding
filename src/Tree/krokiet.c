#include <stdio.h>


#include "krokiet.h"
#include "tree.h"
#include "bitbajt.h"

void fillKrokiet(d_t tree, krokiet_t obiad[], int poziom, int what) {
	// jesteśmy w węźle - wszystkie kody znaków w nim dostają zero
	if(tree->counter == 0) {
		for(int i = 0; i < 256; i++)
			if(!obiad[i].done)
				obiad[i].kod[poziom] = what;
	}
	// znaleźliśmy liść - zakończyć dla tego znaku
	else {
		obiad[tree->znak].kod[poziom] = what;
		obiad[tree->znak].kod[poziom+1] = poziom;
		obiad[tree->znak].done = 1;
		printf("%c: %d\n", tree->znak, tree->znak);
		printf("%d\n", obiad[tree->znak].kod[poziom+1] );
	}
	if(tree->left_node != NULL)
		fillKrokiet(tree->left_node, obiad, poziom+1, 0);
	if(tree->right_node != NULL)
		fillKrokiet(tree->right_node, obiad, poziom+1, 1);
}

void emptyKrokiet(krokiet_t obiad []) {
	for(int i = 0; i < 256; i++)
		obiad[i].done = 0;
}

void printKrokiet(krokiet_t obiad[]) {
	printf("\n==printing krokiet==\nznak - kod\n\n");
	for(int i = 0; i < 256; i++)
		if(obiad[i].done == 1) {
			printf("%c - ", i);
			for(int j = 1; obiad[i].kod[j] != 2; j++)
				printf("%d", obiad[i].kod[j]);
			printf("\n");
		}
}


void codeFile(krokiet_t obiad[], FILE *in, FILE *out) {
	char *buf;
	int liczba = bajt(buf, in, 100);
	for(int i = 0; i < liczba; i++) {
		
	}
	free(buf);
}

