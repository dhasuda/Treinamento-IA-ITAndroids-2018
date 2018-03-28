function G = gradient(x, y, a)
    
    G = x*a-y;
    G = G'*x(:,2);
    G = G/length(x);

end