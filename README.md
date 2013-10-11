Visibility Graph: It is a O(n2logn) algorithm for implementing Visibility Graph of a set of obstacles
------------------------------------------------------------------------------------------------------

Overview
---------

->Have multiple obstacles and some single points outside the obstacles.
->All the Obstacles and Lines are calculated using Boost Model package.
->Geometry calculations have been accomplished using Boost Library
->http://www.boost.org/
->Download Boost from : http://sourceforge.net/projects/boost/files/boost/1.54.0/
->Used CImg for drawing the Visibility Graph
->http://cimg.sourceforge.net/download.shtml

More Features
--------------
->Shortest Path is calculated from a source to destination Point
->Dijkstra algorithm is used for this calculation (O(n2)). 
->Dijkstra Algorithm : Implementation by dziaduZLasu (https://github.com/dziaduZLasu/dijkstra)


Output
------
->Visibility Graph with an image of the virtual graph
->Shortest Path from a given source to destination and it is also displayed in an image .

References
-----------
->http://cs.smith.edu/~streinu/Teaching/Courses/274/Spring98/Projects/Philip/fp/algVisibility.htm
->M. deBerg et al, Computational Geometry: algorithms and applications, Springer Verlag, 1997. 

by Nusrat Sultana <nusratst.cse@gmail.com>
A project as part of my Master's Thesis