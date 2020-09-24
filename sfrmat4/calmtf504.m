function [mtf50] = calmtf504(mtf,freq)
%function [mtf50] = calmtf50(mtf,freq) 计算mtf50点的频率
%mtf50 value
%三角形相似计算mtf50值
%wei chun  2020 8. 27.





%mtf4
len = size(freq);
for i = 1:len
    if mtf(i,4) == 0.5
        mtf50 = freq(i,4);    % 当某一归一化下mtf为0.5，返回该值
        return;
    elseif mtf(i,4) <0.5        %当第一个点就小于0.5时，break，运行下一步
        break;
    end
end


if i==1              %mtf=0返回
    mtf50 = 0;
    return;
end


%三角形相似，求出mtf50点
a = freq(i-1);
b = freq(i);
da = abs(mtf(i-1,4)-0.5);
db = abs(mtf(i,4)-0.5);
mtf50 = (da*b+db*a)/(da+db);
end