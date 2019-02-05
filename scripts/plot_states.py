#!/usr/bin/python

import sys
import csv
from pylab import * 
import matplotlib.font_manager as fm

#if ( len(sys.argv) != 2 ):
#    print "Usage: %s filename.dat"
#    exit(1)

fig = figure(figsize=(6,3))
ax1 = fig.add_subplot(111)
fig.subplots_adjust(bottom=0.12,left=0.07,right=0.93) #left=0.12, bottom=0.12, right=0.12, top=0.12)

lines = []

for what in [100,200,300,400,500, 600,648]:
    reader = csv.reader(open("../stage3/cfg/savestates/state-%i.dat" % what, 'r'), delimiter=' ')

    row = reader.next()
    print row
    height,width = row

    values = []

    for line in reader: 
        #print line
        values.append(float(max(line)))

    #print values
    line = plot(values)
    lines.append(line)
xlim([0,81])
title('Learned Value Function',fontsize=6)
xlabel('State', fontsize=5)
ylabel('Reward', fontsize=5)
figlegend(lines,('100','200','300','400','500','600','648'), 'lower center', ncol=7, prop=fm.FontProperties(size=5))
for tick in ax1.xaxis.get_major_ticks():
    tick.label1.set_fontsize(4)
for tick in ax1.yaxis.get_major_ticks():
    tick.label1.set_fontsize(4)
savefig('foo.pdf',dpi=300)
show()
