#ifndef DOG_H
#define DOG_H

/**
 * struct dog - basic info about a dog
 * @name: dog's name
 * @age: dog's age
 * @owner: dog's owner
 *
 * Description: defines a structure representing a dog.
 */
struct dog
{
	char *name;
	float age;
	char *owner;
};
/* Function prototype for init_dog */
void init_dog(struct dog *d, char *name, float age, char *owner);
#endif /* DOG_H */

