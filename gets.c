//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                             LIBRARIES
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                                 SCOPE
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

void print_grid(FILE *file_ptr, int system_size_int_, int grid_2d_ary_[system_size_int_][system_size_int_]) ;
int avalanche(int system_size_int_, int grid_2d_ary_[system_size_int_][system_size_int_], gsl_rng * gsl_rng_ptr_) ;
int topple( int position_x_int_, int position_y_int_, int system_size_int_, int grid_2d_ary_[system_size_int_][system_size_int_] );

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                PRINT SANDPILE IN FILE
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

void print_grid(FILE *file_ptr, int system_size_int_, int grid_2d_ary_[system_size_int_][system_size_int_]){

  int i_int=0;
  int j_int=0;

  for( i_int = 0; i_int < system_size_int_; i_int++){

    for( j_int = 0; j_int < system_size_int_; j_int++){

      fprintf(file_ptr, "%d\t", grid_2d_ary_[ i_int ][ j_int ] );

    }

    fprintf(file_ptr, "\n");
  }

  fprintf(file_ptr, "\n\n");

}

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                             AVALANCHE
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

int avalanche(int system_size_int_, int grid_2d_ary_[system_size_int_][system_size_int_], gsl_rng * gsl_rng_ptr_){

  int avalanche_size_int = 0 ;
  int position_x_int = 0 ;
  int position_y_int = 0 ;

  float aux_x_int = 0 ;
  float aux_y_int = 0 ;

  aux_x_int = gsl_rng_uniform( gsl_rng_ptr_ ) ;
  aux_y_int = gsl_rng_uniform( gsl_rng_ptr_ ) ;

  position_x_int = (int)floor( aux_x_int*system_size_int_ ) ;
  position_y_int = (int)floor( aux_y_int*system_size_int_ ) ; 

  grid_2d_ary_[ position_x_int ][ position_y_int ] += 1 ;

  avalanche_size_int = topple( position_x_int, position_y_int, system_size_int_, grid_2d_ary_ ) ;

  return avalanche_size_int ;
}

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                                TOPPLE
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

int topple( int position_x_int_, int position_y_int_, int system_size_int_, int grid_2d_ary_[system_size_int_][system_size_int_] ){

  if( grid_2d_ary_[position_x_int_][position_y_int_] >= 4 ){
    
    grid_2d_ary_[position_x_int_][position_y_int_] = 0 ;

    if( position_x_int_ == system_size_int_-1 && position_y_int_ == system_size_int_-1 ){
      
      grid_2d_ary_[position_x_int_][position_y_int_-1] += 1 ;
      grid_2d_ary_[position_x_int_-1][position_y_int_] += 1 ;

      return 1+
        topple( position_x_int_, position_y_int_-1, system_size_int_, grid_2d_ary_ )+
        topple( position_x_int_-1, position_y_int_, system_size_int_, grid_2d_ary_ );

    }else if( position_x_int_ == system_size_int_-1 && position_y_int_ == 0 ){
      
      grid_2d_ary_[position_x_int_-1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_+1] += 1 ;

      return 1+
        topple( position_x_int_, position_y_int_+1, system_size_int_, grid_2d_ary_ )+
        topple( position_x_int_-1, position_y_int_, system_size_int_, grid_2d_ary_ );
      
    }else if( position_x_int_ == 0 && position_y_int_ == system_size_int_-1 ){
      
      grid_2d_ary_[position_x_int_+1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_-1] += 1 ;

      return 1+
        topple( position_x_int_+1, position_y_int_, system_size_int_, grid_2d_ary_ )+
        topple( position_x_int_, position_y_int_-1, system_size_int_, grid_2d_ary_ );

    }else if( position_x_int_ == 0 && position_y_int_ == 0 ){
      
      grid_2d_ary_[position_x_int_+1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_+1] += 1 ;

      return 1+
        topple( position_x_int_+1, position_y_int_, system_size_int_, grid_2d_ary_ )+
        topple( position_x_int_, position_y_int_+1, system_size_int_, grid_2d_ary_ );

    }else if( position_x_int_ == system_size_int_-1 ){

      grid_2d_ary_[position_x_int_-1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_+1] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_-1] += 1 ;
      
      return 1+
        topple(position_x_int_-1, position_y_int_, system_size_int_, grid_2d_ary_)+
        topple(position_x_int_, position_y_int_+1, system_size_int_, grid_2d_ary_)+
        topple(position_x_int_, position_y_int_-1, system_size_int_, grid_2d_ary_);

    }else if( position_x_int_ == 0 ){

      grid_2d_ary_[position_x_int_+1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_+1] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_-1] += 1 ;
      
      return 1+
        topple(position_x_int_+1, position_y_int_, system_size_int_, grid_2d_ary_)+
        topple(position_x_int_, position_y_int_+1, system_size_int_, grid_2d_ary_)+
        topple(position_x_int_, position_y_int_-1, system_size_int_, grid_2d_ary_);

    }else if( position_y_int_ == system_size_int_-1 ){

      grid_2d_ary_[position_x_int_+1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_-1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_-1] += 1 ;
      
      return 1+
        topple(position_x_int_+1, position_y_int_, system_size_int_, grid_2d_ary_)+
        topple(position_x_int_-1, position_y_int_, system_size_int_, grid_2d_ary_)+
        topple(position_x_int_, position_y_int_-1, system_size_int_, grid_2d_ary_);

    }else if( position_y_int_ == 0 ){

      grid_2d_ary_[position_x_int_+1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_-1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_+1] += 1 ;
      
      return 1+
        topple(position_x_int_+1, position_y_int_, system_size_int_, grid_2d_ary_)+
        topple(position_x_int_-1, position_y_int_, system_size_int_, grid_2d_ary_)+
        topple(position_x_int_, position_y_int_+1, system_size_int_, grid_2d_ary_);

    }else{

      grid_2d_ary_[position_x_int_+1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_-1][position_y_int_] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_+1] += 1 ;
      grid_2d_ary_[position_x_int_][position_y_int_-1] += 1 ;

      return 1+
        topple(position_x_int_+1, position_y_int_, system_size_int_, grid_2d_ary_ )+
        topple(position_x_int_-1, position_y_int_, system_size_int_, grid_2d_ary_ )+
        topple(position_x_int_, position_y_int_+1, system_size_int_, grid_2d_ary_ )+
        topple(position_x_int_, position_y_int_-1, system_size_int_, grid_2d_ary_ ) ;
    }
  } else{
    
    return 0;
    
  }
}

//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//                                                                   EOF
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC