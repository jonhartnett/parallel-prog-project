# Parallel Programming Special Project
### Jonathan Hartnett
This project measures the performance benefits gained from parallelizing a quicksort implementation. Tested on Ubuntu. 
Simply running the project with sort a large array of random numbers using 1 to n threads where n is the number of cores detected on the machine.
The results of the test are output to stdout in both textual and graphical format.

The following is a sample output run on an 8-core machine:
```
Running sequential sort
Running parallel sort on 2 threads
Running parallel sort on 3 threads
Running parallel sort on 4 threads
Running parallel sort on 5 threads
Running parallel sort on 6 threads
Running parallel sort on 7 threads
Running parallel sort on 8 threads

Sequential:
	Time elapsed: 1524 ms
Parallel x2:
	Time elapsed: 820 ms
	Speedup : 185%
	Efficiency: 92%
Parallel x3:
	Time elapsed: 562 ms
	Speedup : 270%
	Efficiency: 90%
Parallel x4:
	Time elapsed: 459 ms
	Speedup : 331%
	Efficiency: 82%
Parallel x5:
	Time elapsed: 418 ms
	Speedup : 363%
	Efficiency: 72%
Parallel x6:
	Time elapsed: 395 ms
	Speedup : 385%
	Efficiency: 64%
Parallel x7:
	Time elapsed: 381 ms
	Speedup : 399%
	Efficiency: 57%
Parallel x8:
	Time elapsed: 369 ms
	Speedup : 412%
	Efficiency: 51%
Max Speedup: 412% with 8 threads
Max Efficiency: 92% with 2 threads

Speedup graph:
500%|                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                               ⎯
    |                                                                    ⎯⎯⎯⎽⎽⎼⎼⎻⎻⎺⎺ 
    |                                                           ⎯⎯⎽⎽⎼⎼⎻⎺⎺            
    |                                                   ⎯⎯⎽⎼⎻⎻⎺⎺                     
    |                                             ⎯⎽⎽⎼⎻⎺                             
    |                                         ⎯⎽⎻⎺                                   
    |                                    ⎯⎽⎼⎻⎺                                       
    |                                 ⎯⎼⎺                                            
    |                               ⎽⎻                                               
    |                            ⎯⎼⎺                                                 
    |                          ⎯⎼                                                    
    |                        ⎽⎻                                                      
    |                      ⎽⎺                                                        
    |                    ⎯⎻                                                          
    |                   ⎼                                                            
    |                 ⎽⎺                                                             
    |               ⎯⎻                                                               
    |              ⎼                                                                 
    |            ⎽⎺                                                                  
    |          ⎯⎻                                                                    
    |         ⎼                                                                      
    |       ⎽⎺                                                                       
    |     ⎯⎻                                                                         
    |    ⎼                                                                           
    |  ⎽⎺                                                                            
    |⎯⎻                                                                              
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
  0%|                                                                                
    ⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺
    1                                                                              8

Efficiency graph:
125%|                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |⎯                                                                               
    | ⎻⎼⎽⎯                                                                           
    |     ⎺⎻⎼⎽⎯                                                                      
    |          ⎺⎻⎻⎼⎼⎼⎽⎽⎽⎯⎯⎯                                                          
    |                      ⎺⎻⎼⎽⎯                                                     
    |                           ⎺⎻⎼⎽⎯                                                
    |                                ⎺⎻⎼⎽                                            
    |                                    ⎺⎻⎽⎯                                        
    |                                        ⎻⎼⎯                                     
    |                                           ⎺⎻⎽⎯                                 
    |                                               ⎺⎼⎽⎯                             
    |                                                   ⎺⎻⎽⎯                         
    |                                                       ⎺⎻⎼⎽⎯                    
    |                                                            ⎺⎻⎼⎽⎯               
    |                                                                 ⎺⎻⎼⎽⎯          
    |                                                                      ⎺⎻⎻⎼⎽⎯    
    |                                                                            ⎺⎺⎻⎼
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
    |                                                                                
  0%|                                                                                
    ⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺⎺
    1                                                                              8
```
