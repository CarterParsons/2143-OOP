Program 3 — Image Filter Pipeline
Overview

This program applies a sequence of image filters using a pipeline structure. Each filter is implemented using the Strategy design pattern, where every filter inherits from a common Filter interface. Filters are applied in the order they are provided through command-line arguments.

The pipeline supports chaining multiple operations such as grayscale conversion, brightness adjustment, flipping, rotation, and blur.

Grayscale Implementation Choice

I chose the luminance-based grayscale formula:

gray = 0.299 * R + 0.587 * G + 0.114 * B
Why this formula:

This method produces a more visually accurate grayscale image because it weights colors based on human perception. The human eye is more sensitive to green and less sensitive to blue, so this approach preserves brightness better than a simple average.

Example Commands
1. Single filter
./imgtool images/Hulda.jpg out.png --grayscale
2. Brighten then grayscale
./imgtool images/Hulda.jpg out.png --brighten 50 --grayscale
3. Grayscale then brighten (different result than above)
./imgtool images/Hulda.jpg out.png --grayscale --brighten 50
4. Full pipeline with multiple filters
./imgtool images/Hulda.jpg out.png --grayscale --brighten 30 --blur --flipH
5. Rotation example
./imgtool images/Hulda.jpg out.png --rotate 90
Filter Ordering Demonstration
Order A:
./imgtool images/Hulda.jpg out.png --brighten 40 --grayscale
Order B:
./imgtool images/Hulda.jpg out.png --grayscale --brighten 40

These produce different intermediate results because each filter modifies the image in-place and order affects the final output.

Notes
All filters operate in-place on the image grid.
The pipeline executes filters in the exact order provided in args.order.
Rotation may change image dimensions depending on angle (90° / 270°).
