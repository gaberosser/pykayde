__author__ = 'gabriel'
import numpy as np
import CppVector
import Kde
from time import time
from kde.methods.pure_python import FixedBandwidthKde
import cProfile
import pstats

n = 20000
data = np.random.randn(n, 3)
bandwidths = np.array([1., 2., 3.])
p = FixedBandwidthKde(data, bandwidths=bandwidths, normed=True)

# setup c++ kde
tic = time()
cdata = CppVector.VectorDouble2D()
for i in range(n):
    this_data = CppVector.VectorDouble1D()
    this_data.extend(data[i])
    cdata.append(this_data)
c = Kde.FixedBandwidthKde(cdata)
bdw = CppVector.VectorDouble1D()
bdw.extend(bandwidths)
c.set_bandwidths(bdw)
print "C++ KDE setup took %f s" % (time() - tic)

def cpp_external():
    print "C++ pdf external iteration"
    tic = time()
    tmp = [CppVector.VectorDouble1D() for i in range(n)]
    [tmp[i].extend(data[i]) for i in range(n)]
    print "Vector creation took %f s" % (time() - tic)
    tic = time()
    resc_it = [c.pdf(x, True) for x in tmp]
    print "Computation took %f s" % (time() - tic)
    return resc_it

def cpp_internal():
    print "C++ pdf internal iteration"
    tic = time()
    resc = c.pdf(cdata, True)
    print "Computation took %f s" % (time() - tic)
    return resc

# print "C++ pdf internal iteration"
# tic=time()
# resc = c.pdfm(data)
# print (time()-tic)

print "Python/Numpy implementation"
tic=time()
resp=p.pdf(data[:,0], data[:,1], data[:,2])
print time()-tic

resc_it = cpp_external()
print "Num pdf calls: %d" % c.num_pdf_calls

resc = cpp_internal()
print "Num pdf calls: %d" % c.num_pdf_calls

print "Pure, bloody-minded C++ exp() iteration."
tic = time()
res = c.foo(this_data)
print "Computation took %f s" % (time() - tic)

# cProfile.run('cpp_external()', 'cpp_external.pstat')
# p = pstats.Stats('cpp_external.pstat')
# p.strip_dirs().sort_stats(-1).print_stats()
