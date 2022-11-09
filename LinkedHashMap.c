#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MapNode {
    char key[50];
    int value;
    struct MapNode *next;
}MapNode;

typedef struct LinkedHashMap {
    MapNode* head;
    MapNode* tail;
    int size;
}LinkedHashMap;

LinkedHashMap* createLinkedHashMap();
void put(LinkedHashMap *map, char *key, int value);
void printMap(LinkedHashMap *map);
int get(LinkedHashMap *map, char *key);
int containsKey(LinkedHashMap *map, char *key);
int containsValue(LinkedHashMap *map, int value);
int isEmpty(LinkedHashMap *map);
void removeKey(LinkedHashMap *map, char* key);
void putAll(LinkedHashMap *map, LinkedHashMap *allMap);
int mapSize(LinkedHashMap *map);
void clearMap(LinkedHashMap *map);
int* values(LinkedHashMap *map);
char** keys(LinkedHashMap *map);
void replace(LinkedHashMap *map, char* key, int value);
int getOrDefault(LinkedHashMap *map, char* key, int defaultValue);

int main() {
    LinkedHashMap *map = createLinkedHashMap();
    put(map, "shirts", 14);
    put(map, "shoes", 1324);
    put(map, "pants", 404);
    put(map, "jackets", 58);
    replace(map, "jackets",50);
    removeKey(map, "shoes");
    printMap(map);
    printf("[%d]\n",getOrDefault(map, "glasses", 0));
    printf("shoes %s\n", containsKey(map,"shoes") ? "are in the map" : "are not in the map");
    printf("%s\n", containsValue(map, 50) ? "Value 50 is in the map" : "Value 50 is not in the map");
    int *valuesArray = values(map);
    char **keysArray = keys(map);
    for (int i = 0; i < mapSize(map); i++) {
        printf("-%s-\n", keysArray[i]);
    }
    
    return 0;
}


/**
* This method creates a new empty LinkedHashMap.
* @return a new empty LinkedHashMap
*/
LinkedHashMap* createLinkedHashMap() {
    LinkedHashMap *map = (LinkedHashMap *)malloc(sizeof(LinkedHashMap));
    map->head = NULL;
    map->tail = NULL;
    map->size = 0;
    return map;
}


/**
* Associates the specified value with the specified key in this map.
* If the map previously contained a mapping for the key, the old value will be protected.
* Use replace method instead of this method if you need to change the value of key.
* @param    map      LinkedHashMap object that the key and value will be added.  
* @param    key      key with which the specified value is to be associated
* @param    value    value to be associated with the specified key
*/
void put(LinkedHashMap *map, char *key, int value) {
    if (containsKey(map, key)) {
        return;
    }
    MapNode *node = (MapNode *)malloc(sizeof(MapNode));
    strcpy(node->key, key);
    node->value = value;
    node->next = NULL;
    if (map->head == NULL) {
        map->head = node;
        map->tail = node;
        (map->size)++;
        return;
    }
    map->tail->next = node;
    map->tail = node;
    (map->size)++;
}


/**
* Prints the map with the keys and values.
* @param    map     LinkedHashMap object that will get printed.
*/
void printMap(LinkedHashMap *map) {
    MapNode* temp = map->head;
    while (temp != NULL) {
        printf("Key: %s - Value: %d\n",temp->key, temp->value);
        temp = temp->next;
    }
}


/**
* Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
* @param    map     LinkedHashMap object to get the value from
* @param    key     key that where to get the value from
* @return   the value to which the specified key is mapped, or -1 if this map contains no mapping for the key
*/
int get(LinkedHashMap *map, char *key) {
    MapNode* temp = map->head;
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        } 
        temp = temp->next;
    }
    return -1;
}


/**
* Returns 1 if this map contains a mapping for the specified key.
* @param    map     LinkedHashMap object that will be checked
* @param    key     key that will be checked if exists
* @return   1 if this map contains a mapping for the specified key else 0.
*/
int containsKey(LinkedHashMap *map, char *key) {
    MapNode* temp = map->head;
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return 1;
        } 
        temp = temp->next;
    }
    return 0;
}


/**
* Returns 1 if this map contains a mapping for the specified value.
* @param    map     LinkedHashMap object that will be checked 
* @param    value   value that will be checked if exists
* @return   1 if this map contains a mapping for the specified value else 0.
*/
int containsValue(LinkedHashMap *map, int value) {
    MapNode* temp = map->head;
    while (temp != NULL) {
        if (temp->value == value) {
            return 1;
        } 
        temp = temp->next;
    }
    return 0;
}


/**
* Returns 1 if this map is empty else 0.
* @param    map     LinkedHashMap object that will be checked if empty
* @return   1 if this map is empty else 0.
*/
int isEmpty(LinkedHashMap *map) {
    return (map->size == 0);
}


/**
* Removes the key, value pair from the map.
* @param    map     LinkedHashMap object that key and value will be deleted from
* @param    key     key to remove the pair from the map
*/
void removeKey(LinkedHashMap *map, char* key) {
    if(!containsKey(map,key)) {
        return;
    }
    MapNode* temp = map->head;
    MapNode* prev = map->head;
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            if (temp == map->head) {
                map->head = temp->next;
            }
            if (temp == map->tail) {
                map->tail = prev;
            }
            prev->next = temp->next;
            free(temp);
        }
        prev = temp; 
        temp = temp->next;  
    }
    (map->size)--;
}


/**
* Associates the specified value with the specified key in this map for every pair of second map.
* If the map previously contained a mapping for the key, the old value will be protected.
* @param    map     LinkedHashMap object that will be the combination with second map
* @param    allMap  LinkedHashMap object that pairs will come from
* @param    key     key to remove the pair from the map
*/
void putAll(LinkedHashMap *map, LinkedHashMap *allMap) {
    MapNode *temp = allMap->head;
    for (int i = 0; i < allMap->size; i++) {
        put(map, temp->key, temp->value);
        temp = temp->next;
    }
}


/**
* Returns the map size
* @param    map     LinkedHashMap object to get the map size
* @return   size of the map
*/
int mapSize(LinkedHashMap *map) {
    return map->size;
}


/**
* Deletes all the pairs from the map
* @param    map     LinkedHashMap object to clear it
*/
void clearMap(LinkedHashMap *map) {
    MapNode* temp = map->head;
    while (temp != NULL) {
        free(temp);
        temp = temp->next;
    }
    map->head = NULL;
    map->tail = NULL;
    map->size = 0;
}


/**
* Returns an integer array of values in map
* @param    map     LinkedHashMap object to get values from
* @return   an integer array of values in map
*/
int* values(LinkedHashMap *map) {
    int* valuesArray = malloc(map->size * sizeof(int));
    MapNode* temp = map->head;
    for (int i = 0; i < map->size; i++) {
        valuesArray[i] = temp->value;
        temp = temp->next;
    }
    return valuesArray;
}


/**
* Returns a string array of values in map
* @param    map     LinkedHashMap object to get keys from
* @return   a string array of keys in map
*/
char** keys(LinkedHashMap *map) {
    char **keysArray;
    keysArray = malloc(map->size * sizeof(char*));
    MapNode* temp = map->head;
    for (int i = 0; i < map->size; i++) {
        keysArray[i] = malloc((strlen(temp->key)+1) * sizeof(char)); 
        strcpy(keysArray[i], temp->key);
        temp = temp->next;
    }
    return keysArray;
}


/**
* Replaces the value of key.
* @param    map     LinkedHashMap object for replacing the value
* @param    key     key to change the value
* @param    value   value to be replaced with the specified key
*/
void replace(LinkedHashMap *map, char* key, int value) {
    MapNode* temp = map->head;
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            temp->value = value;
        } 
        temp = temp->next;
    }
}


/**
* Returns the value to which the specified key is mapped, or a default value if this map contains no mapping for the key.
* @param    map             LinkedHashMap object to get the value from
* @param    key             key that where to get the value from
* @param    defaultValue    default value to get if this map contains no mapping for the key
* @return   the value to which the specified key is mapped, or a default value if this map contains no mapping for the key
*/
int getOrDefault(LinkedHashMap *map, char* key, int defaultValue) {
    MapNode* temp = map->head;
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        } 
        temp = temp->next;
    }
    return defaultValue;
}