reset
                                       
set terminal gif animate delay 2.5
set output 'sand_pile.gif'         
ts_data = 'Data/File_1_Size-128_Time-10000_Seed-123456.txt'
# stats 'Data/File_1_Size-128_Time-10000_Seed-123456.txt' nooutput
unset tics
unset key
set size 0.99,0.95; set origin 0.01,0.05
set xrange[-1:128]
set yrange[-1:128]
set colorbox horizontal                         
set colorbox user origin 0.05,0.05 size 0.90,0.02
set cblabel "0, 1, 2, 3"

set palette defined ( 0 "#FFFFFF", 1 "#C0C0C0", 2 "#808080", 3 "#404040")

do for [i=0:10000] {

    plot ts_data index i matrix with image notitle

}