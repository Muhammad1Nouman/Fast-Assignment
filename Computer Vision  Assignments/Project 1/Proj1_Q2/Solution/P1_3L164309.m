[p,map1]=imread('Nelson.jpg');
[z,map2] = imread('DuFrame.jpg');

x=[0,0,768,768];
y=[0,432,0,432];

x2=[129,128,377,382];
y2=[100,498,100,500];

for  i=1:4
     A(2*i-1,:)=  [x(i),y(i),1,0,0,0 ,-x(i)*x2(i),-x2(i)*y(i),-x2(i)];
     A(2*i,:) =   [0,0,0,x(i),y(i),1,-x(i)*y2(i),-y2(i)*y(i),-y2(i)];
end;
[U,S,V]=svd(A);
h=V(:,9);
h1=reshape(h,3,3);

g=projective2d(h1);
finalW=imwarp(p,g);
imagesc(finalW)
for j=1:250
   for k=1:400
        pix=finalW(k,j,:);
        if pix>0
           z(k+105,j+128,:)=pix;
        end 
    end
end
imshow(z)

