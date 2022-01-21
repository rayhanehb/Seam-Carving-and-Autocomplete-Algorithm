# ESC190
ESC190 Projects
## Autocomplete.c
A fast implementation of the autocomplete functionality.You will work with files that contain a large number of terms, along with the importance weight associated with those terms. The autocomplete task is to quickly retrieve the top terms that match a query string. For example, ifthe query string is "Eng", you matches might be "English","Engineering", and "EngSci".To accomplish the task:

* Read in the entire file of terms, and sort the terms in lexicographic ordering. This sorted list will be reused for multiple queries.

* Use binary search to find the location of the first term in lexicographic ordering that matches thequery string, as well as the last term in lexicographic oredering that matches the query string.

* Extract the terms that match the query string, and sort them by weight.

* Extract the top matching terms by weight

## Seamcarving.c
Seam-carving is a content-aware image resizing technique where the image is reduced in size by one pixel of height (or width) at a time. A vertical seam in an image is a path of pixels connected from the top to the bottom with one pixel in each row; a horizontal seam is a path of pixels connected from the left to the right with one pixel in each column. Below left is the original 505-by-287 pixel image; below right is the result after removing 150 vertical seams, resulting in a 30% narrower image. Unlike standard content-agnostic resizing techniques (such as cropping and scaling), seam carving preserves the most interest features (aspect ratio, set of objects present, etc.) of the image.

The underlying algorithm is simple and elegant, but the technique was not discovered until 2007 by Shai Avidan and Ariel Shamir. Now, it is a core feature in Adobe Photoshop (thanks to a Princeton graduate student) and other computer graphics applications. In this assignment, a data type is created that resizes a W-by-H image using the seam-carving technique. Finding and removing a seam involves three parts and a tiny bit of notation: 

* energy calculation
* seam identification
* seam removal
