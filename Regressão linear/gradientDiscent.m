function a = gradientDiscent(data)
    x = data(:, 1);
    y = data(:, 2);

    plot(x, y, 'rx');
    hold on;

    x = [ones(length(x),1) x];
    a = zeros(2,1);

    for i = 1:1500
        a = a - 0.01*gradient(x, y, a);
    end
    
    xregression = min(x(:, 2)):0.01:max(x(:, 2));
    yregression = [ones(length(xregression), 1) xregression']*a;

    plot (xregression, yregression);
end