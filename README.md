# Simple Image Generator
This is a simple application made to generate bmp image.
This project was made in order for me to get used to the [cygwin](https://www.cygwin.com/) env and the use of [git](https://git-scm.com/)
Here is a list of params that can be used:
```bash
-o <filename> #To specify the image's name
-w <number> #To specify the image's width
-h <number> #To specify the image's height
-p <pattern> #To specify the pattern to use when generating the image
--number-of-points <number> #Pattern specific, only matters when using patterns such as point
--seed <number> #To specify the seed to use when doing pattern calculations
--channel <channel> #To specify the color channel to use when drawing the pattern
--transparent #To specify that we want the pattern to use transparency
--thickness <number> #Pattern specifc, only matters when using patterns sush as linemess
```