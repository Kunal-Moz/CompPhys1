import math
from math import *
import matplotlib.pyplot as plt

file_name = "co2_mm_mlo.txt"
file = open(file_name, "r")
lines = file.readlines()
file.close()

dates = []	# x
data = []	# y
for line in lines:
    if len(line) > 4:
        try:
            year = int(line[0:4])
            if year > 1957 and year < 2013:
                words = str.split(line)
                dates.append(words[2])
                ppm = float(words[4])
                if ppm > 0: data.append(ppm)
        except ValueError:
            pass

print " read", len(data), "values from", file_name
#print data


#plt.plot( dates, data )

#plt.show()



n = len(data)   # number of galaxies

if n <= 2 :
      print 'Error! Need at least two data points!'
      exit()

#print n
# Compute all of the stat. variables we need
s_2xy = 0.0
s_yly = 0.0
s_3x = 0.0
s_2x = 0.0

s_xy = 0.0
s_xyly = 0.0
s_y = 0.0
for i in range (0, n): 
   s_2xy += ((float(dates[i]))**2)*(float(data[i]))
   s_yly += (float(data[i]))*(math.log(float(data[i])))
   #s_3x += (float(dates[i]))**3
   #s_2x += (float(dates[i]))**2
   s_xy += (float(dates[i]))*(float(data[i]))
   s_xyly += (float(dates[i]))*(float(data[i]))*(math.log(float(data[i])))
   s_y += (float(data[i]))
   #s_xx += float(dates[i])**2
   #s_xy += float(dates[i])*float(data[i])
#print s_2xy
#print s_4x
#print s_3x
#print s_2x
#print s_xy
#print s_x
#print s_y
denom = (s_y*s_2xy - s_xy**2)
#print denom
if abs( denom ) < 0.000001 : 
      print 'Error! Denomominator is zero!'
      exit()

# Alternatively : slower, but clearer : 
#s_x  = sum(r)
#s_y  = sum(v)
#s_xx = sum(x**2 for x in r)
#s_xy = sum(r[i]*v[i] for i in range(

# Compute y-intercept and slope 

a = (s_2xy*s_yly - s_xy*s_xyly)/denom

b = (s_y*s_xyly - s_xy*s_yly)/denom

aa = exp(a)

print "a = ", aa, "b = ", b

# Compute uncertaintie
s_x = 1.0
s_4x = 1.0
c =1.0
del_a_sqr = 0.0
sigma_sqr_sum = 0.0
sigma_sqr = 0.0
sigma_a = 0.0
sigma_b = 0.0
sigma_c = 0.0
sigma_a_sum = 0.0
del_a = 0.0
del_b = 0.0
del_c = 0.0
sigma_b_sum = 0.0
sigma_c_sum = 0.0
for i in range (0,n):
      k = float(data[i])
      sigma_sqr_sum += (k - a*(b*(float(dates[i]))) )**2

sigma_sqr = sigma_sqr_sum/(n-2)
for i in range (0,n):
      k = float(dates[i])
      p = float(data[i])
      del_a = (((k*k*s_yly + s_2xy*(1+ math.log(p)) - k*s_xyly - s_xy*k*(1+ math.log(p)))/denom) - (((s_2xy*s_yly - s_xy*s_xyly)/denom**2)*(s_2xy + k*k*s_y - 2*s_xy*k)))
      del_b = (((s_xyly + s_y*k*(1+ math.log(p)) - k*s_yly - s_xy*(1+ math.log(p)))/denom) - (((s_y*s_xyly - s_xy*s_yly)/denom**2)*(s_2xy + k*k*s_y - 2*s_xy*k)))
      
      sigma_a_sum += (sigma_sqr * (del_a**2))
      sigma_b_sum += (sigma_sqr * (del_b**2))
      

if n>2:      #print sigma_a_sum
      sigma_a = math.log(math.sqrt(sigma_a_sum))
      sigma_b = (math.sqrt(sigma_b_sum))
      
else:
      sigma_a = 0.0
      sigma_b = 0.0
      

print "sigma a = ", sigma_a, "sigma_b = ", sigma_b





#print "a= ",a,"	sigma a= ", #sigma_a
#print "b= ",b,"	sigma b= ", #sigma_b
#print "c= ",c

# Print out results
print ' Least squares fit of', n , 'data points'
#print ' -----------------------------------'
print " a = {0:6.2f} +- {1:6.2f} ".format( aa, sigma_a)
print " b = {0:6.2f} +- {1:6.2f} ".format( b, sigma_b)
#print " c = {0:6.2f} +- {1:6.2f} ".format( c, sigma_c)
#print ' Estimated v error bar sigma =', round(sigma, 1), 'km/s'

