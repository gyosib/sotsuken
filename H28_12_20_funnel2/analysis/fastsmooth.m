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
