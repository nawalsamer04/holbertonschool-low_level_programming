#ifndef DOG_H
#define DOG_H

/**
 * struct dog - basic info about a dog
 * @name: dog's name
 * @age: dog's age
 * @owner: dog's owner
 *
 * Description: defines a dog structure
 */
struct dog
{
	char *name;
	float age;
	char *owner;
};

/* New type definition for struct dog */
typedef struct dog dog_t;

/* Function prototypes */
void init_dog(struct dog *d, char *name, float age, char *owner);
void print_dog(struct dog *d);
dog_t *new_dog(char *name, float age, char *owner);

#endif /* DOG_H */

