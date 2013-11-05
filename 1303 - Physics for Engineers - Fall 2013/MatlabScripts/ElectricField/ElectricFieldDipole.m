% Electric field of dipole.
xMinRange=-2;
yMinRange=-2;
xMaxRange=2;
yMaxRange=2;
dx=0.125;
dy=0.125;
[x y] = meshgrid(xMinRange:dx:xMaxRange,yMinRange:dy:yMaxRange);

rp = [-0.5 0];
rn = [0.5 0];
r = [x y];
qp = 1e-9;
qn = -1e-9;
e0 = (1e-9)/(36*pi);
Epx = qp/(4*pi*e0)*(x-rp(1))./((x-rp(1)).^2+(y-rp(2)).^2).^3;
Epy = qp/(4*pi*e0)*(y-rp(2))./((x-rp(1)).^2+(y-rp(2)).^2).^3;

Enx = qn/(4*pi*e0)*(x-rn(1))./((x-rn(1)).^2+(y-rn(2)).^2).^3;
Eny = qn/(4*pi*e0)*(y-rn(2))./((x-rn(1)).^2+(y-rn(2)).^2).^3;

quiver(x,y,Epx+Enx,Epy+Eny)