#include <body.h>
#include <barnes_hut.h>

static Node create () {
	Node k = malloc (sizeof(struct node));
	k->left = NULL;
	k->right = NULL;
	k->up = NULL;
	k->down = NULL;
	return malloc (sizeof(struct node));
}

void inseri (corpo k, Node topo) {

}

void barnes_hut (corpo *corpos, int N){
	int i;
	Node topo
	for(i = 0; i < N; i++) insere (corpo[i], Node topo);

}
