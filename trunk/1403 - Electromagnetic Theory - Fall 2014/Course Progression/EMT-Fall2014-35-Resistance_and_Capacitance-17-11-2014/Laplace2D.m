clc
clear all

X=1.0;
Y=1.0;
dx=0.025;
dy=0.025;
I=X/dx+1
J=Y/dy+1
V=zeros(I,J);

V(:,1)=0;
V(1,:)=0;
V(I,:)=10;
V(:,J)=0;

for iterations=0:200
    for i=2:I-1
        for j=2:J-1
            V(i,j)=(V(i+1,j)+V(i-1,j)+V(i,j+1)+V(i,j-1))/4;
        end
    end
end

[x y] = meshgrid(0:dx:X,0:dy:Y);
[Ex,Ey] = gradient(V,dx,dy);
contour(x,y,V)
hold on
quiver(x,y,Ex,Ey)
hold off
