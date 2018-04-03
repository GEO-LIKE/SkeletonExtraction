# SkeletonExtraction
Extract the skeleton of an binary image

### Environment configuration
- vs2015
- openCV 3.4.1

### Basic concepts

![Structure Element B](https://github.com/GEO-LIKE/SkeletonExtraction/raw/master/images/concept1.jpg)

Sequential thinning by use structuring element L

![Structure Element L](https://github.com/GEO-LIKE/SkeletonExtraction/raw/master/images/concept.jpg)

### Utilizing <code>GenerateMat</code> to produce the following image：

![Initial Shapes](https://github.com/GEO-LIKE/SkeletonExtraction/raw/master/images/result0.jpg)

### Extract skeleton by <code>thinning</code>：

![Skeleton](https://github.com/GEO-LIKE/SkeletonExtraction/raw/master/images/result50.jpg)

#### Reference
[1] Image Processing, Analysis, and Machine Vision, Fourth Edition, Milan Sonka, Vaclav Hlavac, Roger Boyle, CENGAGE Learning.

[2] Digital Image Processing, Third Edition, Rafael C. Gonzalez, Richard E. Woods, Pearson.