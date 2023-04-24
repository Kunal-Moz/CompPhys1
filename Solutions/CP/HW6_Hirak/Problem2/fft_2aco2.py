import matplotlib.pyplot as plt

from fft import fft, fft_power, ifft
from numpy import array, real
import math
import time


# data downloaded from http://www.sidc.be/DATA/yearssn.dat
print ' Co2 data'
data_file_name = 'co2_mm_mlo.dat'
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
            xval = float(words[2])
            yval = float( words[4] )
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

maxfreq = 50
rawpowery = fft_power(Y)
ps = fft_power(Y)
#ps = fft_power(Y)
#print y
# Now smooth the data
for iY in range(maxfreq, len(Y)-maxfreq ) :
    Y[iY] = complex(0,0)
    #Y[iY] = Y[iY] * (0.5 - 0.5 * math.cos(2*math.pi*iY/float(N-1))) 

    #for iY in range(0,N) : 
     #   Y[iY] = Y[iY] * math.exp(-1.0*iY / 50.0)



powery = fft_power(Y)


M = len(ps)
log2M = math.log(M, 2)
if log2M - int(log2M) > 0.0 :
    print 'Padding with zeros!'
    pads2 = [0.0] * (pow(2, int(log2M)+1) - M)
    ps = ps + pads2
    N = len(ps)
    print 'Padded : '
    print len(ps)
    for ik in xrange(len(ps)) :									# first pad and window
            ps[ik] = ps[ik] * (0.5 - 0.5 * math.cos(2*math.pi*ik/float(M-1)))



z = array(ps)
psnew = fft(z)

maxfreq2 = 50
for iz in range(maxfreq2, len(psnew)- maxfreq2 ) :
    psnew[iz] = complex(0,0)
    #psnew[iz] = psnew[iz] * (0.5 - 0.5 * math.cos(2*math.pi*iz/float(N-1))) 
#print psnew

psback = ifft(psnew)
psk = len(psback)

#print 'this is ps' , len(smoothps)

 

for ip in xrange(len(psback)) :
     if ((0.5 - 0.5 * math.cos(2*math.pi*ip/float(psk-1))) != 0.0):									# # undoing windowing
          psback[ip] = (psback[ip] / (0.5 - 0.5 * math.cos(2*math.pi*ip/float(psk-1))) )                                             
     #else:
      #    psback[ip] = psback[ip-1]
#print powery

smoothps = real(psback)
ynew = smoothps[:-len(pads2)]														# undoing padding
psx = array([ float(i) for i in xrange(len(ynew)) ] )
Yrenew = [math.sqrt(ynew[i].real**2+ynew[i].imag**2) for i in xrange(len(ynew))]




powerx = array([ float(i) for i in xrange(len(powery)) ] )
#print 'Len powery', len(powery)
Yre = [math.sqrt(Y[i].real**2+Y[i].imag**2) for i in xrange(len(Y))]
#print 'this is Y', Y
ysmoothed = ifft(Y)
#print 'this is ysmoothed', ysmoothed
ysmoothedreal = real(ysmoothed)


#print 'this is ysmoothedreal', ysmoothedreal
#print len(x), len(Yre)
#print len(powerx), len(powery)
ax1 = plt.subplot(2, 1, 1)
p1, = plt.plot( x, y )
p2, = plt.plot( x, ysmoothedreal )
ax1.legend( [p1,p2], ['Original_data', 'Smoothed_data'] )
plt.title("Smoothed power spectrum plot")
plt.xlabel("Year")
plt.ylabel("CO2 ppm")
ax2 = plt.subplot(2, 1, 2)
p3, = plt.plot( powerx, rawpowery)
p4, = plt.plot( psx, ynew )
ax2.legend( [p3, p4], ["Powerraw", "Smoothed_power"] )
plt.yscale('log')

plt.xlabel("frequency")
plt.ylabel("CO2 ppm power spectrum")


#plt.show()
fig = plt.gcf()
fig.set_size_inches((11,8.5), forward=False)
fig.savefig('problem_2a.png', dpi=500)

#plt.savefig('problem_2a.png')
