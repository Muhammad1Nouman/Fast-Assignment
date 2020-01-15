[p,map1]=imread('Audrey.jpg');
[z,map2] = imread('Frame.jpg');

x=[0,0,499,499];
y=[0,507,0,507];

x2=[187,184,346,345];
y2=[153,464,176,433];

for  i=1:4
     A(2*i-1,:)=  [x(i),y(i),1,0,0,0 ,-x(i)*x2(i),-x2(i)*y(i),-x2(i)];
     A(2*i,:) =   [0,0,0,x(i),y(i),1,-x(i)*y2(i),-y2(i)*y(i),-y2(i)];
end;
[U,S,V]=svd(A);
h=V(:,9);
h1=reshape(h,3,3);

g=projective2d(h1);
finalW=imwarp(p,g);

for j=1:160
    for k=1:312
        pix=finalW(k,j,:);
        if pix>0
           z(k+155,j+188,:)=pix;
        end 
    end
end
imshow(z)

