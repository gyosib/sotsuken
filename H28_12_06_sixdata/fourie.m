#Main
disp("data:original data")
disp("smt: smoothed data")
disp("ffsmt: fourie data")
disp("when you want to plot fourie, write \"plot\(f,ffsmt\(1:N/2\)\)\"")
data = load("result_bb.dat");
smt = fastsmooth(data,50);
N = length(smt);
sortindex = randperm(N);
sort = smt(sortindex);
ffsmt = abs(fft(smt,N/2));
Fs = 5000; #sampling frequency
f = [(1:N/2)*(Fs/N)];
f_data = [(1:N)*(1/5000)];
#plot(f,ffsmt(1:N))
#save -text fourie.dat f ffsmt;
csvwrite('result_bb.csv',[f_data;smt.'].');
csvwrite('sort_bb.csv',[f_data;sort.'].');
