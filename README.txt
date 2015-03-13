The algorithm of this program is pretty simple - it looks for the first 
appearance of the #ifndef in the .h(pp) files or #include in the .cpp files,
ERASE EVERYTHING before those lines and insert the license information
from a given file instead. Therefore, please be aware that if your header
files content is not surrounded by the #ifndef-#define-#endif macros (which is
a good practice), the program may erase the whole file. The same is applicable
to the source files that do not begin with the #include. If you have, for
example, important comments before the first appearance of the mentioned lines,
please do not use this program as those comments will be lost.

