#include <stdio.h>
#include <stdbool.h>

#define MEIRO_WIDTH 13
#define MEIRO_HEIGHT 9

#define PATH 0
#define WALL 1
#define GOAL 2
#define PASSED 3

#define MAX_NUM (MEIRO_WIDTH * MEIRO_HEIGHT)
#define STACK_SIZE MAX_NUM

typedef struct POS
{
	int	i;
	int	j;
}	POS_T;

typedef struct STACK
{
	int	tail; // End of data
	POS_T data[STACK_SIZE];
}	STACK_T;

STACK_T	stack;

static int	maze[MEIRO_HEIGHT][MEIRO_WIDTH] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,0,1,1,1,1,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// Stack initializer
void	initStack(STACK_T *stack)
{
	// Set the stack empty
	stack->tail = -1;
}

void	push(STACK_T *stack, POS_T *input)
{
	if (stack->tail >= STACK_SIZE -1)
	{
		printf("Can't push. Stack is full.\n");
		return ;
	}

	stack->data[stack->tail + 1] = *input;
	stack->tail = stack->tail + 1;
}

POS_T	*pop(STACK_T *stack)
{
	POS_T *ret;

	// If stack is empty, do nothing and end the func
	if (stack->tail == -1)
	{
		printf("Stack is empty\n");
		return NULL;
	}

	ret = &(stack->data[stack->tail]);
	stack->tail = stack->tail - 1;

	return (ret);
}

bool check(int i, int j)
{
	bool ret = true;

	// Out of maze
	if (i < 0 || i >= MEIRO_WIDTH || j < 0 || j >= MEIRO_HEIGHT)
		ret = false;

	// Wall
	if (maze[j][i] == WALL)
		ret = false;
	
	// Passed
	if (maze[j][i] == PASSED)
		ret = false;
	
		return ret;
}

bool	search(int s_i, int s_j)
{
	POS_T	pos;
	bool	ret;

	if (check(s_i, s_j))
	{
		pos.i = s_i; // Coordinate i of starting point
		pos.j = s_j; // Coordinate j of starting point

		push(&stack, &pos); // Save the coord in stack
	}

	while (true)
	{
		int i, j;

		// Get next candidate for search from stack
		POS_T *next = pop(&stack);
		
		// If the there's none, search fails
		if (next == NULL)
		{
			ret = false;
			break;
		}

		// Get the coordinate to search
		i = next->i;
		j = next->j;

		if (maze[j][i] == GOAL)
		{
			printf("GOAL!\n");
			ret = true;
			break;
		}

		// Mark where you researched
		maze[j][i] = PASSED;

		// Put valid next candidate into stack

		// Up
		if (check(i, j - 1))
		{
			pos.i = i;
			pos.j = j - 1;
			push(&stack, &pos);
		}

		// Down
		if (check(i, j + 1))
		{
			pos.i = i;
			pos.j = j + 1;
			push(&stack, &pos);
		}
		
		// Left
		if (check(i - 1, j))
		{
			pos.i = i - 1;
			pos.j = j;
			push(&stack, &pos);
		}

		// Right
		if (check(i + 1, j))
		{
			
		}


	}
}