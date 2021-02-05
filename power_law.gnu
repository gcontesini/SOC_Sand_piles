reset

# set output 'power_law.png' 
set terminal pngcairo
ts_data = 'Data/frequency_128.txt'

set grid
set logscale xy
set xlabel "Avalanche Size"
set ylabel "Frequency"
set xrange[0.9:5e2] 

plot ts_data u 1:2 notitle w points pointtype 4 lc rgb "blue"  

f(x)=a*x+b
g(x)=(x**a)*exp(b)

fit f(x) ts_data u (log($1)):(log($2)) via a,b

replot[1:2e2] g(x) title '-1.62518*x+2.58357' lc rgb "black"

set output "power_law.png"

replot