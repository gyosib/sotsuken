#3 average
function res = ave(in,n)
	res = sum(in(n-1:n+1))/3;
endfunction

#smooth
function res = fastsmooth(in,n)
	tmp(1:length(in)) = in(:);
	for i = 2:length(in)-1
		in(i) = ave(tmp,i);
	end
	res = in;
	if(n ~= 1)
		res = fastsmooth(in,n-1);
	end
endfunction

#Main
data = load("result0.dat");
smt = fastsmooth(data,50);
N = length(smt);
ffsms = fft(smt,N/2);
Fs = 5000; #sampling frequency
f = (1:N/2)*(Fs/N);
plot(f,ffsms)
