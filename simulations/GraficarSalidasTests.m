clear all;
close all;
clc;

zn = dlmread("../build/ZieglerNichols.csv", ",", 1, 0);
testControlPID = dlmread("../build/DutWillStabilizeAt900DegreesWithPIDControl.csv", ",", 1, 0);
testControlProporcional = dlmread("../build/DutWillStabilizeAt900DegreesWithProportionalControl.csv", ",", 1, 0);
testControlPIDTempAlta = dlmread("../build/DutWithHighTemperature.csv", ",", 1, 0);
testControlFuzzy2x3 = dlmread("../build/Fuzzy2x3Control.csv", ",", 1, 0);
testControlFuzzy3x1 = dlmread("../build/Fuzzy2x1Control.csv", ",", 1, 0);

figure(1)
x = 1:length(zn(:,1));
plotyy(x, zn(:,1), x, zn(:,2))

figure(4)
plot(testControlPID(:, 2), '.');
title("Control PID: temperatura");
grid minor

figure(3)
plot(testControlPID(:, 1), '.')
title("Control PID: potencia");
grid minor

figure(5)
plot(testControlProporcional(:, 1))
title("Control proporcional: potencia");
grid minor

figure(6)
plot(testControlProporcional(:, 2));
title("Control proporcional: temperatura");
grid minor


figure(7)
plot(testControlPIDTempAlta(:, 1))
title("Control PID temperatura inicial alta:  potencia");
grid minor

figure(8)
plot(testControlPIDTempAlta(:, 2));
title("Control PID temperatura inicial alta: temperatura");
grid minor

figure(9)
plot(testControlFuzzy2x3(:, 1))
title("Control Fuzzy 2x3:  potencia");
grid minor

figure(10)
plot(testControlFuzzy2x3(:, 2));
title("Control Fuzzy 2x3: temperatura");
grid minor

figure(11)
plot(testControlFuzzy3x1(:, 1))
title("Control Fuzzy 3x1:  potencia");
grid minor

figure(12)
plot(testControlFuzzy3x1(:, 2));
title("Control Fuzzy 3x1: temperatura");
grid minor