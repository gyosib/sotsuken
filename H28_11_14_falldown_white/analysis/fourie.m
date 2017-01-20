#Main
disp("data:original data")
disp("smt: smoothed data")
disp("ffsms: fourie data")
disp("when you want to plot fourie, write \"plot\(f,ffsmt\(1:N/2\)\)\"")
data = load("result0.dat");
smt = fastsmooth(data,50);
N = length(smt);
ffsmt = abs(fft(smt,N/2));
Fs = 5000; #sampling frequency
f = (1:N/2)*(Fs/N);
plot(f,ffsmt(1:N/2))
save -text fourie.dat ffsmt
