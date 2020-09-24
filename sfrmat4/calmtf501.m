function [mtf50] = calmtf501(mtf,freq)
%function [mtf50] = calmtf50(mtf,freq) ����mtf50���Ƶ��
%mtf50 value
%���������Ƽ���mtf50ֵ
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