clear all;
close all;
clc;

SAMPLE_RATE = 1e6; % 1 M/s
FREQUENCY = 2.2e4; % 22 kHz
MILLISECOND = 1e-3;
MICROSECOND = 1e-6;
JITTER_FACTOR = 0.2;
NOISE_FACTOR = 0.8;
L = 512;

t = linspace(0, L/SAMPLE_RATE, L);

T = 1/FREQUENCY;

i = 2 * (mod(t, T) < T/2*(1+JITTER_FACTOR*randn(1,L))) - 1;
i = i + NOISE_FACTOR * randn(1, L);

I = fft(i);
P2 = abs(I/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f = SAMPLE_RATE*(0:(L/2))/L;

figure();
hold on;
grid on;
xlabel('Time [s]');
ylabel('Current [A]');
xlim([0 L/SAMPLE_RATE]);
ylim([min(i)-0.1 max(i)+0.1])
plot(t,i);

figure();
hold on;
grid on;
xlabel('Frequency [kHz]');
ylabel('Current [A]');
xlim([0 88]);
plot(f*1e-3,P1);