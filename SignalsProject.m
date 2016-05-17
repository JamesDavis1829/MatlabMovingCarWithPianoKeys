tolerance = 10;
time = 1;

%ascii to send to the car%

front = char(102);
r = char(114);
l = char(108);
b = char(98);
s = char(115);

fs = 8000;
load('A4.mat');
load('B4.mat');
load('C4.mat');
load('D4.mat');
load('E4.mat');
load('F4.mat');
load('G4.mat');
load('f.mat');
recObj = audiorecorder();
t = tcpip('192.168.0.9',23);
fopen(t);

while(1)
    disp('Start Speaking');
    recordblocking(recObj,time);
    disp('End of recording');
    recording = getaudiodata(recObj);

    samples = length(recording);

    recFFT = abs(fft(recording));
    recFFT = recFFT(1:samples/2);

    f = fs*(0:samples/2-1)/samples;
    
    plot(f,recFFT);
    xlim([0,1000]);
    ylim([0,30]);

    [rec, idRec] = max(recFFT);

    %check for A4
    [~, idTemp] = max(A4);
    if(abs(idTemp - idRec) <= 10)
        disp('The note is A4');
    end

    [~, idTemp] = max(B4);
    if(abs(fData(idTemp) - f(idRec)) <= tolerance)
        disp('The note is B4');
    end

    [~, idTemp] = max(C4);
    if(abs(fData(idTemp) - f(idRec)) <= tolerance)
        disp('The note is C4');
        fwrite(t,front);
    end

    [~, idTemp] = max(D4);
    if(abs(fData(idTemp) - f(idRec)) <= tolerance)
        disp('The note is D4');
        fwrite(t,l);
    end

    [~, idTemp] = max(E4);
    if(abs(fData(idTemp) - f(idRec)) <= tolerance)
        disp('The note is E4');
        fwrite(t,r);
    end

    [~, idTemp] = max(F4);
    if(abs(fData(idTemp) - f(idRec)) <= tolerance)
        disp('The note is F4');
        fwrite(t,b);
    end

    [~, idTemp] = max(G4);
    if(abs(fData(idTemp) - f(idRec)) <= tolerance)
        disp('The note is G4');
        fwrite(t,s);
    end
end


