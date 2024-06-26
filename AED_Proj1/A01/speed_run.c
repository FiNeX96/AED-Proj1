//
// AED, August 2022 (Tomás Oliveira e Silva)
//
// First practical assignement (speed run)
//
// Compile using either
//   cc -Wall -O2 -D_use_zlib_=0 solution_speed_run.c -lm
// or
//   cc -Wall -O2 -D_use_zlib_=1 solution_speed_run.c -lm -lz
//
// Place your student numbers and names here
//   N.Mec. 108969 Name: Rodrigo Aguiar
//	 N.Mec. 107186 Name: Vítor Santos


//
// static configuration
//

#define _max_road_size_    800 // the maximum problem size
#define _min_road_speed_   2  // must not be smaller than 1, shouldnot be smaller than 2
#define _max_road_speed_   9  // must not be larger than 9 (only because of the PDF figure)

#define _INCLUDE_SOL_1_    0 // Flag for testing other faster solutions
#define _INCLUDE_SOL_1_IMPROVED_ 1 // Flag for testing other faster solutions
#define _INCLUDE_SOL_2_    1  // Flag for testing other faster solutions
#define _INCLUDE_SOL_3_    1  // Flag for testing other faster solutions
#define _INCLUDE_SOL_4_    1  // Flag for testing other faster solutions
#define _INCLUDE_SOL_5_    1  // Flag for testing other faster solutions
#define true 1
#define false 0

#define _PRINT_FOR_MATLAB_    1 // Flag for printing data in a format better suited for MATLAB
#define min(a,b,c) (a<b?(a<c?a:c):(b<c?b:c)) // min function that is to be used for solution 4, to find the minimum of 3 numbers


//
// include files --- as this is a small project, we include the PDF generation code directly from make_custom_pdf.c
//

#include <math.h>
#include <stdio.h>
#include "../P02/elapsed_time.h"
#include "make_custom_pdf.c"

//Added
#include <assert.h>

//
// road stuff
//

static int max_road_speed[1 + _max_road_size_]; // positions 0.._max_road_size_

static void init_road_speeds(void)
{
  double speed;
  int i;

  for(i = 0;i <= _max_road_size_;i++)
  {
    speed = (double)_max_road_speed_ * (0.55 + 0.30 * sin(0.11 * (double)i) + 0.10 * sin(0.17 * (double)i + 1.0) + 0.15 * sin(0.19 * (double)i));
    max_road_speed[i] = (int)floor(0.5 + speed) + (int)((unsigned int)random() % 3u) - 1;
    if(max_road_speed[i] < _min_road_speed_)
      max_road_speed[i] = _min_road_speed_;
    if(max_road_speed[i] > _max_road_speed_)
      max_road_speed[i] = _max_road_speed_;
  }
}


//
// description of a solution
//

typedef struct
{
  int n_moves;                         // the number of moves (the number of positions is one more than the number of moves)
  int positions[1 + _max_road_size_];  // the positions (the first one must be zero)
}
solution_t;


//
// the (very inefficient) recursive solution given to the students
//

static solution_t solution_1,solution_1_best;
static double solution_1_elapsed_time; // time it took to solve the problem
static unsigned long solution_1_count; // effort dispended solving the problem

static void solution_1_recursion(int move_number,int position,int speed,int final_position)
{
  int i,new_speed;

  // record move
  solution_1_count++;
  solution_1.positions[move_number] = position;
  // is it a solution ?
  if(position == final_position && speed == 1)
  {
    // is it a better solution?
    if(move_number < solution_1_best.n_moves)
    {
      solution_1_best = solution_1;
      solution_1_best.n_moves = move_number;
    }
    return;
  }
  // ITS SET TO THE IMPROVED VERSION FOR NOW JUST FOR THE TABLE TO BE BEAUTIFUL =)
   if(solution_1_best.positions[move_number] > solution_1.positions[move_number]) return;
  if(solution_1_best.n_moves <= move_number) return;
  // no, try all legal speeds
  for(new_speed = speed -1;new_speed <= speed +1;new_speed++)
    if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
    {
      for(i = 0;i <= new_speed && new_speed <= max_road_speed[position + i];i++)
        ;
      if(i > new_speed)
        solution_1_recursion(move_number + 1,position + new_speed,new_speed,final_position);
    }
}

static void solve_1(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_1: bad final_position\n");
    exit(1);
  }
  solution_1_elapsed_time = cpu_time();
  solution_1_count = 0ul;
  solution_1_best.n_moves = final_position + 100;
  solution_1_recursion(0,0,0,final_position);
  solution_1_elapsed_time = cpu_time() - solution_1_elapsed_time;
}

//
// SOLUTION 1 IMPROVED
// 
//

static void solution_1_improved(int move_number,int position,int speed,int final_position)
{
  int i,new_speed;

  // record move
  solution_1_count++;
  solution_1.positions[move_number] = position;
  // is it a solution ?
  if(position == final_position && speed == 1)
  {
    // is it a better solution?
    if(move_number < solution_1_best.n_moves)
    {
      solution_1_best = solution_1;
      solution_1_best.n_moves = move_number;
    }
    return;
  }
  if(solution_1_best.positions[move_number] > solution_1.positions[move_number]) return; // IMPROVEMENT
  if(solution_1_best.n_moves <= move_number) return;                                     // IMPROVEMENT
  // no, try all legal speeds
  for(new_speed = speed +1;new_speed >= speed -1;new_speed--)
    if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
    {
      for(i = 0;i <= new_speed && new_speed <= max_road_speed[position + i];i++)
        ;
      if(i > new_speed)
        solution_1_improved(move_number + 1,position + new_speed,new_speed,final_position);
    }
}

static void solve_1_improved(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_1_improved: bad final_position\n");
    exit(1);
  }
  solution_1_elapsed_time = cpu_time();
  solution_1_count = 0ul;
  solution_1_best.n_moves = final_position + 100;
  solution_1_improved(0,0,0,final_position);
  solution_1_elapsed_time = cpu_time() - solution_1_elapsed_time;
}

//
// SOLUTION 2 WITH RECURSION
//

static solution_t solution_2,solution_2_best;
static double solution_2_elapsed_time; // time it took to solve the problem
static unsigned long solution_2_count; // effort dispended solving the problem

// Static result array that stores the number of moves of an instance upon its traversal of a particular
// position at a particular speed.

// This array shall be used to avoid recomputations and bad computations.

// More explained in the report.

static int r[_max_road_size_+1][_max_road_speed_+1]; // For all possible positions and speeds

int isPossibleSolution(int new_position,int new_speed,int final_position){
  // Check if the solution is possible
  if ((final_position - new_position) >= (new_speed*(new_speed+1))/2){ // if the distance to the final position is greater than the sum
   // of the first 1:new_speed natural numbers, then the solution is possible
    return true;
    }
  else{
    return false;
}
}


static void solution_2_recursion(int move_number,int position,int speed,int final_position)
{
  //if(final_position == 22 )
    //  printf("\n I ENTERED THE FUNCTION WITH SPEED %i AND POSITION %i \n",speed,position);  // THE FUNCTION IS NOT COMPUTING SOME VALUES RIGHT!!
  
  int i,new_speed;

  // record move
  solution_2_count++;
  solution_2.positions[move_number] = position;
  // is it a solution ?
  if(position == final_position && speed == 1)
  {
    // is it a better solution?
    if(move_number < solution_2_best.n_moves)
    {
      solution_2_best = solution_2;
      solution_2_best.n_moves = move_number;
    }
    return;
  }
  
  r[position][speed] = move_number;
  
  // Flag
  if(solution_2_best.positions[move_number] > solution_2.positions[move_number]) return; // IMPROVEMENT
  if(solution_2_best.n_moves <= move_number) return;
  for(new_speed = speed+1 ;new_speed >= speed-1;new_speed--)
    if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
    {
      for(i = 0;i <= new_speed && new_speed <= max_road_speed[position + i];i++)
        ;
      if(i > new_speed){
         if (r[position+new_speed][new_speed] == 0 ){
			// There has never been a move_number calculated for the speed and position associated with next move? Then calculate it
            solution_2_recursion(move_number + 1,position + new_speed,new_speed,final_position);
         }
         else{
			// Will the function generate a better move_number for [position+new_speed][new_speed] ? Then calculate it
             if ( ! isPossibleSolution(position+new_speed,new_speed,final_position))
              continue;
             if (move_number+1 < r[position+new_speed][new_speed] )
			        {           
                solution_2_recursion(move_number + 1,position + new_speed,new_speed,final_position);}
             else
              {
		            // The function wont generate a better move_number, so dont call it
                break;
              }
         }
       }
    }
}

    


static void solve_2(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_2: bad final_position\n");
    exit(1);
  }
  solution_2_elapsed_time = cpu_time();
  solution_2_count = 0ul;
  solution_2_best.n_moves = final_position + 100;
  solution_2_recursion(0,0,0,final_position);
  solution_2_elapsed_time = cpu_time() - solution_2_elapsed_time;
}

//
// SOLUTION 3 ITERATIVE APPROACH ----------------------------------------
//

// ------ Extremely basic linked list implementation

typedef struct node_t
{
    int pos;
    int speed;
    int *positions;
    struct node_t* prev;
    struct node_t* next;
}node_t;

void insert(struct node_t *p, int pos, int speed, int *positions, int move_number)
{
    assert(p != NULL);
    node_t *p_new = (node_t *)malloc(sizeof(node_t));
    p_new->pos = pos;
    p_new->speed = speed;
    p_new->next = NULL;
    p_new->prev = NULL;

    int* new_pos = (int *)malloc( (size_t)(move_number + 1) * sizeof(int) );

    p_new->positions = new_pos;

    for(int i = 0; i < move_number; i++)
      new_pos[i] = positions[i];

    new_pos[move_number] = pos; 

    p_new->next = p->next;
    if(p->next != NULL)
      p->next->prev = p_new;
    p_new->prev = p;
    p->next = p_new;
}

// Dangerous on head pointers. Save head->next to head before deleting it.

void delete_node_t(node_t *p)
{
    assert(p != NULL);
    if(p->next != NULL)
      p->next->prev = p->prev;
    if(p->prev == NULL)
    {
        free(p->positions);
        free(p);
        return;
    }
    p->prev->next = p->next;
    free(p->positions);
    free(p);
}

// ------ End of linked list implementation

static solution_t solution_3_best;
static unsigned long solution_3_count;
static double solution_3_elapsed_time;

// Uses results array

static void solution_3(int final_position)
{
  node_t* head = (node_t*)malloc(sizeof(node_t));

  int move_number = 0;

  head->pos = 0;
  head->speed = 0;
  head->next = NULL;
  head->prev = NULL;
  head->positions = (int *)malloc( (size_t)(move_number + 1) * sizeof(int) );
  head->positions[0] = 0;
  node_t* n = head; 
  node_t* nn = n->next; // Save a copy of n->next since n's next node will be changed


  while(1)
  {
    // is it a solution ?
    if(n->pos == final_position && n->speed == 1)
      break;
    
    int new_speed, i;

    // Compare position stored in this node with maximum position for all nodes of the same move_number
    // Try all speeds
    for(new_speed = n->speed - 1;new_speed <= n->speed + 1;new_speed++)
      if(new_speed >= 1 && new_speed <= _max_road_speed_ && n->pos + new_speed <= final_position)
      {
        for(i = 0;i <= new_speed && new_speed <= max_road_speed[n->pos + i];i++)
          ;
        if(i > new_speed && (n->pos == 0 || !r[n->pos+new_speed][new_speed] ) )
        {            
          insert(n,n->pos + new_speed, new_speed, n->positions, move_number+1);
          r[n->pos + new_speed][new_speed] = 1; // Results array only needs boolean values
          solution_3_count++;
        }
        else
          break;
      }
    if(n->prev == NULL)
    {
      head = n->next;
    }
    delete_node_t(n);
    n = NULL;
    if(nn == NULL)
    {
      n = head;
      move_number++;
    }
    else
      n = nn;
    nn = n->next;
  }
  solution_3_best.n_moves = move_number;
  for(int i = 0; i <= move_number; i++)
    solution_3_best.positions[i] = n->positions[i];
}


static void solve_3(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_3: bad final_position\n");
    exit(1);
  }
  solution_3_count = 0;
  solution_3_elapsed_time = cpu_time();
  solution_3_best.n_moves = -1;
  solution_3(final_position);
  solution_3_elapsed_time = cpu_time() - solution_3_elapsed_time;
}

// 
/// Solution 4 with Dynamic Programming
//


static solution_t solution_4,solution_4_best;
static double solution_4_elapsed_time; // time it took to solve the problem
static unsigned long solution_4_count; // effort dispended solving the problem

static int solution_4_DP(int position,int speed,int final_position)
{
  int new_speed,i;

  solution_4_count++;

  if(position == final_position && speed == 1)
    return 0;
  
  int prev_min = -1; // Se um valor mínimo for -1 significa que é inválido e não deve ser comparado
  int min = -1;

  for(new_speed = speed-1 ; new_speed <= speed+1 ; new_speed++)
    if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
    {
      for(i = 0; i <= new_speed && new_speed <= max_road_speed[position + i]; i++)
        ;
      if(i > new_speed)
      {
        if(r[position + new_speed][new_speed] == 0)
          min = solution_4_DP(position + new_speed, new_speed, final_position);
        else
          min = r[position + new_speed][new_speed];
      }
      else
        break;
      if(prev_min != -1)
      {
        if(min != -1)
        {
          if(prev_min > min)
            prev_min = min;
        }
      }
      else
        prev_min = min;
    }
  if(prev_min != -1)
  {
    prev_min++;
  }
  r[position][speed] = prev_min;
  return r[position][speed];
}
  

static void solve_4(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_4: bad final_position\n");
    exit(1);
  }
  solution_4_elapsed_time = cpu_time();
  solution_4_count = 0ul;
  solution_4_best.n_moves = final_position + 100;
  solution_4_best.n_moves = solution_4_DP(0, 0, final_position);
  solution_4_elapsed_time = cpu_time() - solution_4_elapsed_time;
}




//
// Solution 5 - Max Speed Backtracking
//

// Changed version of isPossibleSolution from solution 2 for this solution

int slow_down_sol_5(int position,int speed,int final_position){
  return (final_position - position) - ((speed - 1)*(speed))/2;
}

static solution_t solution_5,solution_5_best;
static double solution_5_elapsed_time; // time it took to solve the problem
static unsigned long solution_5_count; // effort dispended solving the problem

static int solution_5_recursion(int move_number,int position,int speed,int final_position)
{
  int i,new_speed, sig;

  // record move
  solution_5_count++;
  solution_5.positions[move_number] = position;

  //printf("-(P: %d, S: %d, M: %d, F: %d)-",position , speed, move_number, final_position);

  // is it a solution ?
  if(position == final_position && speed == 1)
  {
      solution_5_best = solution_5;
      solution_5_best.n_moves = move_number;
    return 1;
  }
  
  sig = -1;
  int slow_down = slow_down_sol_5(position, speed, final_position);

  // Doesn't need to slow down yet
  if(slow_down > 1)
  {
    //printf("U");
    // try all legal speeds
    for(new_speed = speed + 1;new_speed >= speed - 1;new_speed--)
      if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
      {
        for(i = 0;i <= new_speed && new_speed <= max_road_speed[position + i];i++)
          ;
        if(i > new_speed) // valid speed
        {
          if(r[new_speed + position][new_speed] == 0)
            sig = solution_5_recursion(move_number + 1,position + new_speed,new_speed,final_position);
          else
            sig = r[new_speed + position][new_speed];
          if(sig == 1)
            break; // Succesful move, signal caller with sig = 1; 
          // else, move was invalid, try next lowest speed
        }
      }
  }
  // slow down from now on
  else if(slow_down == 0)
  {
    //printf("D");
    new_speed = speed - 1;
    if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
    {
      for(i = 0;i <= new_speed && new_speed <= max_road_speed[position + i];i++)
        ;
      if(i > new_speed)
      { // if the next slowed down speed is valid, slow down again
          if(r[new_speed + position][new_speed] == 0)
            sig = solution_5_recursion(move_number + 1,position + new_speed,new_speed,final_position);
          else
            sig = r[new_speed + position][new_speed];
        // If this move is invalid, the caller will be informed with sig = -1;
      }
        // else , next slowed down speed is invalid, backtrack with sig = -1.
    }
  }
  // else, can't slow down, therefore, it cannot be a solution.
  r[position][speed] = sig;
  return sig;
}

static void solve_5(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_1: bad final_position\n");
    exit(1);
  }
  solution_5_elapsed_time = cpu_time();
  solution_5_count = 0ul;
  solution_5_best.n_moves = final_position + 100;
  //printf("\n");
  solution_5_recursion(0,0,0,final_position);
  solution_5_elapsed_time = cpu_time() - solution_5_elapsed_time;
}







//
// example of the slides
//

static void example(void)
{
  int i,final_position;

  srandom(0xAED2022);
  init_road_speeds();
  final_position = 30;
  solve_1(final_position);
  make_custom_pdf_file("example.pdf",final_position,&max_road_speed[0],solution_1_best.n_moves,&solution_1_best.positions[0],solution_1_elapsed_time,solution_1_count,"Plain recursion");
  printf("mad road speeds:");
  for(i = 0;i <= final_position;i++)
  printf(" %d",max_road_speed[i]);
  printf("\n");
  printf("positions:");
  for(i = 0;i <= solution_1_best.n_moves;i++)
    printf(" %d",solution_1_best.positions[i]);
  printf("\n");
}


//
// main program
//

int main(int argc,char *argv[argc + 1])
{
# define _time_limit_  3600.0
  int n_mec,final_position,print_this_one;
  char file_name[64];

  // generate the example data
  if(argc == 2 && argv[1][0] == '-' && argv[1][1] == 'e' && argv[1][2] == 'x')
  {
    example();
    return 0;
  }
  // initialization
  n_mec = (argc < 2) ? 0xAED2022 : atoi(argv[1]);
  srandom((unsigned int)n_mec);
  init_road_speeds();
  // run all solution methods for all interesting sizes of the problem
  final_position = 1;
  solution_1_elapsed_time = 0.0;

#if !_PRINT_FOR_MATLAB_
  printf("    + --- ---------------- --------- + --- ---------------- --------- + --- ---------------- --------- + --- ---------------- --------- +\n");
  printf("    |                plain recursion |       Solution 1 improved      |             Solution 2         |           Solution 3 - DLL     |\n");
  printf("    + --- ---------------- --------- + --- ---------------- --------- + --- ---------------- --------- + --- ---------------- --------- +\n");
  printf("  n | sol            count  cpu time | sol            count  cpu time | sol            count  cpu time | sol            count  cpu time |\n");
  printf("    + --- ---------------- --------- + --- ---------------- --------- + --- ---------------- --------- + --- ---------------- --------- +\n");
#endif

  while(final_position <= _max_road_size_/* && final_position <= 20*/)
  {
    print_this_one = (final_position == 10 || final_position == 22 || final_position == 50 || final_position == 100 || final_position == 200 || final_position == 400 || final_position == 800) ? 1 : 0;

#if !_PRINT_FOR_MATLAB_
    printf("%3d |",final_position);
#else
    printf("%3d ", final_position);
#endif

    // first solution method (very bad)
#if _INCLUDE_SOL_1_
    if(solution_1_elapsed_time < _time_limit_)
    {
      solve_1(final_position);
      if(print_this_one != 0)
      {
        sprintf(file_name,"%03d_1.pdf",final_position);
        make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_1_best.n_moves,&solution_1_best.positions[0],solution_1_elapsed_time,solution_1_count,"Plain recursion");
      }
#if !_PRINT_FOR_MATLAB_
      printf(" %3d %16lu %9.3e |",solution_1_best.n_moves,solution_1_count,solution_1_elapsed_time);
#else
      printf(" %3d %16lu %9.3e ",solution_1_best.n_moves,solution_1_count,solution_1_elapsed_time);
#endif
    }

    else
    {
      solution_1_best.n_moves = -1;
#if !_PRINT_FOR_MATLAB_
      printf("                                |");
#endif
    }
#endif
    // first solution method (improved)
    #if _INCLUDE_SOL_1_IMPROVED_
    if(solution_1_elapsed_time < _time_limit_)
    {
      solve_1_improved(final_position);
      if(print_this_one != 0)
      {
        sprintf(file_name,"%03d_1_improved.pdf",final_position);
        make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_1_best.n_moves,&solution_1_best.positions[0],solution_1_elapsed_time,solution_1_count,"Solution 1 improved");
      }
#if !_PRINT_FOR_MATLAB_
      printf(" %3d %16lu %9.3e |",solution_1_best.n_moves,solution_1_count,solution_1_elapsed_time);
#else
      printf(" %3d %16lu %9.3e ",solution_1_best.n_moves,solution_1_count,solution_1_elapsed_time);
#endif
    }

    else
    {
      solution_1_best.n_moves = -1;
#if !_PRINT_FOR_MATLAB_
      printf("                                |");
#endif
    }
#endif

    // second solution method (less bad)
    // Clear results array
#if _INCLUDE_SOL_2_
    for(int p = 0; p <= _max_road_size_ ;p++)
      for(int z = 0; z <= _max_road_speed_; z++)
        r[p][z] = 0;
    
    if(solution_2_elapsed_time < _time_limit_)
    {
      solve_2(final_position);
      if(print_this_one != 0)
      {
        sprintf(file_name,"%03d_2.pdf",final_position);
        make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_2_best.n_moves,&solution_2_best.positions[0],solution_2_elapsed_time,solution_2_count,"Sol. 2");
      }
#if !_PRINT_FOR_MATLAB_
      printf(" %3d %16lu %9.3e |",solution_2_best.n_moves,solution_2_count,solution_2_elapsed_time);
#else
      printf( "%3d %16lu %9.3e ",solution_2_best.n_moves,solution_2_count,solution_2_elapsed_time);
#endif
    }
    else
    {
      solution_2_best.n_moves = -1;
#if !_PRINT_FOR_MATLAB_
      printf("                                |");
#endif
    }
#endif

    // third solution method (less bad)
    // ...

    // Clear results array
#if _INCLUDE_SOL_3_
    for(int p = 0; p <= _max_road_size_ ;p++)
      for(int z = 0; z <= _max_road_speed_; z++)
        r[p][z] = 0;
    
    if(solution_3_elapsed_time < _time_limit_)
    {
      solve_3(final_position);
      if(print_this_one != 0)
      {
        sprintf(file_name,"%03d_3.pdf",final_position);

        make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_3_best.n_moves,&solution_3_best.positions[0],solution_3_elapsed_time,solution_3_count,"Sol. 3");
      }
#if !_PRINT_FOR_MATLAB_
      printf(" %3d %16lu %9.3e |",solution_3_best.n_moves,solution_3_count,solution_3_elapsed_time);
#else
      printf( " %3d %16lu %9.3e ",solution_3_best.n_moves,solution_3_count,solution_3_elapsed_time);
#endif
    }
    else
    {
      solution_3_best.n_moves = -1;
#if !_PRINT_FOR_MATLAB_
      printf("                                |");
#endif
    }
#endif

// SOLUTION 4 

#if _INCLUDE_SOL_4_

    for(int p = 0; p <= _max_road_size_ ; p++)
      for(int z = 0; z <= _max_road_speed_; z++)
        r[p][z] = 0;

    if(solution_4_elapsed_time < _time_limit_)
    {
      solve_4(final_position);
      if(print_this_one != 0)
      {
        //sprintf(file_name,"%03d_4.pdf",final_position);
        //make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_4_best.n_moves,&solution_4_best.positions[0],solution_4_elapsed_time,solution_4_count,"Solution 4 - DP with memoization");
      }
#if !_PRINT_FOR_MATLAB_
      printf(" %3d %16lu %9.3e |",solution_4_best.n_moves,solution_4_count,solution_4_elapsed_time);
#else
      printf(" %3d %16lu %9.3e ",solution_4_best.n_moves,solution_4_count,solution_4_elapsed_time);
#endif
    }

    else
    {
      solution_4_best.n_moves = -1;
#if !_PRINT_FOR_MATLAB_
      printf("                                |");
#endif
    }
#endif

    // fifth solution 

#if _INCLUDE_SOL_5_
    for(int p = 0; p <= _max_road_size_ ;p++)
      for(int z = 0; z <= _max_road_speed_; z++)
        r[p][z] = 0;

    if(solution_5_elapsed_time < _time_limit_)
    {
      solve_5(final_position);
      if(print_this_one != 0)
      {
        sprintf(file_name,"%03d_5.pdf",final_position);
        make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_5_best.n_moves,&solution_5_best.positions[0],solution_5_elapsed_time,solution_5_count,"Plain recursion");
      }
#if !_PRINT_FOR_MATLAB_
      printf(" %3d %16lu %9.3e |",solution_5_best.n_moves,solution_5_count,solution_5_elapsed_time);
#else
      printf(" %3d %16lu %9.3e ",solution_5_best.n_moves ,solution_5_count ,solution_5_elapsed_time);
#endif
    }

    else
    {
      solution_5_best.n_moves = -1;
#if !_PRINT_FOR_MATLAB_
      printf("                                |");
#endif
    }
#endif

    // done
    printf("\n");
    fflush(stdout);
    // new final_position
    if(final_position < 50)
      final_position += 1;
    else if(final_position < 100)
      final_position += 5;
    else if(final_position < 200)
      final_position += 10;
    else
      final_position += 20;
  }
#if !_PRINT_FOR_MATLAB_
  printf("--- + --- ----------------  ---------+ --- ----------------  ---------+ --- ----------------  ---------+ --- ---------------- --------- +\n");
#endif
  return 0;
# undef _time_limit_
}
