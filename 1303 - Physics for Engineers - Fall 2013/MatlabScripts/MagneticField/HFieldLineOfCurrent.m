function [H] = HFieldLineOfCurrent(r, r1, r2, I)
%HFIELDLINEOFCURRENT Calculate Magnetic field due to a line current.
%   Calculates magnetic field due to a finite straight current carrying wire.
% r : Observation point.
% r1: Starting location of wire.
% r2: Ending location of wire.
% I : Magnitude of current. Direction of current is from r1 to r2.
    cosalpha1=-1*dot(r-r1,r2-r1)/(norm(r-r1)*norm(r2-r1));
    cosalpha2=-1*dot(r-r2,r2-r1)/(norm(r-r2)*norm(r2-r1));
    rho=norm(cross(r-r1,r2-r1))/norm(r2-r1);
    phi=-1*cross(r-r1,r2-r1)/norm(cross(r-r1,r2-r1));
    H=I/(4*pi*rho)*(cosalpha2-cosalpha1)*phi;
end
