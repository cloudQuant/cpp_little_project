This hash function should return the least-significant three decimal digits 
(a number from 0 to 999) of the variable value. 

when solve this homework, I used the hash function `value%999`, in fact ,it needs to be `value%1000`, 
I don't consider the 0%999 equals 999%999