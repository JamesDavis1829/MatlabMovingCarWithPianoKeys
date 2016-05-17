fs = 8000;
recObj = audiorecorder();
disp('Start Speaking');
recordblocking(recObj,1);
disp('End of recording');
recording = getaudiodata(recObj);

samples = length(recording);

recFFT = abs(fft(recording));
recFFT = recFFT(1:samples/2);

f = fs*(0:samples/2-1)/samples;