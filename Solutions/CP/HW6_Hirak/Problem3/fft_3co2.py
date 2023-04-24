import matplotlib.pyplot as plt

from fft import fft, fft_power, ifft
from numpy import array, real
import math
import time


# data downloaded from http://www.sidc.be/DATA/yearssn.dat
print ' Co2 data'
data_file_name = 'nonlinear.dat'
file = open(data_file_name, 'r')
lines = file.readlines()
file.close()
print ' read', len(lines), 'lines from', data_file_name

window = False

yinput = []
xinput = []

for line in lines :
    if line[0] != '#' :
        try:
            words = line.split()
            xval = float(words[0])
            yval = float( words[1] )
            yinput.append( yval )
            xinput.append( xval )
        except ValueError :
            print 'bad data:',line


N = len(yinput)
log2N = math.log(N, 2)
if log2N - int(log2N) > 0.0 :
    print 'Padding with zeros!'
    pads = [0.0] * (pow(2, int(log2N)+1) - N)
    yinput = yinput + pads
    N = len(yinput)
    print 'Padded : '
    print len(yinput)
    # Apply a window to reduce ringing from the 2^n cutoff
    if window : 
        for iy in xrange(len(yinput)) :									# first pad
            yinput[iy] = yinput[iy] * (0.5 - 0.5 * math.cos(2*math.pi*iy/float(N-1)))			# then take fft
													# then smooth
y = array( yinput ) 											# take ifft
x = array([ float(i) for i in xrange(len(y)) ] )							# take real of ifft
Y = fft(y)

maxfreq = 10				# cleaning up jitters.

#print y
# Now smooth the data
for iY in range(maxfreq, len(Y)-maxfreq ) :
    Y[iY] = complex(0,0)
    #Y[iY] = Y[iY] * (0.5 - 0.5 * math.cos(2*math.pi*iY/float(N-1))) 

    #for iY in range(0,N) : 
     #   Y[iY] = Y[iY] * math.exp(-1.0*iY / 50.0)



powery = fft_power(Y)



powerx = array([ float(i) for i in xrange(len(powery)) ] )
#print 'Len powery', len(powery)
Yre = [math.sqrt(Y[i].real**2+Y[i].imag**2) for i in xrange(len(Y))]
#print 'this is Y', Y
ysmoothed = ifft(Y)
#print 'this is ysmoothed', ysmoothed
ysmoothedreal = real(ysmoothed)





fftY = real(Y)
fftx = array([ float(i) for i in xrange(len(fftY)) ] )
#print 'this is ysmoothedreal', ysmoothedreal
#print len(x), len(Yre)
#print len(powerx), len(powery)




data_file_name_new = 'linear.dat'						# adding the data to the linear trend
file = open(data_file_name_new, 'r')
lines_new = file.readlines()
file.close()
print ' read', len(lines_new), 'lines from', data_file_name_new

new_yinput = []

for line in lines_new :
    if line[0] != '#' :
        try:
            words = line.split()
            
            yval = float( words[1] )
            new_yinput.append( yval )
            
        except ValueError :
            print 'bad data:',line
c = array(new_yinput)
d = len(c)
for ia in range (d):
    ysmoothedreal[ia] = ysmoothedreal[ia] + c[ia]					# adding the data



											# reading actual Co2 data
data_file_name_raw = 'co2_mm_mlo.dat'
file = open(data_file_name_raw, 'r')
lines_raw = file.readlines()
file.close()
#print ' read', len(lines), 'lines from', data_file_name


yinput_raw = []
xinput_raw = []

for line in lines_raw :
    if line[0] != '#' :
        try:
            words = line.split()
            xval_raw = float(words[2])
            yval_raw = float( words[4] )
            yinput_raw.append( yval_raw )
            xinput_raw.append( xval_raw )
        except ValueError :
            print 'bad data:',line


N_raw = len(yinput_raw)
log2N_raw = math.log(N_raw, 2)
if log2N_raw - int(log2N_raw) > 0.0 :
    print 'Padding with zeros!'
    pads_raw = [0.0] * (pow(2, int(log2N_raw)+1) - N_raw)
    yinput_raw = yinput_raw + pads_raw
    N_raw = len(yinput_raw)
    print 'Padded_raw : '
    print len(yinput_raw)
    # Apply a window to reduce ringing from the 2^n cutoff
    if window : 
        for iy in xrange(len(yinput_raw)) :									
            yinput_raw[iy] = yinput_raw[iy] * (0.5 - 0.5 * math.cos(2*math.pi*iy/float(N_raw-1)))		
													
y_raw = array( yinput_raw ) 										
x_raw = array([ float(i) for i in xrange(len(y_raw)) ] )



ax1 = plt.subplot(2, 1, 1)
p1, = plt.plot( x, ysmoothedreal)
p2, = plt.plot( x_raw, y_raw )
ax1.legend( [p1,p2], ['Smoothed_reconstructed_data','Original_data'] )
plt.title("Reconstructed vs Raw spectrum")
plt.xlabel("Year")
plt.ylabel("CO2 ppm")

ax2 = plt.subplot(2, 1, 2)
p3, = plt.plot( x, ysmoothedreal)
p4, = plt.plot( x_raw, y_raw )
ax2.legend( [p3,p4], ['Reconstructed_data_magnified','Original_data_magnified'] )
#plt.title("Reconstructed vs Raw spectrum")
plt.xlim(0,650)
plt.ylim(300,425)
plt.xlabel("Year")
plt.ylabel("CO2 ppm")


#plt.show()
fig = plt.gcf()
fig.set_size_inches((11,8.5), forward=False)
fig.savefig('problem_3b.png', dpi=500)

#plt.savefig('problem_2a.png')
