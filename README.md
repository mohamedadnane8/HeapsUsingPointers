# HeapsUsingPointers
I implemented the heaps in this project without using an array. Although this implementation is more time costly(still log(n)), but it has an efficient memory utilization. 
To acheive that I have used a binary counter, which keeps track of the position of the last element. 
this project also prints the heaps in a form of a tree. 
This project aims to serve add and serve patients in ER.

A demonstration how the binary counter will be useful when creating this heap:


                        1=1
                2=10			    3=11
            4=100		5=101	6=110		7=111
                       ...
                       
 the first '1' in the binary to start.
 the characters after the first '1' indicate where to go (1 to the left and 0 to the right).	
