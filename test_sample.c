#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"

#ifdef COUNTING_WORDS
#include "wordcount.h"
#endif

size_t mystrlen(const char *str) {
    return strlen(str) + 1;
}

void print_element(const char *key, void *data) {
	printf("(\"%s\", %s)\n", key, (char*)data);
}

void *resolve_collision(void *old_value, void *new_value) {
	return new_value;
}

unsigned your_own_hash(const char *key) {
	return (unsigned) strlen(key) + (unsigned) *key;
}

int main()
 {unsigned int key_space = 1024;
	HashMap * hm = create_hashmap(key_space);

	char * string_1 = "TI2725-C";
	char * string_2 = "Embedded";
	char * string_3 = "Software";
	const char * key_1    = "ab";
	const char * key_2    = "cd";
	const char * key_3    = "ad";
	const char * key_4    = "xy";

	// Insert ("ab" -> "TI2725-C").
	insert_data(hm, key_1, string_1, resolve_collision);
	assert(memcmp(get_data(hm, key_1), string_1, mystrlen(string_1)) == 0);

	// Insert ("cd" -> "Embedded").
	insert_data(hm, key_2, string_2, resolve_collision);
	assert(memcmp(get_data(hm, key_2), string_2, mystrlen(string_2)) == 0);

	// Insert ("ad" -> "Software").
	insert_data(hm, key_3, string_3, resolve_collision);
	assert(memcmp(get_data(hm, key_3), string_3, mystrlen(string_3)) == 0);

	// Insert ("ab" -> "Embedded").
	insert_data(hm, key_1, string_2, resolve_collision);
	assert(memcmp(get_data(hm, key_1), string_2, mystrlen(string_2)) == 0);

	// Get data for a not inserted key.
	assert(get_data(hm, key_4) == NULL);
	printf("passing non inserted ket to get_data test:  complete\n");



	assert(get_data(hm, NULL) == NULL);
	printf("passing null to get_data test:  complete\n");

	// removing the middle node
	remove_data(hm, key_2, NULL);
	assert(get_data(hm, key_2) == NULL);
	printf("removing key 2\n");
	
	//print all values	
	iterate(hm, NULL);

	//deleting hashmap
	delete_hashmap(hm, NULL);
	printf("hashmap deleted\n");

	return 0;

}
