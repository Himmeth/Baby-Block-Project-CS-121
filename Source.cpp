//#include "robot_functions.cpp"
#include <iostream>
#include <iomanip>
#include <string>

unsigned int move_left_right(unsigned int position, unsigned int movement, bool direction);
void shift_all(unsigned int position, bool direction, char slots[]);
char get_block();
void print_slots(char slots[]);
unsigned int put_block(char block, unsigned int position, char array[]);
unsigned int remove_block(unsigned int position, char array[]);
unsigned int shift_right(unsigned int position);
unsigned int shift_left(unsigned int position);
bool robot_ltoreq_slot(char robot, char in_slot);
char switch_blocks(char robot, unsigned int position, char array[]);
bool test_empty(unsigned int position, char array[]);


using namespace std;

// Function get_block
// Reads in a single character value from the keyboard 
// This is the input from the chute
// Returns: a single character in uppercase
//
// Example function call: 	block = get_block();
char get_block()
{
	char block;
	cout << "Enter one block: ";
	cin >> block;
	return toupper(block);
}

// Function print_slots
// Prints the contents of the slots array in a well formatted form.
// Input: Array of slots
// Returns: Nothing (void)
//
// Example function call: print_slots(slot_array);
void print_slots(char slots[])
{
	unsigned int j = 1;
	for (j = 1; j <= 20; j++)
	{
		cout << setw(3) << j;
	}
	cout << endl;
	for (j = 0; j < 20; j++)
	{
		cout << setw(3) << slots[j];
	}
	cout << endl;
}

// Function put_block
// This function stores a character into the character array representing the slots
//
// Inputs: 
// block - type char - The character to be inserted into a slot
// position - type unsigned int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// position - type unsigned int - the index of the slot where the block was placed
unsigned int put_block(char block, unsigned int position, char array[])
{
	bool debug = true;
	array[position] = block;
	if (debug)
		cout << "Block " << block << " inserted into slot " << position << endl;
	return position;
}

// Function remove_block
// This function removes a block from the slot array
// The slot where the block is removed is then set to a space
//
// Inputs: 
// position - type unsigned int - index of the slot where block is located
// array - type char - array of slots containing the blocks
//
// Returns:
// block - type char - the block removed from the slot
unsigned int remove_block(unsigned int position, char array[])
{
	bool debug = true;
	char block = ' ';
	block = array[position];
	array[position] = ' ';  // Reset slot to blank after block removed
	if (debug)
		cout << "Block " << block << " removed from slot " << position + 1 << endl;
	return block;
}


// Function shift_right
// This function increments the index simulating a movement of the robot 
// to the next higher slot (index) of the array
// 
// Inputs:
// position - type unsigned int - current slot position
//
// Returns:
// position - type unsigned int - The updated position which is input position + 1
//
// Example function call:  position = shift_right(position)
unsigned int shift_right(unsigned int position)
{
	bool debug = true;
	position++;
	if (debug)
		cout << "Position right shifted to " << position << endl;
	return position;
}

// Function shift_left
// This function decrements the index simulating a movement of the robot 
// to the next lower slot (index) of the array
// 
// Inputs:
// position - type unsigned int - current slot position
//
// Returns:
// position - type unsigned int - The updated position which is input position - 1
unsigned int shift_left(unsigned int position)
{
	bool debug = true;
	position--;
	if (debug)
		cout << "Position left shifted to " << position << endl;
	return position;
}

// Function robot_ltoreq_slot
// This function compares the value of the block held by the robot 
// with the value of the block in a slot 
// 
// Inputs:
// robot - type char - value of block held by robot
// in_slot - type char - value of block in the slot
//
// Returns:
// true or false
// TRUE if block held by robot is LESS than or equal to the block in slot
// FALSE if block held by robot is GREATER than block in slot
bool robot_ltoreq_slot(char robot, char in_slot)
{
	bool debug = true;
	if (debug)
		cout << endl << "Comparing robot block " << robot << " with block in slot " << in_slot << endl;
	if (robot <= in_slot)
	{
		if (debug)
			cout << "Returning true. Robot block LESS than or EQUAL to block in slot. " << endl;
		return true;
	}
	else
	{
		if (debug)
			cout << "Returning false. Robot block GREATER than block in slot. " << endl;
		return false;
	}
}
// Function switch_blocks
// This function switches the block held by the robot with a block in a slot. 
// After the switch the robot is holding the block removed from the slot.
// 
// Inputs: 
// robot - type char - The block to be inserted into a slot
// position - type unsigned int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// robot - type char. The value of the block removed from the slot.
char switch_blocks(char robot, unsigned int position, char array[])
{
	char temp_hold;
	bool debug = true;
	if (debug)
		cout << "Switching blocks " << robot << " with " << array[position] << endl;
	temp_hold = robot;
	robot = array[position];
	array[position] = temp_hold;
	return robot;
}

// Function test_empty
// This function tests the array to determine if a slot is empty (NULL) 
// or if the slot contains a blank. The slot array must be intialized to 
// all NULL or all blanks (spaces) before any blocks are added.
// 
// Inputs:
// position - type unsigned int - index of slot to be tested
//
// Returns:
// true or false as value o function
// TRUE if slot is empty
// FALSE if the slot contains a block
bool test_empty(unsigned int position, char array[])
{
	char blank = ' '; // Blank space
	bool debug = true;
	if (array[position] == NULL || array[position] == blank)
	{
		if (debug)
			cout << "Slot " << position << " empty. " << endl;
		return true;
	}
	else
	{
		if (debug)
			cout << "Slot " << position << " contains a block " << endl;
		return false;
	}

}
//#endif // !ROBO_FUNC

unsigned int move_left_right(unsigned int position, unsigned int movement, bool direction){
	if (direction) {
		for (unsigned int i = 0; i < movement; i++) {
			position = shift_left(position);
		}
		return position;
	}
	else{	
		for (unsigned int i = 0; i < movement; i++) {
			position = shift_right(position);
		}
		return position;
	}
}

void shift_all(unsigned int position, bool direction, char slots[]) {
	char robo_arm;
	if (direction) {
		while (position > 1 && !test_empty(position, slots)) {
			robo_arm = remove_block(position, slots);
			position = shift_right(position);
			put_block(robo_arm, position, slots);
			position -= 2;
		}
	}
	else {
		while (position < 19 && !test_empty(position, slots)) {
			robo_arm = remove_block(position, slots);
			position = shift_left(position);
			put_block(robo_arm, position, slots);
			position += 2;
		}
	}
}



int main() {
	char robo_arm;
	char slots[20] = { 0 };
	bool direction;
	unsigned int position, blocks_left = 20;

	while (blocks_left != 0) {
		robo_arm = get_block();
		position = 0;
		if (blocks_left == 20) {
			put_block(robo_arm, 9, slots);
			blocks_left--;
		}
		else if (blocks_left == 19) {
			direction = robot_ltoreq_slot(robo_arm, slots[9]);
			if (direction) { //if new block less than one in slot[9] shift to begginning of array and place it there
				position = move_left_right(9, 9, !direction);
				put_block(robo_arm, position, slots);

				robo_arm = remove_block(9, slots);
				position = move_left_right(9, 10, direction); //place block at slot[9] in last slot
				put_block(robo_arm, position, slots);
				blocks_left--;
			}
			else { //if new block is greater than the one in slot[9] shift it to the end of the array and place it there
				position = move_left_right(9, 10, direction);
				put_block(robo_arm, position, slots);

				robo_arm = remove_block(9, slots);
				position = move_left_right(9, 9, !direction); //place block at slot[9] in first slot
				put_block(robo_arm, position, slots);
				blocks_left--;
			}
		}
		else { //actual sorting
			direction = robot_ltoreq_slot(robo_arm, slots[position]);

			if (direction) { //if held block is less than slot
				robo_arm = switch_blocks(robo_arm, position, slots);
				print_slots(slots);
				position++;
			}
			else {
				position++;
			}

			unsigned int empty_blocks = 0;

			while (test_empty(position, slots)) { //count number of empty blocks to traverse
				empty_blocks++;
				position++;
			}

			cout << empty_blocks << endl;

			unsigned int starting_shift_position = 0;
			starting_shift_position = position; //if blocks have to be shifted, it will start at this point

			direction = robot_ltoreq_slot(robo_arm, slots[position]);
			if (direction) { //if held block less than slot
				position--;
				put_block(robo_arm, position, slots);
				print_slots(slots);
				blocks_left--;
			}
			else if (!direction){//held block is greater than slot
				bool direction_change = false;

				while (position < 20 && !direction_change) {
					position++;
					direction_change = robot_ltoreq_slot(robo_arm, slots[position]);
				}
				cout << position << endl;
				shift_all(starting_shift_position, direction, slots);
				put_block(robo_arm, --position, slots);
				print_slots(slots);
				blocks_left--;				
			}
		}
	}

	print_slots(slots);
}