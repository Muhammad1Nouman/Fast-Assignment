clear
imagefiles = dir('E:\semester 6\Computer Vision\Project 2(a)\faces\*.png');      
nfiles = length(imagefiles);    % Number of files found

for ii=1:nfiles
   currentfilename = imagefiles(ii).name;
   currentimage = imread(currentfilename);
   reshapedImage=reshape(currentimage,2500,1);
   A(:,ii) = reshapedImage;
end
for p=1:2500
    MeanOfX(p,:)=mean(A(p,:));
end

R=zeros(2500,2500);

for l=1:640
    matrix1=(A(:,l));
    x(:,l)=double(matrix1)-double(MeanOfX);
end

G=x*transpose(x);
R=G/639; %% Number of images-1


[U,S,V]=svd(R);



D=U(1:2500,1:100);
D16=zeros(2500,1);
g=1;
for i=1:4
    E2=transpose(D);
    MeanMatrix=double(A(:,g))-double(MeanOfX);
    y1=E2*MeanMatrix;
    D10=D*y1;
    D11=double(D10)+double(MeanOfX);
    D12=reshape(D11,50,50);
    D12=D12/255;
    subplot(1,4,i), imshow(D12)
    g=g+64;
   
end


