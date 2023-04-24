import math
# If installed, use matplotlib!
import matplotlib.pyplot as plt

# distances in Mpc
r = [ 0.214, 0.263, 0.275, 0.576, 0.9, 0.9, 1.075, 1.05, 1.94 ]

# velocities in km/s
v = [ -130, -70, 202.5, 252, -30, 500, 437.5, 710, 840 ]

# Plot v versus r
plt.scatter(r,v)

# For checking n < 2 condition:
#r = [0.0, 1.0]
#v = [0.0, 1.0]

# For checking denom > 0.000001 condition :
#r = [0.0, 0.0, 0.0]
#v = [0.0, 0.0, 0.0]

n = len(r)   # number of galaxies

if n <= 2 :
      print 'Error! Need at least two data points!'
      exit()


# Compute all of the stat. variables we need
s_x = 0
s_y = 0
s_xx = 0
s_xy = 0
sigma2 = 0
for i in range (0, 8): 
   s_x += r[i]
   s_y += v[i]
   s_xx += r[i]**2
   s_xy += r[i]*v[i]
denom = n * s_xx - s_x**2
if abs( denom ) < 0.000001 : 
      print 'Error! Denomominator is zero!'
      exit()

# Alternatively : slower, but clearer : 
#s_x  = sum(r)
#s_y  = sum(v)
#s_xx = sum(x**2 for x in r)
#s_xy = sum(r[i]*v[i] for i in range(

# Compute y-intercept and slope 
a = (s_xx * s_y - s_x * s_xy) / denom
b = (n*s_xy - s_x * s_y) / denom   

# Compute uncertainties
if n > 2 : 
      sigma = math.sqrt(sum((v[i] - (a+b*r[i]))**2 for i in range(n)) / (n-2))
      sigma_a = math.sqrt(sigma**2 * s_xx / denom)
      sigma_b = math.sqrt(sigma**2 * n / denom)
else :
      sigma = 0.
      sigma_a = 0.
      sigma_b = 0.

# Print out results
print ' Least squares fit of', 9, 'data points'
print ' -----------------------------------'
print " Hubble's constant slope   b = {0:6.2f} +- {1:6.2f}  km/s/Mpc".format( b, sigma_b)
print " Intercept with r axis     a = {0:6.2f} +- {1:6.2f}  km/s".format( a, sigma_a)
print ' Estimated v error bar sigma =', round(sigma, 1), 'km/s'

plt.show()
