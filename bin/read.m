clc;clear all;close all;


fid=fopen('writeout.txt','r')


A=textscan(fid,'%f %f %f %f %f %f')

yyaxis left
plot(A{1},[A{2},A{3},A{4},A{5}])
hold on
yyaxis right
plot(A{1},[A{6}])