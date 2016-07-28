#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

t_map* map_create(int slots, float lf, float gf) {
    t_map* myMap = (t_map*)malloc(sizeof(t_map));
    myMap->entries = malloc(sizeof(t_map_entry*)*slots);
    for(int i = 0; i < slots; i++) {
        myMap->entries[i] = NULL;
    }
    myMap->slots = slots;
    myMap->size = 0;
    myMap->load_factor = lf;
    myMap->grow_factor = gf;
    return myMap;
}

int map_hashcode(char* key) {
    int hash = 0;
    for(int i = 0 ; key[i] != '\0' ; i++)
        hash = 42*hash+key[i];
    return abs(hash);
}

void* map_remove(t_map* map, char* key) {
    int slot = map_hashcode(key) % map->slots;
    t_map_entry** entries = &(map->entries[slot]);

    while ((*entries) != NULL) {
        if(strcmp((*entries)->key, key) == 0) {
            
            t_map_entry* prev = *entries;
            (*entries) = ((*entries)->next);
            void* value = prev->value;
            free(prev);
            return value;

        }
        entries = &((*entries)->next);
    }
    return NULL;
}

void* map_get(t_map* map, char* key) {
    int slot = map_hashcode(key) % map->slots;
    if (map->entries[slot] == NULL)
        return NULL;

    t_map_entry* entries = map->entries[slot];
    while (entries != NULL) {
        if (strcmp(entries->key,key) == 0) {
            return entries->value;
        }
        entries = entries->next;
    }
    return NULL;
}

t_map_entry* map_entry_create(char* key, void* value) {
    t_map_entry* myEntry = malloc(sizeof(t_map_entry));
    myEntry->key = key;
    myEntry->value = value;
    return myEntry;
}

void map_put(t_map* map, char* key, void* value) {
    // int slot = hashmap_hashcode(key, map->slots);
    // t_hashmap_entry** entries = &(map->entries[slot]);
    int slot = map_hashcode(key) % map->slots;
    t_map_entry** entries = &(map->entries[slot]);
    while (*entries != NULL) {
        if (strcmp((*entries)->key, key) == 0) {
            (*entries)->value = value;
            return;
        }
        entries = &((*entries)->next);
    }
    (*entries) = map_entry_create(key, value);
    map->size++;
}