#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

int main() {
	d_t tree = createTree();
	int ile = 0;
	char c = 'e';
	table_t tab[4];
	// insert
	tree->znak = 'a';
	tree->counter = 10;
	tree = extend(tree, 'b', 'p', 1);
	tree->right_node->counter = 100;
	tree->right_node = extend(tree->right_node, 'c', 'n', 1);
	tree->right_node->left_node->counter = 1;
	tree->right_node = extend(tree->right_node, 'd', 'p', 1);
	tree->right_node->right_node->counter = 1000;
	counter(tree, &ile);
	printf("Drzewo ze wczytania\n\nliczba liści drzewa: %d\n\n", ile);
	writeTree(tree, 0);

/*
	for(i = 0; i < ile; i++) {
		tab[ile-1-i].priority = maxi;
		rarestt(tree, &( tab[ile-1-i].tree ) , &( tab[ile-1-i].priority) );
		printf("%p\n", tab[ile-1-i].tree);
		tab[ile-1-i].tree->counter = -1;
	}
	for(i = 0; i < ile; i++)
		printf("znak: %c, priorytet: %d\n", tab[i].tree->znak, tab[i].priority );
	for(i = 0; i < 4; i++) {
		tab[i].tree->right_node = NULL;
		tab[i].tree->left_node = NULL;
	}

	tree = tab[0].tree;
	for(i = 0; i < ile-1; i++)
		tab[i].tree->right_node = tab[i+1].tree;
	writeTree(tree);
	tab[3].tree = createTree();
	tab[3].tree->right_node = tab[0].tree;
	tab[3].tree->znak = 'x';
	tab[3].tree->counter = 112;
	tree = tab[3].tree;


*/
/*
	for(i = 0; tab[1].tree != NULL; i++) {
		int j = ile-i-1, temp;
		tree = createTree();
		tree->counter = 0;
		tree->right_node = tab[j].tree;
		tree->left_node = tab[j-1].tree;
		tab[j].tree = NULL;
		tab[j-1].tree = tree;
		tab[j-1].priority += tab[j].priority;
		tab[j].priority = 0;
		j--;
		while(j > 0 && ( tab[j].priority >= tab[j-1].priority ) ) {
			tree = tab[j].tree;
			temp = tab[j].priority;
			tab[j].tree = tab[j-1].tree;
			tab[j].priority = tab[j-1].priority;
			tab[j-1].tree = tree;
			tab[j-1].priority = temp;
		}
	}

	tree = tab[0].tree;
	tab[0].tree = NULL;
*/
	tree = makeHTree(tree);
	printf("\nDrzewo Huffmana\n\n");
	writeTree(tree, 0);
	ile = 0;
	counter(tree, &ile);
	printf("%d\n", ile);
	FILE *out = fopen("tutej_drzewo", "wb");
	freeTree(tree);
	return 0;
}