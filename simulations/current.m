function i = current(t)
i = 2 * (t < 0.5) - 1; % square signal
f = 12; % relative frequency
A = (0.5 - t) .* (t < 0.5) - (1 - t) .* (t >= 0.5); % sine signal amplitude, larger near edges 
i = i + A .* sin(2*pi*t*f); % square + sine
n = 0.1 * randn(1, length(t)); % white noise
i = i + n; % square + sine + noise
R = rand(1, length(t)) < 0.15 - rand(1, length(t)) > 0.9; % random peaks
r = R .* randn(1, length(t)); % random amplitude for random peaks
i = i + R; % result
end