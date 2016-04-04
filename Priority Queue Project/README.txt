HOMEWORK 9: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  < Xu Chai >


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 hours >

w = the width of the input image
h = the height of the input image
p = the number of black pixels in the input image

——————————————————————————————————————————————————————————————————————————————————————————
NAIVE ALGORITHM:

Order Notation: O(w^2 * h^2)

Timing Experiment Data:
Test Case	                 Real	          User	          Systiny_5x5.ppm	               0m0.012s  	0m0.001s	0m0.002ssmall_10x10.ppm 	       0m0.011s	        0m0.001s	0m0.002ssquiggle_30x30.ppm	       0m0.025s	        0m0.016s	0m0.003slines_100x100.ppm	       0m1.472s	        0m1.451s	0m0.004sdata_structures_300x300.ppm    2m9.714s	        2m9.285s        0m0.142sdots_1000x1000.ppm	       three hours had past, but the result still didn’t run out		
Discussion:
This naive algorithm is based on a four-level nested loop which tries to compute
 the distance between every pixels. It does a lot of work that we don’t need at all. 
So it is very ineffective and slow.
——————————————————————————————————————————————————————————————————————————————————————————
IMPROVED ALGORITHM:

Order Notation:O(w*h*p)

Timing Experiment Data:
Test Case                      	Real	          User         	  Sys
tiny_5x5.ppm            	0m0.013s	0m0.001s	0m0.003ssmall_10x10.ppm        		0m0.014s	0m0.002s	0m0.002ssquiggle_30x30.ppm              0m0.017s	0m0.006s	0m0.003slines_100x100.ppm	       	0m0.081s	0m0.069s	0m0.003sdata_structures_300x300.ppm	0m15.929s	0m15.907s	0m0.008s
dots_1000x1000.ppm              half an hour had past, but the result still didn’t run out


Discussion:
This improved algorithm is just a little better than naive algorithm. 
Instead of four-level nested loop, we first use a nested loop to collect 
all the black pixels(O(w*h)), then use another nested loop to compute all
other white pixels closest distance to these black pixels(O(w*h*p)), so 
total is O(w*h)+O(w*h*p), which can be concluded as O(w*h*p). 
This method is faster in some degree, but is still not very good and 
very slow when the input is very big.
——————————————————————————————————————————————————————————————————————————————————————————

FAST MARCHING METHOD (with a map):

Order Notation:

Timing Experiment Data:
Test Case                      	Real	          User         	  Sys
tiny_5x5.ppm	                0m0.012s	0m0.001s	0m0.002ssmall_10x10.ppm 	        0m0.015s	0m0.003s	0m0.003ssquiggle_30x30.ppm	        0m0.020s	0m0.008s	0m0.003slines_100x100.ppm	        0m0.072s	0m0.060s	0m0.003sdata_structures_300x300.ppm	0m0.676s	0m0.661s	0m0.005sdots_1000x1000.ppm	        0m8.639s	0m8.581s	0m0.058s


Discussion:
In my fast marching method. I firstly assign each pixel a pair of coordinate(O(w*h))
, then use a nested loop to collect all black pixels(O(w*h)), then push these black 
pixels into a vector(O(1)*p), and further compute the distance of each black pixel’s
 8 adjacent pixels(O(1)*8*p)), reset their distance value(O(1)*8*p)), temporarily store 
them in a map(O(log8*p)). Next, I transfer this map into a vector that contains this 
these pixels((O(1)*8*p))), use this vector build a priority queue(O(1)* 8*p, 
in which, average case of perculate_up is O(1), the approximate vector size is 8*p). 

The running time for the operation above is (w*h + p + 8*p + 8*p + 8*p + 8*p)
which can be concluded as O(w*h + p);


Next, I use a while loop to do propagate
(keep repeating (1) to (3) until priority queue is empty)
(1) removing the top element(O(log8*p):the approximate size of the priority queue is 8*p 
    and the perculate_down is O(logn))
(2) compute 8 adjacent pixels of the removed root (O(1)*8)
(3) if a certain adjacent pixel is already in queue, adjust its place.
    (perculate_up O(1) + perculate_down O(log8*p))
    if a certain adjacent pixel is not in queue, push it in the queue (perculate_up O(1));

the while loop is about 8*p times iteration. 
So the total running time for this loop is 8*p*(log8*p + 8 + 1 + log8*p + 1)
which can be concluded as O(p*logp)

So the total order notation is O(w*h + p + p*logp), which is O(w*h + plogp), approximately