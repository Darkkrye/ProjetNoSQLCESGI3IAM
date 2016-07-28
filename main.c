#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "json.h"

int main (int argc, char **argv) {
	t_map* map = JSON_parse("{test 1 : 'coucou1'},{ test 2 : 'coucou2'}");
	printf("HERE ?\n");
	char* a = "test 1";
	char* b = "test 2";
	printf("%s\n", map_get(map, a));
	printf("%s\n", map_get(map, b));
	//JSON_parse("{ AHAHAH OHOH: fds},{ IHIHIH OHOH : fds}");
	//JSON_parse("{AHAHAH OHOH: fds},{ IHIHIH OHOH : fds}");

}