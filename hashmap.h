typedef struct s_map_entry {
	char* key;
	void* value;
	struct s_map_entry* next;
} t_map_entry;

typedef struct s_map {
	t_map_entry** entries;
	int slots;
	int size;
	float load_factor;
	float grow_factor;
} t_map;


t_map* map_create(int slots, float lf, float gf);

int map_hashcode(char* key);

void map_put(t_map* map, char* key, void* value);

void* map_get(t_map* map, char* key);

void* map_remove(t_map* map, char* key);

t_map_entry* map_entry_create(char* key, void* value);