[p,map1]=imread('White knight.jpg');
[z,map2] = imread('FAST_lhr.jpg');

x=[0,0,182,182];
y=[0,276,0,276];
p=p+1;
x2=[706,709,871,874];
y2=[150,331,133,325];

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
for j=1:165
   for k=1:196
        pix=finalW(k,j,:);
        if pix>0
           z(k+134,j+707,:)=pix;
        end 
    end
end
imshow(z)

