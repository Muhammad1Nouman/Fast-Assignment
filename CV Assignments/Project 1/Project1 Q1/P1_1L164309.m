Imag=imread('cameraman.tif');
[mag dirX]=imgradient(Imag);
imagesc(dirX);
colormap(gray);
colorbar;
