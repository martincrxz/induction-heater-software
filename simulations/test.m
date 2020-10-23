clc;
clear all;
close all;

N = 1000;

t0 = 2000; % temperatura ambiente, incial de la pieza
T = [t0]; % vector de temperaturas
sp = 900; % temperatura objetivo, set point
E = [sp-t0]; % vector de error de temperatura
p = 0; % potencia instantanea
P = [p]; % vector de potencias

T = [T heating_process(T(end),1)];
E = [E T(end)-sp];
P = [P 1];

Kp = 15;
Ki = 0.1;
Kd = 0.1;

for i = 1 : N

	e = E(end);
	e_i = sum(E);
	e_d = e - E(end-1);

	% aca habria que meter un codigo que calcule los Ks a partir de algun algoritmoa
	%
	%

	p = Kp * e + Ki * e_i + Kd * e_d; % accion del pid
	p = 0.1 * (p < 0.1) + p * (p >= 0.1) * (p < 1) + 1 * (p >= 1); % saturacion del actuador

	n = 5*randn(1); % simula un ruido de medicion

	T = [T heating_process(T(end),p)];
	E = [E sp-T(end)+n];
	P = [P p];

end

figure()
hold on;
plot(T,'b');
plot(E,'r');
grid on;
xlim([0 N])


