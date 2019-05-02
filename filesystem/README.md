# The filesystem support library. Example of usage.
Working with filesystem paths is always tedious if we don't have a library that helps us because there are many conditions that we need to handle.  
Some paths are absolute, some are relative, and maybe they are not even straightforward because they also contain `.` (current directory) and `..` (parent directory) indirections.
Then, at the same time, different operating systems use the slash `/ `to separate directories (Linux, MacOS, and different UNIX derivatives), or the backslash `\` (Windows).
And of course there are different types of files.  
It is great to have the new [filesystem library](https://en.cppreference.com/w/cpp/filesystem) in the C++17 STL.
The best thing about it is that it works the same way for different operating systems, so we don't have to write different code for versions of our programs that support different operating systems.  
An example here is aimed to demonstrate how task 'listening all files in directories' can be implemented.  
Of course, every operating system that offers filesystem support also comes with some kind of utility that does just list all files within a directory in the filesystem.
The simplest examples are the `ls` command on Linux, MacOS, and other UNIX-related operating systems.
In DOS and Windows, there is the `dir` command.
Both list all files in a directory and provide supplemental information such as file size, permissions, and so on.  
Reimplementing such a tool is, however, also a nice standard task to get going with directory and file traversal. It's a good way to get a knowledge from the practice. 

## Further informations
* [`std::filesystem`](https://en.cppreference.com/w/cpp/filesystem)
* [How to Iterate Through Directories in C++](https://www.bfilipek.com/2019/04/dir-iterate.html) by Bartlomiej Filipek

## Related links
* TBD

## Compilers
* [GCC 8.1.0](https://wandbox.org/)
* [clang 6.0.0](https://wandbox.org/)
* Visual C++ 19.14 
