//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                             LIBRARIES
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <string.h>
#include "sets.c"
#include "gets.c"

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                                  MAIN
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

int main(){

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                  VARIABLE DECLARATION
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

  int system_size_int = 128 ;
  int time_int=0;
  int simulation_time_int = 1e4 ;
  int seed_int = 123456 ;
  int avalanche_size_int = 0 ;

  int grid_2d_ary[system_size_int][system_size_int] ;

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                           OUTPUT FILE
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

  FILE *file_1_ptr=NULL ;
  FILE *file_2_ptr=NULL ;

  set_file( &file_1_ptr, "File_1_", system_size_int, simulation_time_int, seed_int ) ;
  set_file( &file_2_ptr, "File_2_",system_size_int, simulation_time_int, seed_int ) ;

  if( file_1_ptr == NULL ){    
    printf("FILE 1 ERROR\n") ;
    return 1 ;
  }

  if( file_2_ptr == NULL ){   
    printf("FILE 2 ERROR\n") ;
    return 1 ;
  }

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                         INITIALIZTION
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
  
  gsl_rng *gsl_rng_ptr = gsl_rng_alloc( gsl_rng_ranlux ) ;

  gsl_rng_set( gsl_rng_ptr, seed_int ) ;

  set_grid_random( system_size_int, grid_2d_ary, gsl_rng_ptr) ;
  
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                                  CORE
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

  for(time_int=0; time_int < simulation_time_int; time_int++){

    print_grid( file_1_ptr, system_size_int, grid_2d_ary ) ;
    
    avalanche_size_int = avalanche( system_size_int, grid_2d_ary, gsl_rng_ptr ) ;

    if( avalanche_size_int != 0){
      
      fprintf( file_2_ptr, "%d\t%d\n",time_int, avalanche_size_int ) ;

    }

  }

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                   MEMORY DEALLOCATION
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

  gsl_rng_free( gsl_rng_ptr ) ;
  fclose ( file_1_ptr ) ;

  return 0 ;
}
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                                   EOF
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC