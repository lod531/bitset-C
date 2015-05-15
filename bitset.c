#include <stdio.h>
#include <stdlib.h>

#define BITMAP_SIZE 256

struct bitset
{
	unsigned char * array;
	int size;
	int numberOfBytes;
};

void bitset_print(struct bitset * this)
{
	int i;
	for(i = 0; i < this->numberOfBytes; i++)
	{
		unsigned char currentChar = this->array[i];
		int j;
		for(j = 0; j < 8; j++)
		{
			if(currentChar & (128 >> j))
			{
				printf("%c\n", i*8 + j);
			}
		}
	}
}

// create a new, empty bit vector set of 'size' items
struct bitset * bitset_new(int size)
{
	struct bitset * result = malloc(sizeof(struct bitset));
	result->numberOfBytes = size/8 + ((size%8 == 0)? 0 : 1);
	result->array = malloc(sizeof(unsigned char) * result->numberOfBytes);
	result->size = size;
	int i;
	for(i = 0; i < result->numberOfBytes; i++)
	{
		result->array[i] = 0;
	}
	return result;
}

// check to see if an item is in the set
// returns 1 if in the set, 0 if not, and -1 if 'item' is out of bounds
int bitset_lookup(struct bitset * this, int item)
{
	unsigned char target = this->array[item/8];
	target = (target << item % 8) & 128;
	return target;
}

// add an item, with number 'item' to the set
// (returns 0 if item is out of bounds, 1 otherwise)
// has no effect if the item is already in the set
int bitset_add(struct bitset * this, int item)
{
	unsigned char target = this->array[item/8];
	target = target | (128 >> item % 8);
	this->array[item/8] = target;
	return 1;
}

// remove an item with number 'item' from the set
// (returns 0 if item is out of bounds, 1 otherwise)
int bitset_remove(struct bitset * this, int item)
{
	unsigned char target = this->array[item/8];
	target = target & ~(128 >> item % 8);
	this->array[item/8] = target;
	return 1;
}

// place the union of src1 and src2 into dest
void bitset_union(struct bitset * dest, struct bitset * src1,
		  struct bitset * src2);
//simple for loop + bitwise OR

// place the intersection of src1 and src2 into dest
void bitset_intersect(struct bitset * dest, struct bitset * src1,
                  struct bitset * src2);
//simple for loop * bitwise AND

int main()
{
	struct bitset * test = bitset_new(BITMAP_SIZE);
	bitset_add(test, 'a');
	bitset_add(test, 'b');
	bitset_remove(test, 'a');
	bitset_remove(test, 'b');
	bitset_add(test, 'a');
	bitset_add(test, 'c');
	bitset_print(test);
	return 0;
}