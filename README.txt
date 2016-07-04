The algorithm of this program is pretty simple - it looks for the first 
appearance of the #ifndef in the .h(pp) files or #include in the .cpp files,
ERASES EVERYTHING before those lines and inserts the license information
from a given file instead. The program will not change those files that do not
contain the key-lines mentioned above (#ifndef for .h(pp), and #include for
.cpp files). 

