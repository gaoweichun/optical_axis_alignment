function [mtf50] = calmtf501(mtf,freq)
%function [mtf50] = calmtf50(mtf,freq) 计算mtf50点的频率
%mtf50 value
%三角形相似计算mtf50值
%wei chun  2020 8. 27.


%%%%mtf1
len = size(freq);
for i = 1:len
    if mtf(i,1) == 0.5
        mtf50 = freq(i,1);
        return;
    elseif mtf(i,1) <0.5
        break;
    end
end


if i==1
    mtf50 = 0;
    return;
end
a = freq(i-1);
b = freq(i);
da = abs(mtf(i-1,1)-0.5);
db = abs(mtf(i,1)-0.5);
mtf50 = (da*b+db*a)/(da+db);


end