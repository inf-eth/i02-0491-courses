% Field Plot
xMinRange=-2;
yMinRange=-2;
xMaxRange=2;
yMaxRange=2;
dx=0.5;
dy=0.5;
[x y] = meshgrid(xMinRange:dx:xMaxRange,yMinRange:dy:yMaxRange);
Ex = y;
Ey = y.^2.*x;

quiver(x, y, Ex, Ey)
hold on
grid on
startx=xMinRange:dx:0;
starty=yMaxRange*ones(1,length(startx));
streamline(x,y,Ex,Ey,startx,starty)
startx=0:dx:xMaxRange;
starty=yMinRange*ones(1,length(startx));
streamline(x,y,Ex,Ey,startx,starty)
starty=yMinRange:dy:0;
startx=xMaxRange*ones(1,length(starty));
streamline(x,y,Ex,Ey,startx,starty)
starty=0:dy:yMaxRange;
startx=xMinRange*ones(1,length(starty));
streamline(x,y,Ex,Ey,startx,starty)