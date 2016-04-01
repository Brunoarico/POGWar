struct node {
	float pos[2];
	float mass;
	Node left, right, down, up;
} * Node;

void barnes_hut (corpo *corpos, int N);