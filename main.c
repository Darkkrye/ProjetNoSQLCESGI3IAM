#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "hashmap.h"
#include "json.h"

int nosql_insert(char* collection, char* json);
void nosql_find(char* collection, t_map* params);


int main (int argc, char **argv) {

	char* collection_name;
	char* val;
	
	char* insert = NULL;
    if(argc > 1) {
    	for(int i = 1 ; i < argc ; i++) {
    		char* key = strsep(&argv[i], "=");

    		if(strcmp(key, "-collection") == 0) {
    			collection_name = strsep(&argv[i], "=");
    		}

    		if(strcmp(key, "-insert") == 0) {
    			val = strsep(&argv[i], "=");

    			nosql_insert(collection_name, val);
    		}

            if(strcmp(key, "-find") == 0) {
                val = strsep(&argv[i], "=");
                t_map* params = JSON_parse(val);
                nosql_find(collection_name, params);
            }

            if(strcmp(key, "-help") == 0) {
                printf("./myFile.o -collection=\"COLLECTION_NAME\" -insert=\"{key1:'value1',key2:'value2'}\"\n");
                printf("./myFile.o -collection=\"COLLECTION_NAME\" -find=\"{key:'value'}\"\n");
            }
    	}
    } else {
        printf("NOT ENOUGH ARGUMENTS \n\n");
        printf("./myFile.o -collection=\"COLLECTION_NAME\" -insert=\"{key1:'value1',key2:'value2'}\"\n");
        printf("./myFile.o -collection=\"COLLECTION_NAME\" -find=\"{key:'value'}\"\n");
    }

    return 0;
}


int nosql_insert(char* collection, char* json) {
    FILE* fp = fopen(collection, "a");
    if (fp == NULL) return -1;
    int success = fprintf(fp, "%s\n", json) > 1;
    fclose(fp);
    return success;
}

void nosql_find(char* collection, t_map* params) {
    FILE *fp;
    char ch;
    t_map_entry** entry = params->entries;

    char* keyToFind;
    char* valueToFind;

    for(int i = 0 ; i < params->slots ; i++) {
        if(entry[i] != NULL) {
            keyToFind = entry[i]->key;
            valueToFind = entry[i]->value;
        }
    }
 
    fp = fopen(collection,"r"); // read mode

    int start = 0;
    int cnt = 0;
    char line[256];
    t_map* current = NULL;
    while(fgets(line, sizeof(line), fp)) {    
        current = JSON_parse(line);
        char* aaa = map_get(current, keyToFind);
        if(strcmp(aaa, valueToFind) == 0) {
            printf("%s", line);    
        }
    }

    fclose(fp);
}