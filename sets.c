//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                             LIBRARIES
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                                 SCOPE
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

void set_file(FILE **file_ptr_, char *uid_str, int system_size_int, int simulation_time_int, int seed_int_) ;
void set_grid_random(int system_size_int, int grid_ary_[system_size_int][system_size_int], gsl_rng * gsl_rng_ptr_) ;

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                OPEN and SET FILE NAME
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

void set_file(FILE **file_ptr_, char *uid_str, int system_size_int, int simulation_time_int, int seed_int_){

  char *begin_str="./Data/";
  char *size_str="Size-"; 
  char *mcs_str="_Time-";
  char *seed_str="_Seed-";
  char *ext_str=".txt";
  char file_str[ strlen( begin_str ) + strlen( uid_str ) + strlen( size_str ) + strlen( ext_str ) + strlen( seed_str ) + strlen( mcs_str ) + 20 ];
  
  snprintf( file_str, sizeof(file_str), "%s%s%s%d%s%d%s%d%s", begin_str, uid_str, size_str, system_size_int, mcs_str, simulation_time_int, seed_str, seed_int_, ext_str );

  *file_ptr_ = fopen(file_str, "w");

}

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                              SET GRID
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

void set_grid_random(int system_size_int, int grid_ary_[system_size_int][system_size_int], gsl_rng * gsl_rng_ptr_){
  
  int i_int = 0;
  int j_int = 0;
  
  float random_number_float = 0.0;

  for( i_int=0; i_int < system_size_int; i_int++ ){

    for( j_int=0; j_int < system_size_int; j_int++ ){

      random_number_float = gsl_rng_uniform( gsl_rng_ptr_ );
      
      if( random_number_float <= 0.25 ){
    
        grid_ary_[ i_int ][ j_int ] = 0 ;
    
      } else if( random_number_float <= 0.50 ){
    
        grid_ary_[ i_int ][ j_int ] = 1 ;
    
      } else if( random_number_float <= 0.75 ){
    
        grid_ary_[ i_int ][ j_int ] = 2 ;
    
      } else{

        grid_ary_[ i_int ][ j_int ] = 3 ;

      }
    }
  }
}

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                                   EOF
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC