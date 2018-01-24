% 1-21-2018 Checks if C++ program read the values correctly

close all;
clc;
clear

fileID = fopen('output.txt','r');
formatSpec = '%f %f';
sizeA = [2 Inf];
audio_file_contents_C = fscanf(fileID,formatSpec,sizeA);
audio_file_contents_C = audio_file_contents_C';

filename = './sweep.wav';
[audio_file_contents_Matlab, Fs] = audioread(filename);

% For some reason the matlab file is longer??? Are we skipping samples in
% C++ program?
[num_frames, num_channels] = size(audio_file_contents_C);

audio_file_contents_Matlab = audio_file_contents_Matlab(1:num_frames,:);
