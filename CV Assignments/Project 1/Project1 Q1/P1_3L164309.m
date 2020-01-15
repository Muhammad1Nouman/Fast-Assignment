
Imag=imread('cameraman.tif');
f=[1, 0, -1];
p=imfilter(Imag,f);
imshow(p);