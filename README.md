# Pattern Recognition App
Back in 2006, when PyTorch and TensorFlow weren’t around, me and my lab-mates had to write our own code to perform pattern recognition tasks (data analysis method that uses machine learning), so we could do our research and, eventually, get our Ph.D. degrees!

Since there weren’t any reference implementations around, we validated our code by running the same datasets, in each implementation, and expect similar results. That’s pretty much how we were sure that our code actually worked!

Digging through old folders, I found my implementation, written entirely in C++ (most people preferred matlab). The code was used to produce the results appearing in all my Ph.D.-related publications.

The project is essentially a collection of unsupervised and supervised classification techniques (LD, kNN, PNN, SVM, etc.). There’s also code for textural feature calculation (GLCM, GLRLM, etc.), reduction (PCA, etc.), and selection (ES, etc.). Finally, there are performance evaluation methods (SC, LOO, ECV, etc.), as well as an effort to create a framework that would combine classification techniques into ensemble schemes (pretty cool idea at that time!).

Long story short (5 years long!), publications were accepted in scientific journals, and I got my Ph.D., all because of this code (and the invaluable help of pretty smart people that I now have the honor to call friends)!

Here it is: [Computer assisted diagnosis of brain tumors based on statistical methods and pattern recognition techniques][phd-url].

### Disclaimer
The code was written using Visual Studio 6.0 and I’m not even sure whether it compiles on a modern IDE!

### License
Pattern Recognition App is released under the MIT License.

[phd-url]: https://nemertes.library.upatras.gr/jspui/handle/10889/4012?locale=en
