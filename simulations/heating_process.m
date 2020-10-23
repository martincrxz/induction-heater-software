%% heating_process: open loop response approximation of the induction heating process
function out = heating_process(t0,p)
	persistent p0;

	% para cambiar el comportamiento de la funcion se pueden
	% modificar estos parametros:
	Tc = 700;
	A = 0.01;
	B = 0.002;
	C = 0.5;

	% A y B no tienen significado fisico pero dan la pendiente incial antes
	% y despues de Tc

	% C se puede usar para modificar la "inercia" de temperatura

	if isempty(p0)
		% este polinomio da la funcion maxima dada una potencia,
		% se podria usar cualquier otra funcion
		t1 = 1111.1 * p * p + 972.22 * p - 83.333;
		p0 = p;
	else
		p1 = (p + C * (p0 - p));
		t1 = 1111.1 * p1 * p1 + 972.22 * p1 - 83.333;
		p0 = p1;
 	end
 	out = (t1-t0)*(A*(t0<Tc)+B*(t0>Tc))+t0;
