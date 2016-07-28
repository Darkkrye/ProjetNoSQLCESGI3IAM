#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "json.h"

t_map* JSON_parse(char* str) {
	t_map* map = map_create(5, 1, 1);
	void* value;
	char* key;
	int isKey = 0;
	int isValue = 0;


	for(int i = 0; i < strlen(str) ; i++) {
		int keyInProgress = 0;
		int save = 0;
		int idx = 0;
		int cnt = 0; 

		// Get char by char
		char c = str[i];
		
		// If char is '{', start get key
		if(c == '{' || c == ',') {
			isKey = 0;
			char k[50] = "";
			for(int j = 1 ; str[i+j] != ':' ; j++) {
				char cbis = str[i+j];
				char cbisbis = str[i+j+1];
				if( cbis != ' ' || keyInProgress == 1) {
					if(cbisbis != ':') {
						if(idx == 0) idx = i+j;
						cnt++;
						keyInProgress = 1;
					} else {
						cnt++;
						keyInProgress = 0;
					}
				}
				save = j;
			}
			char test[cnt+2];
			strncpy(test, &str[idx], cnt+1);
			test[cnt] = '\0';
			/////
			key = strndup(test, sizeof(test));
			isKey = 1;
			/////
			i = i+save;
		}
		if(c == ':') {
			i++;
			c = str[i];
		}
		if(c == '\'') {
			isValue = 0;
			for(int j = 1 ; str[i+j] != '\'' ; j++) {
				char cbis = str[i+j];
				char cbisbis = str[i+j+1];
				if( cbis != '\'' || keyInProgress == 1) {
					if(cbis == '\'') {
						keyInProgress = 0;
					
					}
					if(idx == 0) idx = i+j;
					cnt++;
					keyInProgress = 1;
				} 
				save = j;
			}
			char test[cnt+1];
			strncpy(test, &str[idx], cnt);
			test[cnt] = '\0';
			/////
			value = strndup(test, sizeof(test));
			isValue = 1;
			/////
			i = i+save+1;
		}

		if(isValue == 1 && isKey == 1) {
			isKey = 0;
			isValue = 0;
			map_put(map, key, value);
		}
	}
	return map;
}

char* JSON_stringify(t_map* map) {

	char str[200] = "";
    for(int i = 0 ; i < map->slots ; i++) {
        t_map_entry* entries = map->entries[i];
        strcat(str, "{");
        // While there is an entry
        while(entries != NULL) {
            strcat(str, entries->key);
            strcat(str, ":");
            strcat(str, "'");
            strcat(str, entries->value);
            strcat(str, "'");
            
            entries = entries->next;

            // If there is a next element
            if(entries != NULL)
                strcat(str, ",");
        }

        strcat(str, "}");
    }
    return strdup(str);
}