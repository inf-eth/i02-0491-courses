% E-field of a point charge.
%range = [-2 -1.8 -1.6 -1.4 -1.2 -1.0 -0.8 -0.6 -0.4 -0.2 -0.1 0.1  0.2 0.4 0.6 0.8 1.0 1.2 1.4 1.6 1.8 2.0];
startx = 0:0.02:0.25;
starty = sqrt(0.25^2-startx.^2);

[x,y] = meshgrid(-2:0.2:2);
Ex = x./(x.^2+y.^2).^(1.5);
Ey = y./(x.^2+y.^2).^(1.5);


quiver(x,y,Ex,Ey)
hold on
streamline(x,y,Ex,Ey,startx,starty)
streamline(x,y,Ex,Ey,-startx,starty)
streamline(x,y,Ex,Ey,-startx,-starty)
streamline(x,y,Ex,Ey,startx,-starty)