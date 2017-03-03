import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import random
def linear_regression_tf():
	points_num = 1000
	
	#predefine W0 (weight0)
	W0_pre = 0.1
	#predefine b (bias)
	b_pre  = 0.3
	vectors = []
	for index in xrange(points_num):
		x = np.random.normal(0,0.55)
		y = W0_pre*x + b_pre + np.random.normal(0.0,0.03)					
		vectors.append([x,y])

	
	x_data = [v[0] for v in vectors]
	y_data = [v[1] for v in vectors]
	
	#index_vector = [index for index in xrange(points_num)]
	#plt.plot(x_data,y_data)
	#print(vectors)	
	W0 = tf.Variable(tf.zeros([1]))
	b = tf.Variable(tf.zeros([1]))

	y = W0 * x_data + b

	loss =  tf.reduce_mean(tf.square(y - y_data))
	
	optimizer = tf.train.GradientDescentOptimizer(0.5)
	
	train = optimizer.minimize(loss)

	init = tf.global_variables_initializer()

	with tf.Session() as sess:
		sess.run(init)
		for step in xrange(100):
			sess.run(train)
			if step % 10 == 0:
				print(step,sess.run(W0),sess.run(b))
				plt.plot(x_data, sess.run(W0)*x_data + sess.run(b),label = str(step))
	
	plt.plot(x_data,y_data,'ro',label = 'original data')
	plt.legend()

import pdb


def linear_regression():
	points_num = 100
	
	#predefine W0 (weight0)
	W0_pre = 0.1
	#predefine b (bias)
	b_pre  = 0.3
	vectors = []
	for index in xrange(points_num):
		#x = np.random.normal(0,0.55)
		x = index
		y = W0_pre*x #+ b_pre + np.random.normal(0.0,0.03)					
		vectors.append([x,y])

	
	x_data = [v[0] for v in vectors]
	y_data = [v[1] for v in vectors]
	
	#index_vector = [index for index in xrange(points_num)]
	#plt.plot(x_data,y_data)
	#print(vectors)	
	#W0 = np.random.rand()
	#b = np.random.rand()
	W0 = 0.0
	b = 0.0
	learning_rate = 0.5
	
	for step in xrange(100):
		w0_diff_sum = 0.0
		b_diff_sum = 0.0
		for point_index in xrange(points_num):
			y = W0 * x_data[point_index] #+ b
			w0_diff_sum += (y_data[point_index] - y)*x_data[point_index]
			b_diff_sum += (y_data[point_index] - y)
		
		#print(w0_diff_sum,b_diff_sum)		
		#pdb.set_trace()
		W0 = W0 +1.0/points_num * learning_rate * w0_diff_sum
		#b = b + learning_rate * b_diff_sum
		if step % 10 == 0:
			print(step,W0,b,w0_diff_sum) 
	
	#plt.plot(x_data,y_data,'ro',label = 'original data')
	#plt.legend()

def get_data(dataSet):
	m,n = np.shape(dataSet)
	trainData = np.ones((m,n))
	trainData[:,:,-1] = dataSet[:,:,-1]
	trainLabel = dataSet[:-1]
	return trainData,trainLabel

class perceptron(object):
	def __init__(self,debugMode = True):
		self.debug = debugMode
		self.iteration = 0

	def init(self,learningRate = 0.1,maxIteration = 1000,initWeights_Start = 0,\
		initWeights_End=1):
		self.theta = learningRate
		self.maxIteration = maxIteration
		#self.weights = [random.uniform(initWeights_Start,initWeights_End) for _ in xrange(2)]
		self.weights = [0,0]
	def train(self,trainData):
		learned = False
		while not learned:
			covergence = 0.0

			for x in trainData:
				ret = self.expected(x)
				if x[2] != ret:
					err = x[2]-ret
					self._updateWeight(err,x)
					covergence += err**2
			
			self.iteration += 1
		
			if covergence == 0.0 or self.iteration >= self.maxIteration:
				if self.debug:
					print 'linear mode: y=' + str(self.weights[1])+'x2+'+ str(self.weights[0])+'x1'
					print(covergence,self.iteration)
				learned = True
		return self.weights[0],self.weights[1]	
	def _updateWeight(self,err,trainDataPart):
		for x in xrange(2):
			self.weights[x] += self.theta * err * trainDataPart[x]
		
	def expected(self,data):
		sum = 0
		for x in xrange(2):
			sum += data[x]*self.weights[x]
		if sum >= 0:
			return 1
		else:
			return -1 

from mpl_toolkits.mplot3d import Axes3D

def draw3DSurface():
	fig = plt.figure()
	ax = Axes3D(fig)
	X = np.arange(-4,4,0.25)
	Y = np.arange(-4,4,0.25)
	X,Y = np.meshgrid(X,Y)
	R = np.sqrt(X**2 + Y**2)
	Z = np.sin(R)
	ax.plot_surface(X,Y,Z,rstride=1,cstride=1,cmap='rainbow')
	plt.show()

'''
Plot the plane:
	 Y = W0*X0 + W1*X1 +b
'''
def plot_plane(W0,W1,b):
	points_num = 100
	X0 = [np.random.normal(0,0.55) for _ in xrange(points_num)]
	X1 = [np.random.normal(0,0.55) for _ in xrange(points_num)]
	
	fig = plt.figure()
	ax = fig.add_subplot(111,projection='3d')
	#ax = Axes3D(fig)
	ax.set_xlabel('X0')
	ax.set_ylabel('X1')
	ax.set_zlabel('Y')
	
	mesh_X0,mesh_X1 = np.meshgrid(X0,X1)
	Y = mesh_X0*W0 + mesh_X1*W1 + b

	ax.plot_wireframe(mesh_X0,mesh_X1,Y,rstride=1,cstride=1)
	plt.show()
	

if __name__ == '__main__':
	'''W0 = 0.1
	W1 = 0.2
	sample_num = 1000
	trainData = []
	for i in xrange(sample_num):
		x0 = np.random.normal(0,0.55)
		x1 = np.random.normal(0,0.55)
		x2 = 1
		if W0 * x0 + W1 * x1 < 0:
			x2 = -1
		trainData.append([x0,x1,x2])
		#if x2 == 1:
		#	plt.plot(x0,x1,'ro','1')
		#else:
		#	plt.plot(x0,x1,'bo','-1')
		
		
	perceptron = perceptron()
	perceptron.init()
	W0,W1 =perceptron.train(trainData)
	'''#plt
	plot_plane(0.1,0.2,-0.1)
	
		


	

				
		
	
