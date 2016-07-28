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
		printf("## %d ## %c\n", i, c);
		
		// If char is '{', start get key
		if(c == '{'/* || c == ','*/) {
			isKey = 0;
			printf("%d -> i\n", i);
			char k[50] = "";
			for(int j = 1 ; str[i+j] != ':' ; j++) {
				printf("# %d #\n", i+j);
				char cbis = str[i+j];
				char cbisbis = str[i+j+1];
				if( cbis != ' ' || keyInProgress == 1) {
					if(cbisbis != ':') {
						if(idx == 0) idx = i+j;
						cnt++;
						// printf("%s\n", &cbis);
						keyInProgress = 1;
						// strcat(k, &cbis);
						// printf("%s\n", k);
					} else {
						keyInProgress = 0;
					}
				}
				save = j;
			}
			char test[cnt+1];
			strncpy(test, &str[idx], cnt);
			test[cnt] = '\0';
			printf("~~~~~ %s\n", test);
			/////
			key = strndup(test, sizeof(test));
			isKey = 1;
			/////
			i = i+save;
			printf("k : %s\n", k);
//			return NULL;
		}
		if(c == ':') {
			printf("TWO POINTS\n");
			i++;
			c = str[i];
			printf("++++++++ %c\n", c);
			printf("++++++++ %c\n", str[i+1]);
		}
		if(c == '\'') {
			isValue = 0;
			for(int j = 1 ; str[i+j] != '}' ; j++) {
				printf("@ %d @\n", i+j);
				char cbis = str[i+j];
				char cbisbis = str[i+j+1];
				if( cbis != '\'' || keyInProgress == 1) {
					if(cbisbis != '}' && cbisbis != ' ') {
						if(idx == 0) idx = i+j;
						cnt++;
						// printf("%s\n", &cbis);
						keyInProgress = 1;
						// strcat(k, &cbis);
						// printf("%s\n", k);
					} else {
						keyInProgress = 0;
					}
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
			printf("~~~~~ %s\n", test);
			i = i+save+1;
		}

		if(isValue == 1 && isKey == 1) {
			printf("%s - %s\n", key, value);
			map_put(map, key, value);
			printf("OK\n");
		}
		printf("-> %d\n", i);
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
            // If there isn't next element
            if(entries != NULL)
                strcat(str, ",");
        }

        strcat(str, "}");
    }
    return strdup(str);
}