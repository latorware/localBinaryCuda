function [y] = CPUbinaritzation3values()
I = rgb2gray(imread('tiger.jpg')); 
y = blkproc(I, [1, 1], [50, 50], @CPUbinaritzation3value2, 16);  
end
