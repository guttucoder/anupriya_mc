nidx=999
fname='mc1_conf.txt'

set key off

plot for [i=0:nidx] fname index i using 2:(i):1 w p pt 7 ps 0.2 palette
