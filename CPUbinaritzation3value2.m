function [y] = CPUbinaritzation3value2(x,k)
m = mean(x, 'all');
[f, c] = size(x);
cf = round(f/2);
cc = round(c/2); 

B = x(cf, cc) > m + k; % es brillant
F = x(cf, cc) < m - k; % es fosc

y = int8(B) - int8(F); 
end
