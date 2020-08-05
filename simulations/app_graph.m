% Este script genera las imagenes de potencia estacionaria, potencia minima
% y temperatura de corte que se ven como ayuda en la aplicación principal
clear all;
close all;
x = 1:1000;
yestacionario = (1-exp(-x/100)) * 50;

figure(1)
plot(x, yestacionario);
line ([0 1000], [50 50], "color", "k", "linewidth", 3, "linestyle", "-.");
grid on;
axis([0, 1000, 0, 100]);
ylabel("Potencia (%)");
text (300, 57, ['Potencia Estacionaria']);
print("-S1200,800", "potenciaEstacionaria.png");
print("-S240,180", "potenciaEstacionariaChica.png");

figure(2)
yminimo = ones(size(x)) * 30;
yminimo(301:1000) += yestacionario(1:700);
plot(x, yminimo);
line ([150 150], [0 30], "color", "k", "linewidth", 3, "linestyle", "-.");
hold on;
grid on;
axis([0, 1000, 0, 100]);
ylabel("Potencia (%)");
text (200, 15, ['Potencia Minima']);
print("-S1200,800", "potenciaMinima.png");
print("-S240,180", "potenciaMinimaChica.png");

figure(3)
ycorte = (1-exp(-x/100)) * 400;
ycorte(400:1000) = -0.4 * (x(400:1000) - 400) + ycorte(400);
plot(x, ycorte);
line([0 1000], [ycorte(400) ycorte(400)], "color", "k", "linewidth", 3, "linestyle", "-.");
hold on;
grid on;
axis([0, 1000, 0, 500]);
ylabel("Temperatura (°C)")
text (500, 450, ['Temperatura de corte']);
print("-S1200,800", "temperaturaCorte.png");
print("-S240,180", "temperaturaCorteChica.png");