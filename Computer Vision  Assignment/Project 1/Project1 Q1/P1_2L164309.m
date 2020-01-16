line=imread('Lines.png');
filter=[-2 -1 0;-1 0 1;0 1 2];
filter=filter/8;
convoult=imfilter(line,filter);
max(max(convoult));
th=convoult>=126 & convoult<=127;
imshow(th);