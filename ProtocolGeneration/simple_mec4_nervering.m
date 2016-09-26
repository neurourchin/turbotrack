%% Notes
% Tip of HEAD is (0, 0). 
% Tail is (99,0)
%
% 
% Pictorially:
%      (-10,0)  (0,0)  (10,0)
%             Head
%                ^ 
%              /  \
%             /    \
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             |    |
%             \    /
%              \  /
%               \/
%             Tail  
%        (-10,99)  (0,99)  (10,99)
%
%
%    y
%    ^
%    |     (axis)
%    |
%    ------------> x
%
% Note also, you can walk off the worm in x (but not in y).
% Note too that x here is different from the convention used in the GUI.
% The silly sliders that I use in the GUI for on-the-fly illumination 
% can't do negative numbers. So x=0 on the GUI is actually x=-10 here. 
% And x=10 on the GUI is actualy x=0 here.

clear all; close all;


% Header informatoin
filename='simple_mec4_nervering.yml';
gridHeight=100;
gridWidth=21; %must be odd
%Note: No carriage return at the end of the description
description= sprintf('Illuminate (ALM & AVM) or nerve ring, or entire posterior.');




%Index notation
X=1; Y=2;

%Defualt Radii
dRadFullWorm=10;
dRad(X)=6;
dRad(Y)=4;

  


%We have to convert from the slider bar manual illumination coordinate convention
%To the protocol illumiantion convention.
annoyingXOffset=-10;
%Neuron centroid & radii
AVM(X)=13+annoyingXOffset;
AVM(Y)=34;

ALM(X)=annoyingXOffset+7;
ALM(Y)=42

PVM(X)=annoyingXOffset+11;
PVM(Y)=66;

PLM(X)=annoyingXOffset+12;
PLM(Y)=90;

AFD(X)=10+annoyingXOffset;
AFD(Y)=11;

%predefine protocol
protocol=cell(0);

% Protocol = [x1, y1, x2,y2, x3,y3, x4,y4]
% This can be generated using the rect(x1,y1,x4,y4) function if the
% rectangle lies on a grid


%Entire Anterior
protocol{end+1}=rect(-10, 52,  10, 0 );

%AVM + ALM
protocol{end+1}=rect(-10, 52, 10,30);

%Nerve Ring
protocol{end+1}=rect(-10, 7, 10,15);


%ALM
protocol{end+1}=rect(ALM(X)-dRad(X), ALM(Y)-dRad(Y), ALM(X)+dRad(X), ALM(Y)+dRad(Y) );

%PVM
protocol{end+1}=rect(PVM(X)-dRad(X), PVM(Y)-dRad(Y), PVM(X)+dRad(X), PVM(Y)+dRad(Y) );

%PLM
protocol{end+1}=rect(PLM(X)-dRad(X), PLM(Y)-dRad(Y), PLM(X)+dRad(X), PLM(Y)+dRad(Y) );



writeProto(filename,description,gridWidth,gridHeight,protocol)

figure;
for n=1:length(protocol)
plotProtocol(protocol{n},gridHeight,gridWidth)
pause
end


