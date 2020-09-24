function [mtf50] = calmtf504(mtf,freq)
%function [mtf50] = calmtf50(mtf,freq) ����mtf50���Ƶ��
%mtf50 value
%���������Ƽ���mtf50ֵ
%wei chun  2020 8. 27.





%mtf4
len = size(freq);
for i = 1:len
    if mtf(i,4) == 0.5
        mtf50 = freq(i,4);    % ��ĳһ��һ����mtfΪ0.5�����ظ�ֵ
        return;
    elseif mtf(i,4) <0.5        %����һ�����С��0.5ʱ��break��������һ��
        break;
    end
end


if i==1              %mtf=0����
    mtf50 = 0;
    return;
end


%���������ƣ����mtf50��
a = freq(i-1);
b = freq(i);
da = abs(mtf(i-1,4)-0.5);
db = abs(mtf(i,4)-0.5);
mtf50 = (da*b+db*a)/(da+db);
end