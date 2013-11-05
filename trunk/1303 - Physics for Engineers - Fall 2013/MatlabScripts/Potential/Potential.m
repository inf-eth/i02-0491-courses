function [V] = Potential(r, rp, q)
%POTENTIAL Calculates absolute potential of a point charge
% r : Observation point
% rp: Source point
% q : Value of charge
    e0 = (1e-9)/(36*pi);
    V = q/(4*pi*e0)/norm(r-rp);
end

