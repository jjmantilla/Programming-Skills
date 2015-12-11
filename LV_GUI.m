
function varargout = GUICS(varargin)
% GUICS M-file for GUICS.fig
%      GUICS, by itself, creates a new GUICS or raises the existing
%      singleton*.
%
%      H = GUICS returns the handle to a new GUICS or the handle to
%      the existing singleton*.
%
%      GUICS('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUICS.M with the given input arguments.
%
%      GUICS('Property','Value',...) creates a new GUICS or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before GUICS_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to GUICS_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help GUICS

% Last Modified by GUIDE v2.5 23-Jan-2014 14:19:13

% Begin initialization code - DO NOT EDIT



% To inizialize the GUI setpath contourlet, curvelet, wavelab and the path of the
% data in the file coupe.m. In the section mostrar, set the path to save
% the profiles (radial or diametral and the basal, medial and apical planes)


global ls;
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUICS_OpeningFcn, ...
                   'gui_OutputFcn',  @GUICS_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before GUICS is made visible.
function GUICS_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to GUICS (see VARARGIN)

% Choose default command line output for GUICS
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

initialize(handles,1,1,1);

% UIWAIT makes GUICS wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = GUICS_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
global xP;
xP=get(hObject,'Value');
y=1;
z=1;
initialize(handles,xP,y,z);

% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1


% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
global xP;
yP=get(hObject,'Value');
z=1;
initialize(handles,xP,yP,z);

% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2


% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu3.
function popupmenu3_Callback(hObject, eventdata, handles)



% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu3 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu3


% --- Executes during object creation, after setting all properties.
function popupmenu3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
global Im;  
global t;
t=get(hObject,'Value');
g=get(hObject,'Max');
t=g-round(t)+1;

axes(handles.axes1);
imshow(abs(Im(:,:,t)),[])

% global h;
% r=getPosition(h)
% h = imrect(gca, [90 80 89 89]);
% addNewPositionCallback(h,@(p1) title(mat2str(p1,3)));
% fcn = makeConstrainToRectFcn('imrect',get(gca,'XLim'),get(gca,'YLim'));
% setPositionConstraintFcn(h,fcn);
global proc;
if (proc==1)
    set(handles.slider2,'Value',t); 
    mostrar2(handles);
    val=get(handles.popupmenu4,'Value');
    temporal(val,handles);
    transformadas(handles);
end
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
global proc;
proc=0;
global hor;
global ins;
global bd;
global mr;
mr=0;
hor=10;
bd=1;
pax=1;
plane=5;
bd=get(handles.popupmenu1,'Value');
pax=get(handles.popupmenu2,'Value');
plane=get(handles.popupmenu3,'Value');
[ic fc p a cr pac ins]=coupe(bd,pax,plane);
addpath(p);
sizeSl=[256 256]; 
% initial counter of images, example: IMic
% final counter of images, example: IMfc
%length of series
if(bd==1)
    a=a-1;
end
global ls;
ls=fc-ic+1;  
%ls=20;
slider_step(1) = 1/(ls);
slider_step(2) = 1/(ls);
set(handles.slider1,'sliderstep',slider_step,'max',ls,'min',1,'Value',10)
% Patients 0,1,5 a=1, 2,3,4 a=2
global Im;
if bd==1 || bd==2
    Im = IMOtempserieExtrac(sizeSl,ic,fc,a,bd); 
end
if bd==3
    Im = SbtempserieExtrac(sizeSl,ic,fc);
end
if bd==4
    Im = CAPserieExtrac(sizeSl,ic,fc);
end
if bd==5
    [Im ls]= KCLserieExtrac(sizeSl,ic,fc,p);
end

 %load ImA
% Im=ImA;
 %ls=24;
 save Im;
%ImMont = reshape(Im(:,:,:),[size(Im,1) size(Im,2) 1 ls]);
%figure(1), montage(abs(ImMont),'DisplayRange',[],'Indices',1:1:ls)
axes(handles.axes1);
imshow(abs(Im(:,:,1)),[])
%hold on
%rectangle('Position',([90 80 89 89]),'EdgeColor','w');hold off
fdct_usfft_path;
% % global h;
% % h = imrect(gca, [90 80 89 89]);
% % addNewPositionCallback(h,@(p1) title(mat2str(p1,3)));
% % fcn = makeConstrainToRectFcn('imrect',get(gca,'XLim'),get(gca,'YLim'));
% % setPositionConstraintFcn(h,fcn);
set(handles.slider1,'Visible','on')
set(handles.pushbutton2,'Visible','on')

marcar(handles);





% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
    set(handles.popupmenu4,'Visible','on')
    set(handles.uipanel1,'Visible','on')
    set(handles.slider2,'Visible','on')
    set(handles.slider3,'Visible','on')
    set(handles.axes2,'Visible','on')
    set(handles.axes3,'Visible','on')
    mostrar(handles);
    global proc;
    proc=1;
   % temporal(1,handles);
    %wavcontinuos(handles);

    
    % hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on selection change in popupmenu4.
function popupmenu4_Callback(hObject, eventdata, handles)
    global t;
    t=get(hObject,'Value');
    global val;
    val=t;
    temporal(t,handles);


% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu4 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu4


% --- Executes during object creation, after setting all properties.
function popupmenu4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
    if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
        set(hObject,'BackgroundColor','white');
    end


function mostrar(handles)
    global ls;
    global Im;
    global h;
    global b;
    global bd;
    ls=20;
    b=zeros(100,100,ls);
    for i=1:ls
       b(:,:,i)= imresize(Im(:,:,i),[100 100],'bicubic');
    end
    save b b
    ImMont1 = reshape(b(:,:,:),[size(b,1) size(b,2) 1 ls]);
  
    p=[80 125; 160 125]
 
    c1=-(p(1,1)-p(2,1));  
    c2=-(p(1,2)-p(2,2)); 
    m=atand(c2/c1);
    beta=-(90-m);

    Imr=zeros(100,100,ls);
    Imr1=zeros(100,100,ls);
    Imr2=zeros(100,100,ls);
    Imr3=zeros(100,100,ls);

%     col=45;
%     Im=b;
%     k=1;
%     for j=0:359
%         ImrSVM=zeros(80,80,ls);
%         e=1;
%         for i=1:ls
%            ImrSVM(:,:,i) = imrotate(Im(:,:,i),-(j-m),'bicubic','crop'); %rotate I (90-m)degrees clockwise
%         end
%         I= createIt(ImrSVM,'col',col);   
%         ItkSVMP(:,:,k)= I;%imresize(I,[40 20],'bicubic');        
%         k=k+1;
%     end
    
    tic
    cuts=360;
    ori=1;
    %for j=60:60:cuts   para cuboids
    for j=1:cuts        
        l=1;
        for i=1:ls 
            f=extract(Im,i,j,2);             %% 1 radial, 2 diametral
            %f2=extract2(Im,i,j,1);           %cuboids
            %size(f2)            %cuboids
            temp(:,l,j)=f; 
            %temp2(:,:,l)=imresize(f2,[40 7],'bicubic');                 %cuboids
            l=l+1;
        end
      %  ItkSVM30(:,:,j)= imresize(temp(:,:,j),[40 20],'bicubic');    %%% diamterial
        %%Cuboid18(:,:,:,ori)= temp2;  %cuboids
        ori=ori+1;
        %ItkSVM27(:,:,j)= imresize(temp(:,:,j),[40 20],'bicubic');    %%% diamterial
        
        ItkSVM29(:,:,j)= imresize(temp(:,:,j),[90 20],'bicubic');    %%% radial
        %ItkSVM19(:,:,j)= imresize(temp(:,:,j),[40 30],'bicubic');    %%% radial
        %ItkSVM1(:,:,j)= temp(:,:,j);    %%% radial
        
        
    end
    toc
    
    %save /home/mantilla/Documents/Tesis/Software/LCKSVD/sharingcode-LCKSVD/RadialProfiles2/Basal/ItkSVM30 ItkSVM30; 
    %save /home/mantilla/Documents/Tesis/Software/LCKSVD/sharingcode-LCKSVD/Simul/Medial/ItkSVM1 ItkSVM1 
    %save /home/mantilla/Documents/Tesis/Software/LCKSVD/sharingcode-LCKSVD/RadialProfiles4/Medial/Cuboid18 Cuboid18; 
    
    save /home/mantilla/Documents/Tesis/Software/LCKSVD/sharingcode-LCKSVD/DiametralProfiles/Medial/ItkSVM29 ItkSVM29;
    %save ./RadialProfiles2/Apical/ItkSVM19 ItkSVM19;
    %save ./RadialProfiles2/Basal/ItkSVB19 ItkSVB19;
    %save ./RadialProfiles2/Basal/ItkSVB19 ItkSVB19;
    
% %     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FOURIER
% %     for j=1:k-1
% %        ItkSVMFFT2D14(:,:,j)=fftshift(fft2(ItkSVM14(:,:,j)));
% %        ItkSVMFFT14(:,:,j)=fftshift(fft(ItkSVM14(:,:,j),[],1),1);
% %     end
% %     save ItkSVMFFT14;
% %     save ItkSVMFFT2D14;
% %     
% % %     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% WAVELET
% % %     wname='db4';
% % %     scales=1:100
% % %     for j=1:k-1
% % %         ItkSVMWAV(:,:,j) = cwt2D(ItkSVM(:,:,j),wname,20,0);
% % %     end
% % %     save ItkSVMWAV;
% % %     %%%%%%%%%%%%%%%%%%%%%%%%%%

    Im=b;
    m=0;
    for i=1:ls
       Imr(:,:,i) = imrotate(Im(:,:,i),-(90-m),'bicubic','crop'); %rotate I (90-m)degrees clockwise
       Imr1(:,:,i) = imrotate(Im(:,:,i),-(45-m),'bicubic','crop'); %rotate I (90-m)degrees clockwise
       Imr2(:,:,i) = imrotate(Im(:,:,i),-(135-m),'bicubic','crop'); %rotate I (90-m)degrees clockwise
       Imr3(:,:,i) = Im(:,:,i);    
    end


    global It;
    global It1;
    global It2;
    global It3;
    col=50;
    It = createIt(Imr,'col',col);
    It1 = createIt(Imr1,'col',col);
    It2 = createIt(Imr2,'col',col);
    It3 = createIt(Imr3,'col',col);

    axes(handles.axes2);
    imshow(b(:,:,1),[])
    %save It;
    %p=ginput(2);
    %p=[90 125; 180 125]
    h=line([p(1,1) p(2,1)],[p(1,2) p(2,2)]);

% %     line([col col],[0 90]);
% %     line([0 90],[col col]);
% %     line([0 90],[0 90]);
% %     line([0 90],[90 0]);
    set(handles.axes3,'Visible','on')
    set(handles.pushbutton2,'Visible','off')
    set(handles.popupmenu4,'Visible','on')

    slider_step(1) = 1/(ls);
    slider_step(2) = 1/(ls);
    set(handles.slider2,'sliderstep',slider_step,'max',ls,'min',1,'Value',10)

    slider_step(1) = 1/(80);
    slider_step(2) = 1/(80);
    set(handles.slider3,'sliderstep',slider_step,'max',80,'min',1,'Value',10)


function mostrar2(handles)
global b;
global t;
axes(handles.axes2);
imshow(b(:,:,t),[])
col=50;
line([col col],[0 100]);
line([0 100],[col col]);
line([0 100],[0 100]);
line([0 100],[100 0]);


function temporal(va,handles)
global It;
global It1;
global It2;
global It3;
global t;
global hor;
axes(handles.axes3);
cla;
axes(handles.axes3);
if (va==1)
imshow(It,[]); 

end
if (va==2)
imshow(It1,[]); 
It=It1;
end
if (va==3)
imshow(It2,[]); 
It=It2;
end
if (va==4)
imshow(It3,[]); 
It=It3;
end
t
line([t t],[0 100]);
line([0 100],[hor hor]);
resaltar(handles);



function transformadas(handles)
global It;
global It1;
global It2;
global It3;
global Imrtt2DA;
global nx1;
global ny1;
global ins;

Imrt=It;
[nx1 ny1]=size(Imrt);
It=It;
% Calcula transformada

zeropadded=0;
if zeropadded==0
    axx=ls;
    axy=80;
else
    df=0.08;
    axx=128;
    axy=128;   
end

fs=10;
ts=1/fs;

if zeropadded==0
    Imrtt=fft(Imrt,[],2);
    Imrttv=fft(Imrt,[],1);  % fft a lo largo de las columnas (=fy)
    Imrtt2D=fft2(Imrt);
else
    Imrtt=fftseq(Imrt,ts,df,2);  % fft a lo largo de las columnas (=ft)
    Imrttv=fftseq(Imrt,ts,df,1);
    Imrtt2D=fftseq(Imrt,ts,df,3);
end
ImrttA=fftshift(Imrtt,2);
ImrttvA=fftshift(Imrttv,1);
Imrtt2DA=fftshift(Imrtt2D);

% extrayendo senales 1D de la imagen
global hor;
global t;
k=1;

nn=max(abs(ImrttA(:)));
mm=max(abs(Imrt(:)));
axes(handles.axes4);
f=hor+1;
s=Imrt(f,:);   
st=ImrttA(f,:);
plot(s,'lineWidth',2)
set(handles.axes4,'YLim',[0 mm])
axes(handles.axes5);
plot(abs(st),'lineWidth',2)
set(handles.axes5,'YLim',[0 nn])

k=k+1;
nn=max(abs(ImrttvA(:)));
mm=max(abs(Imrt(:)));
    c=t;
    s=Imrt(:,c); 
    st=ImrttvA(:,c);
    axes(handles.axes6);
    plot(s,'lineWidth',2)
    set(handles.axes6,'YLim',[0 mm])
    axes(handles.axes7);
    plot(abs(st),'lineWidth',2)
  
    mag=max(st);
    set(handles.axes7,'YLim',[0 nn])

nn=max(abs(Imrtt2DA(:)));
mm=max(abs(Imrtt2DA(:)));

 ft=Imrtt2DA(f,:);
 fs=Imrtt2DA(:,c);
 axes(handles.axes8);
 plot(abs(ft),'lineWidth',2);
 set(handles.axes8,'YLim',[0 mm]);
 axes(handles.axes9);
 plot(abs(fs),'lineWidth',2)
 set(handles.axes9,'YLim',[0 mm]); 

 axes(handles.axes10);
imshow(log(abs(ImrttA)+1),[]), title('1D - ft')%, colormap jet
 axes(handles.axes11);
imshow(log(abs(ImrttvA)+1),[]), title('1D - fy')%, colormap jet
 axes(handles.axes12);
imshow(log(abs(Imrtt2DA)+1),[]), title('2D')%, colormap jet

 
 
% --- Executes on slider movement.
function slider2_Callback(hObject, eventdata, handles)
global val;
global t;
t=get(hObject,'Value');
%get(hObject,'Max')-
t=round(t);
%hor=get(hObject,'Max')-round(hor);

    mostrar2(handles);
    val=get(handles.popupmenu4,'Value');
    temporal(val,handles);
    transformadas(handles);
  %  wavcontinuos(handles);

    
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider3_Callback(hObject, eventdata, handles)

global val;
global hor;
hor=get(hObject,'Value');
%get(hObject,'Max')-

hor=get(hObject,'Max')-round(hor);

    mostrar2(handles);
    val=get(handles.popupmenu4,'Value');
    temporal(val,handles);
    transformadas(handles);
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


function wavcontinuos(handles)
global It;
 global t;
global ins;  
global Sca;  
 axes(handles.axes13);
 plot(It(:,t));
global v;
 axes(handles.axes14);

 scales = 1:1:200;
 v=get(handles.popupmenu7,'Value');
switch v
    case 1 
        wname='gaus4';
    case 2 
        wname='haar';
    case 3 
        wname='db4';
    case 4 
        wname='shan1-1.5';
    case 5 
        wname='dmey';
    case 6 
        wname='cmor1-1.5';        
end

 CWTcoeffs = cwt(It(:,t),scales,wname); %gaus4
 %CWTcoeffs = cwt2D(fft2(It),'gaussx',1,0); %gaus4
 %size(CWTcoeffs)
 %figure(697), yashow(CWTcoeffs);
 imagesc(size(It(:,t)),scales,abs(CWTcoeffs))%,colormap jet; 

for i=1:2
t=ins(i);
h = spectrum.welch;
Hpsd = psd(h,It(:,t),'Fs',500);
figure(11),
hLIN = plot(Hpsd);
xdata = get(hLIN,'XData');
ydata = get(hLIN,'ydata');
[dummy,idxMax] = max(ydata);
FreqMax = xdata(idxMax);
hold on
ylim = get(gca,'YLim');
plot([FreqMax,FreqMax],ylim,'m--');
Frq=500;
TAB_Sca2Frq = scal2frq(scales,wname,1/Frq);
[za,idxSca] = min(abs(TAB_Sca2Frq-FreqMax));
Sca = scales(idxSca);
end
 axes(handles.axes14);
 hold on
 plot([1 size(CWTcoeffs,2)],[Sca Sca],'Color','m','LineWidth',2);
 colorbar('vertical');

% % figure(78),subplot(5,1,1),plot(CWTcoeffs(Sca,:));
% % hold on
% % subplot(5,1,2),plot(CWTcoeffs(1,:));
% % hold on
% % subplot(5,1,3),plot(CWTcoeffs(10,:));
% % hold on
% % subplot(5,1,4),plot(CWTcoeffs(50,:));
% % hold on
% % subplot(5,1,5),plot(CWTcoeffs(80,:));
% % hold on


% figure(4587),subplot(5,1,1),plot(CWTcoeffs(:,1))
% figure(4587),subplot(5,1,2),plot(CWTcoeffs(:,5))
% figure(4587),subplot(5,1,3),plot(CWTcoeffs(:,13))
% figure(4587),subplot(5,1,4),plot(CWTcoeffs(:,65))
% figure(4587),subplot(5,1,5),plot(CWTcoeffs(:,90))



function initialize(handles,x,y,z)
[ic fc p a cr pac ins]=coupe(x,y,z);
s=[];
for i=1:pac(x)
    s=[s;i];
end
set(handles.popupmenu2,'String','');
set(handles.popupmenu2,'String',num2str(s));
set(handles.popupmenu3,'String','');
set(handles.popupmenu3,'String',num2str(cr));







        


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
transforms(handles);
compare(handles);
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


function transforms(handles)
global Imrtt2DA;
global nx1;
global ny1;

[nx,ny] = size(Imrtt2DA);
IMSIZE = nx*ny
pfilt = '9-7';
dfilt = 'pkva';
nlevs = [0, 0, 4, 4, 5]; 
%%%%%%%%%%%%%%%%%%%%%TRANSFORMADAS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Imrtt2DA=imresize(Imrtt2DA,[256 256],'bicubic');
CC=ifft2(ifftshift(Imrtt2DA));

IMG_dct = dct2(CC);%(Imrt);
IMG_d = D(CC);%(Imrt);
CC=imresize(CC,[256 256],'bicubic');
imgtemp=CC;
IMG_wavSym = FWT2_PO(imgtemp,3,MakeONFilter('Symmlet',8));
IMG_wavDau = FWT2_PO(imgtemp,3,MakeONFilter('Daubechies',4));
IMG_wavCoi = FWT2_PO(imgtemp,3,MakeONFilter('Coiflet',5));
IMG_wavHar = FWT2_PO(imgtemp,3,MakeONFilter('Haar'));

Im_Curv = fdct_usfft(double(imgtemp),0);
ImCont = pdfbdec(imgtemp, pfilt, dfilt, nlevs);
[nx,ny] = size(Imrtt2DA);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(4001), subplot(2,4,1), imshow(log(abs(IMG_wavHar)+1),[]), title('Haar');%, colormap jet
figure(4001), subplot(2,4,2), imshow(log(abs(IMG_wavSym)+1),[]), title('Symlet');%, colormap jet
figure(4001), subplot(2,4,3), imshow(log(abs(IMG_wavDau)+1),[]), title('Daub');%, colormap jet
figure(4001), subplot(2,4,4), imshow(log(abs(IMG_wavCoi)+1),[]), title('Coiflet');%, colormap jet
figure(4001), subplot(2,4,5), imshow(log(abs(IMG_dct)+1),[]), title('DCT');%, colormap jet
Ci = fdct_usfft_dispcoef(Im_Curv);
figure(4001), subplot(2,4,6), imshow(log(abs(Ci)+1),[]), title('Curvelet');%, colormap jet
figure(4001), subplot(2,4,7), showpdfb(ImCont) ; title('Contourlet');%, colormap jet




idx_tt2D = sort(abs(Imrtt2DA(:)),1,'descend');
idx_dct = sort(abs(IMG_dct(:)),1,'descend');
idx_d = sort(abs(IMG_d(:)),1,'descend');
idx_wavSym = sort(abs(IMG_wavSym(:)),1,'descend');
idx_wavDau = sort(abs(IMG_wavDau(:)),1,'descend');
idx_wavHaar = sort(abs(IMG_wavHar(:)),1,'descend');
idx_wavCoif = sort(abs(IMG_wavCoi(:)),1,'descend');
[cT, sT] = pdfb2vec(ImCont);
idx_Cont = sort(abs(cT(:)),1,'descend');




cfs =[];
for s=1:length(Im_Curv)
  for w=1:length(Im_Curv{s})
    cfs = [cfs; abs(Im_Curv{s}{w}(:))];
  end
end

cfs = sort(cfs); cfs = cfs(end:-1:1);

figure(1100), subplot(2,5,1), plot(idx_tt2D),title('Fourier');
%axis([0 3000 0 500]);
figure(1100), subplot(2,5,2), plot(idx_dct),title('DCT');
%axis([0 3000 0 500]);
figure(1100), subplot(2,5,3), plot(idx_d),title('Finite Dif');
%axis([0 3000 0 500]);
figure(1100), subplot(2,5,4), plot(idx_wavSym),title('Wavelet Symlet');
%axis([0 3000 0 500]);
figure(1100), subplot(2,5,5), plot(idx_wavDau),title('Wavelet Daub4');
%axis([0 3000 0 500]);
figure(1100), subplot(2,5,6), plot(idx_wavHaar),title('Wavelet Haar');
%axis([0 3000 0 500]);
figure(1100), subplot(2,5,7), plot(idx_wavCoif),title('Coiflet');
%axis([0 3000 0 500]);
figure(1100), subplot(2,5,8), plot(cfs),title('Curvelet');
figure(1100), subplot(2,5,9), plot(idx_Cont),title('Contourlet');

    disp('IMSIZE');  
    pctg = floor([0.05]*IMSIZE);
    pctg1=0.05;   
    % threshold FFT coefficients   
    thresh = idx_tt2D(pctg);    
    tmp = Imrtt2DA;
    tmp(find(abs(tmp)<thresh))=0;
    disp('Coeff Fourier'); size(tmp)
    disp('Coeff Fourier >0'); sum(tmp(:) ~= 0)
    rec_fft = ifft2(ifftshift(tmp));
    
    % threshold dctT coefficients    
    thresh = idx_dct(pctg);
    tmp = IMG_dct;
    tmp(find(abs(tmp)<thresh))=0;
    disp('Coeff DCT'); size(tmp)    
    disp('Coeff DCT >0'); sum(tmp(:) ~= 0)    
    rec_dct = idct2(tmp);
    
    % threshold Finite Difference coefficients    
    thresh = idx_d(pctg);    
    tmp = IMG_d;
    tmp(find(abs(tmp)<thresh))=0;
    disp('Finite Dif'); size(tmp)
    disp('Coeff Fourier >0'); sum(tmp(:) ~= 0)    
    rec_d = invD(tmp,[nx,ny]);
    
    IMSIZE=256*256;
    pctg = floor([0.05]*IMSIZE);
    % threshold Wavelet Symlet coefficients    
    thresh = idx_wavSym(pctg);    
    tmp = IMG_wavSym;
    tmp(find(abs(tmp)<thresh))=0;
    disp('Coeff Symlet'); size(tmp)
    disp('Coeff Fourier >0'); sum(tmp(:) ~= 0)    
    sum(tmp(:) == 0) 
    rec_wavSym = IWT2_PO(tmp,3,MakeONFilter('Symmlet',8));  
    
    % threshold Wavelet Daubechies coefficients    
    thresh = idx_wavDau(pctg);    
    tmp = IMG_wavDau;

    tmp(find(abs(tmp)<thresh))=0;
    disp('Coeff Daube 4'); size(tmp)
    disp('Coeff Fourier >0'); sum(tmp(:) ~= 0)    
    rec_wavDau = IWT2_PO(tmp,3,MakeONFilter('Daubechies',4));  
    
    % threshold Wavelet Haar coefficients    
    thresh = idx_wavHaar(pctg);    
    tmp = IMG_wavHar;
    tmp(find(abs(tmp)<thresh))=0;
    disp('Coeff Haar'); size(tmp)
    disp('Coeff Fourier >0'); sum(tmp(:) ~= 0)    
    rec_wavHar = IWT2_PO(tmp,3,MakeONFilter('Haar'));  
    
    % threshold Wavelet Coiflet coefficients  
    thresh = idx_wavCoif(pctg);    
    tmp = IMG_wavCoi;
    tmp(find(abs(tmp)<thresh))=0;
    disp('Coeff Coifl'); size(tmp)
    disp('Coeff Fourier >0'); sum(tmp(:) ~= 0)    
    rec_wavCoif = IWT2_PO(tmp,3,MakeONFilter('Coiflet',5));  

    disp('CURVELET')
    length(cfs)
    sum(cfs(:) ~= 0)
    nb = round(pctg1*IMSIZE);%length(cfs));
    cutoff = cfs(nb);
    % Set small coefficients to zero Curvelet
    Im_Curvt=Im_Curv;
    cont=0;
    for s=1:length(Im_Curvt)
        for w=1:length(Im_Curvt{s})
        Im_Curvt{s}{w} = Im_Curvt{s}{w} .* (abs(Im_Curvt{s}{w})>cutoff);
        end
    end    

    rec_Curv =ifdct_usfft(Im_Curvt,0);
    cfs1 =[];
    for s=1:length(Im_Curvt)
       for w=1:length(Im_Curvt{s})
            cfs1 = [cfs1; abs(Im_Curvt{s}{w}(:))];
       end
    end
    
    disp('Coeff Curvelet'); size(rec_Curv)
    disp('Coeff Curvelet >0'); sum(cfs1(:) ~= 0)    
    sum(cfs(:) ~= 0) 
    %oo=round(size(cT(:))*0.0001);
    thresh = idx_Cont(pctg);
    tmp = cT(:);
    size(tmp)
    tmp(find(abs(tmp)<thresh))=0;
    yT = vec2pdfb(tmp, sT);
    recCont = pdfbrec(yT, pfilt, dfilt);
    disp('Coeff Contourlet'); size(recCont)
    disp('Coeff Conteroulet >0'); sum(tmp(:) ~= 0) 
 
    
    ps=[];
    
iifft2=ifft2(ifftshift(Imrtt2DA));
%iifft2=imcrop(iifft2,[0 0 nx1 ny1]);
%rec_fft=imcrop(rec_fft,[0 0 nx1 ny1]);

ps(1)=psnr(iifft2,rec_fft);
figure(6664),subplot(2,9,1),imshow(iifft2,[]),title('100% FFT')
figure(6664),subplot(2,9,10),imshow(rec_fft,[]),title('10% FFT ');
mse(1) = sum( sum( (rec_fft - double(iifft2)).^2 ) );
mse(1) = mse(1) / prod(size(iifft2));


dct=idct2(IMG_dct);
%dct=imcrop(dct,[0 0 ny1 nx1]);
%rec_dct=imcrop(rec_dct,[0 0 ny1 nx1]);
ps(2)=psnr(dct,rec_dct);
figure(6664),subplot(2,9,2),imshow(dct,[]),title('100% dct')
figure(6664),subplot(2,9,11),imshow(rec_dct,[]),title('10% dct');
mse(2) = sum( sum( (rec_dct - double(dct)).^2 ) );
mse(2) = mse(2) / prod(size(dct));



dct=invD(IMG_d,[nx,ny]);
%dct=imcrop(dct,[0 0 ny1 nx1]);
%rec_d=imcrop(rec_d,[0 0 ny1 nx1]);
ps(3)=psnr(dct,rec_d);
figure(6664),subplot(2,9,3),imshow(dct,[]),title('100% fin diff')
figure(6664),subplot(2,9,12),imshow(rec_d,[]),title('10% fin diff');
mse(3) = sum( sum( (rec_d - double(dct)).^2 ) );
mse(3) = mse(3) / prod(size(dct));


wav=IWT2_PO(IMG_wavSym,3,MakeONFilter('Symmlet',8));  
%wav = imresize(wav, [nx ny]);
%rec_wavSym = imresize(rec_wavSym, [nx ny]);
%wav=imcrop(wav,[0 0 ny1 nx1]);
%rec_wavSym=imcrop(rec_wavSym,[0 0 ny1 nx1]);
ps(4)=psnr(wav,rec_wavSym);
figure(6664),subplot(2,9,4),imshow(wav,[]),title('100% Symlet 8')
figure(6664),subplot(2,9,13),imshow(rec_wavSym,[]),title('10% Symlet 8');
mse(4) = sum( sum( (rec_wavSym - double(wav)).^2 ) );
mse(4) = mse(4) / prod(size(wav));


wav=IWT2_PO(IMG_wavDau,3,MakeONFilter('Daubechies',4));  
%wav = imresize(wav, [nx ny]);
%rec_wavDau = imresize(rec_wavDau, [nx ny]);
%wav=imcrop(wav,[0 0 ny1 nx1]);
%rec_wavDau=imcrop(rec_wavDau,[0 0 ny1 nx1]);
ps(5)=psnr(wav,rec_wavDau);
figure(6664),subplot(2,9,5),imshow(wav,[]),title('100% Daubechies 4')
figure(6664),subplot(2,9,14),imshow(rec_wavDau,[]),title('10% Daubechies 4');
mse(5) = sum( sum( (rec_wavDau - double(wav)).^2 ) );
mse(5) = mse(5) / prod(size(wav));


wav=IWT2_PO(IMG_wavHar,3,MakeONFilter('Haar'));  
%wav = imresize(wav, [nx ny]);
%rec_wavHar = imresize(rec_wavHar, [nx ny]);
%wav=imcrop(wav,[0 0 ny1 nx1]);
%rec_wavHar=imcrop(rec_wavHar,[0 0 ny1 nx1]);
ps(6)=psnr(wav,rec_wavHar);
figure(6664),subplot(2,9,6),imshow(wav,[]),title('100% Haar')
figure(6664),subplot(2,9,15),imshow(rec_wavHar,[]),title('10% Haar');
mse(6) = sum( sum( (rec_wavHar - double(wav)).^2 ) );
mse(6) = mse(6) / prod(size(wav));



wav=IWT2_PO(IMG_wavCoi,3,MakeONFilter('Coiflet',5));  
%wav = imresize(wav, [nx ny]);
%rec_wavHar = imresize(rec_wavHar, [nx ny]);
%wav=imcrop(wav,[0 0 ny1 nx1]);
%rec_wavCoif=imcrop(rec_wavCoif,[0 0 ny1 nx1]);
ps(7)=psnr(wav,rec_wavCoif);
figure(6664),subplot(2,9,7),imshow(wav,[]),title('100% Coiflet 5')
figure(6664),subplot(2,9,16),imshow(rec_wavCoif,[]),title('10% Coifet 5');
mse(7) = sum( sum( (rec_wavCoif - double(wav)).^2 ) );
mse(7) = mse(7) / prod(size(wav));



curv=ifdct_usfft(Im_Curv,0);
a=real(curv);%(1:nx1,1:ny1));
b=real(rec_Curv);%(1:nx1,1:ny1));
a(1:5,1:5)
ps(8)=psnr(a,b);
figure(6664),subplot(2,9,8),imshow(mat2gray(a)),title('100% Curvelet'),set(gca,'xtick',[]),set(gca,'ytick',[]), box off
figure(6664),subplot(2,9,17),imshow(mat2gray(b)),title('10% Curvelet '),set(gca,'xtick',[]), set(gca,'ytick',[]),box off;
mse(8) = sum( sum( (b - double(a) ).^2 ) );
mse(8) = mse(8) / prod(size(a));

y = vec2pdfb(cT, sT);
cim = pdfbrec(y, pfilt, dfilt);
%cim=imcrop(cim,[0 0 ny1 nx1]);
%recCont=imcrop(recCont,[0 0 ny1 nx1]);
cim(1:5,1:5)
recCont(1:5,1:5)
ps(9)=psnr(cim,recCont);
figure(6664),subplot(2,9,9),imshow(cim,[]),title('100% Contourlet')
figure(6664),subplot(2,9,18),imshow(recCont,[]),title('10% Contourlet');

mse(9) = sum( sum( (recCont - double(cim)).^2 ) );
mse(9) = mse(9) / prod(size(cim));
ps
mse
t=[1 2 3 4 5 6 7 8 9]
%t=['FFT' 'DCT' 'FD' 'Symlet8' 'Daub16' 'Haar' 'Curvelet'];
figure(151),subplot(1,2,1),plot(ps),title('PSNR (FFT - DCT - FD- Symlet8- Daub4 - Haar - Coiflet - Curvelet - Contourlet)')
figure(151),subplot(1,2,2),plot(mse),title('MSE (FFT - DCT - FD- Symlet8- Daub4 - Haar - Coiflet - Curvelet - Contourlet)');


function resaltar(handles)
% % global It;
% % mat=It;
% % [ni nj]=size(mat);
% % [m y]=max(mat(:,1))
% % y=y+1;
% % u=1;
% % v=1;
% % for j=1:1
% %      
% %     val=mat(ni/2)-1;
% %     for i=y+1:1:ni-1        
% %         if(mat(i,1)<mat(i+1,1) && u==1)
% %             pos1=i;
% %             u=0;
% %             break;
% %         end
% %     end
% %     val=mat(ni/2)-1;    
% %     for i=y-1:-1:2        
% %         if(mat(i,1)<mat(i-1,1) && v==1)
% %             pos2=i;
% %             v=0;
% %             break;
% %         end
% %     end
% % end     
% % val
% % pos1
% % mat(pos2,1)
% % pos2
% % mat(pos1,1)
% % 
% % mat(:,1)
% % 
% % axes(handles.axes3);
% % line([1 1],[ni-pos2 ni-pos1]);
% % line([1 10],[15 50]);



function compare(handles)
global It;
global It1;
global It2;
global It3;
global Imrtt2DA;
global nx1;
global ny1;
global ins;

Imrt=It;
[nx1 ny1]=size(Imrt);
It=It;
% Calcula transformada

zeropadded=0;
if zeropadded==0
    axx=ls;
    axy=90;
else
    df=0.08;
    axx=128;
    axy=128;   
end

fs=10;
ts=1/fs;
paint(It,1);
paint(It1,2);
paint(It2,3);
paint(It3,4);
% % wavcontinuos2(It,1);
% % wavcontinuos2(It1,2);
% % wavcontinuos2(It2,3);
% % wavcontinuos2(It3,4);


function paint(Imrt,a)
global ins;
Imrt=imresize(Imrt,[256 256],'bicubic');
zeropadded=0;
if zeropadded==0
    Imrtt=fft(Imrt,[],2);
    Imrttv=fft(Imrt,[],1);  % fft a lo largo de las columnas (=fy)
    Imrtt2D=fft2(Imrt);
else
    Imrtt=fftseq(Imrt,ts,df,2);  % fft a lo largo de las columnas (=ft)
    Imrttv=fftseq(Imrt,ts,df,1);
    Imrtt2D=fftseq(Imrt,ts,df,3);
end
ImrttA=fftshift(Imrtt,2);
ImrttvA=fftshift(Imrttv,1);
Imrtt2DA=fftshift(Imrtt2D);

% extrayendo senales 1D de la imagen
global hor;
global t;

    nn=max(abs(ImrttvA(:)));
    nn=50000;
    st=ImrttvA(:,ins(1));   
     figure(12),subplot(2,4,a),plot(abs(st),'lineWidth',2)   
    mag1=max(abs(st));
    set(gca,'YLim',[0 nn])
     grid on
    hold on
    st=ImrttvA(:,ins(2));   
    mag2=max(abs(st));
    dif=mag1-mag2;
    figure(12),subplot(2,4,a+4),plot(abs(st),'lineWidth',2),xlabel(dif)   
    set(gca,'YLim',[0 nn])

    grid on

    
function wavcontinuos2(It,a)
global ins;
global Sca;
global v;
scales = 1:1:400;
switch v
    case 1 
        wname='gaus4';
    case 2 
        wname='haar';
    case 3 
        wname='db4';
    case 4 
        wname='shan1-1.5';
    case 5 
        wname='dmey';
    case 6 
        wname='cmor1-1.5';        
end
    t=ins(1);
    CWTcoeffs1 = cwt(It(:,t),scales,wname); %gaus4
    figure(33),subplot(2,4,a),imagesc(size(It(:,t)),scales,abs(CWTcoeffs1))%,colormap jet;        
    hold on
    plot([1 size(CWTcoeffs1,2)],[Sca Sca],'Color','m','LineWidth',2);
    t=ins(2);
    CWTcoeffs2 = cwt(It(:,t),scales,wname); %gaus4
    figure(33),subplot(2,4,a+4),imagesc(size(It(:,t)),scales,abs(CWTcoeffs2))%,colormap jet;    
    hold on
    plot([1 size(CWTcoeffs2,2)],[Sca Sca],'Color','m','LineWidth',2);
    re=[1:1:90];
         hold on     
     if(a==1)

    figure(789),plot(re,abs(CWTcoeffs1(Sca,:)),'b',re,abs(CWTcoeffs2(Sca,:)),'b');
     set(gca,'YLim',[-2000 6000])
    hold on
     end
% %      if(a==2)
% %     figure(789),plot(re,CWTcoeffs1(Sca,:),'r',re,CWTcoeffs2(Sca,:),'*');
% %      end
% %      if(a==3)
% %     figure(789),plot(re,CWTcoeffs1(Sca,:),'g',re,CWTcoeffs2(Sca,:),'*');
% %      end
% %      if(a==4)
% %     figure(789),plot(re,CWTcoeffs1(Sca,:),'y',re,CWTcoeffs2(Sca,:),'*');
% %      end
    
   
    
% %     CWTcoeffs3=abs(CWTcoeffs2)-abs(CWTcoeffs1);
% %     figure(33),subplot(3,4,a+8),imagesc(size(It(:,t)),scales,abs(CWTcoeffs3)),colormap jet;    
% %     hold on
    %KMeans(It);
    
    
    
%     h = spectrum.welch;
%     Hpsd = psd(h,It(:,t),'Fs',500);
%     figure(33),
%     hLIN = plot(Hpsd);
%     xdata = get(hLIN,'XData');
%     ydata = get(hLIN,'ydata');
%     [dummy,idxMax] = max(ydata);
%     FreqMax = xdata(idxMax);
%     hold on
%     ylim = get(gca,'YLim');
%     plot([FreqMax,FreqMax],ylim,'m--');
%     Frq=500;
%     
%     TAB_Sca2Frq = scal2frq(scales,wname,1/Frq);
%     [za,idxSca] = min(abs(TAB_Sca2Frq-FreqMax));
%     Sca = scales(idxSca);
% end
    
    


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    


% --- Executes on selection change in popupmenu7.
function popupmenu7_Callback(hObject, eventdata, handles)
wavcontinuos(handles);
% hObject    handle to popupmenu7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu7 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu7


% --- Executes during object creation, after setting all properties.
function popupmenu7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
global Im;
global mr;
global ls;
axes(handles.axes1);
mr=mr+1;
for i=1:ls
     Im(:,:,i) = imrotate(Im(:,:,i),-(mr),'bicubic','crop');
end
imshow(abs(Im(:,:,10)),[])
global h;
h = imrect(gca, [90 80 89 89]);
addNewPositionCallback(h,@(p1) title(mat2str(p1,3)));
fcn = makeConstrainToRectFcn('imrect',get(gca,'XLim'),get(gca,'YLim'));
setPositionConstraintFcn(h,fcn);

% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global Im;
global mr;
global ls;
axes(handles.axes1);
mr=mr+1;
for i=1:ls
     Im(:,:,i) = imrotate(Im(:,:,i),(mr),'bicubic','crop');
end
imshow(abs(Im(:,:,10)),[])
global h;
h = imrect(gca, [90 80 89 89]);
addNewPositionCallback(h,@(p1) title(mat2str(p1,3)));
fcn = makeConstrainToRectFcn('imrect',get(gca,'XLim'),get(gca,'YLim'));
setPositionConstraintFcn(h,fcn);

function marcar(handles)
global Im;
n=4;
order=2;
for i = 1:n		
	p(i,:) = ginput(1);
	hold off;
	plot(p(:,1),p(:,2),'k-','LineWidth',2);
	axis([0 1 0 1]);
   imshow(abs(Im(:,:,1)),[])    
	hold on; box on;
	if (i  >= order) 
		T = linspace(0,1,i-order+2);
		y = linspace(0,1,1000);
		p_spl = DEBOOR(T,p,y,order);
		plot(p_spl(:,1),p_spl(:,2),'b-','LineWidth',4);
        
	end
	plot(p(:,1),p(:,2),'ro','MarkerSize',4,'MarkerFaceColor','r');
end

p2 = ginput(1);
plot(p2(1),p2(2),'ro','MarkerSize',4,'MarkerFaceColor','g');

xc=0;
yc=0;
k=size(p_spl,1);
for j = 1:k
	xc=xc+p_spl(j,1);
    yc=yc+p_spl(j,2);
    
end


x1= min(p(:,1));
y1= min(p(:,2));
x2= max(p(:,1));
y2= max(p(:,2));

h = imrect(gca, [x1 y1 x2-x1 y2-y1]);
c1=((x2-x1)/2)+x1;
c2=((y2-y1)/2)+y1;
a1=p2(1);
a2=c2;

ad=sqrt(  ((c2-a2).^2) + ((c1-a1).^2) );
hyp=sqrt(  ((c2-p2(2)).^2) + ((c1-p2(1)).^2) );

cuad=cuadrante(p2,c1,c2);

alfa=180*acos(ad/hyp)/pi;
if cuad==2
    alfa=180-alfa;
end
if cuad==3
    alfa=180+alfa;
end
if cuad==4
    alfa=270+alfa;
end

m=alfa-120;

plot(p2(1),c2,'ro','MarkerSize',4,'MarkerFaceColor','g');

r=getPosition(h);

hold on
plot(c1,c2,'ro','MarkerSize',4,'MarkerFaceColor','r');

for i=1:size(Im,3)
    
    t1=imcrop(Im(:,:,i),r);
    t2 = imrotate(t1,-m,'bicubic','crop'); 
    imcT(:,:,i)=t2;
end
Im=imcT;

function cuad=cuadrante(p2,c1,c2)

if p2(2)<c2 && p2(1)>c1
    cuad=1;
end
if p2(2)<c2 && p2(1)<c1
    cuad=2;
end
if p2(2)>c2 && p2(1)<c1
    cuad=3;
end
if p2(2)>c2 && p2(1)>c1
    cuad=4;
end


function tem=extract(imc,i,j,f)
if f==1   %radial
    ang=1;
    t2 = imrotate(imc(:,:,i),-j*ang,'bilinear','crop');     
    a=floor(size(imc,1)/2);
    b=floor(size(imc,2)/2);    
    tem=t2(a,b+1:size(imc,2));
else   %diametral
    ang=1;
    t2 = imrotate(imc(:,:,i),-j*ang,'bilinear','crop');     
    a=floor(size(imc,1)/2);
    b=floor(size(imc,2)/2);    
    tem=t2(a,1:size(imc,2));
end


function tem=extract2(imc,i,j,f)
if f==1   %radial
    ang=1;
    t2 = imrotate(imc(:,:,i),-j*ang,'bilinear','crop');     
    a=floor(size(imc,1)/2);
    b=floor(size(imc,2)/2);    
    size(t2)    
    tem(:,1)=t2(a-3,b+1:size(imc,2));
    tem(:,2)=t2(a-2,b+1:size(imc,2));
    tem(:,3)=t2(a-1,b+1:size(imc,2));
    tem(:,4)=t2(a,b+1:size(imc,2));
    tem(:,5)=t2(a+1,b+1:size(imc,2));
    tem(:,6)=t2(a+2,b+1:size(imc,2));
    tem(:,7)=t2(a+3,b+1:size(imc,2));
    
    figure(2)
    imshow(tem,[])

else   %diametral
    ang=1;
    t2 = imrotate(imc(:,:,i),-j*ang,'bilinear','crop');     
    a=floor(size(imc,1)/2);
    b=floor(size(imc,2)/2);    
    
    
   
    tem(:,1)=t2(a-3,1:size(imc,2));
    tem(:,2)=t2(a-2,  1:size(imc,2));
    tem(:,3)=t2(a-1,1:size(imc,2));
    tem(:,4)=t2(a,1:size(imc,2));
    tem(:,5)=t2(a+1,1:size(imc,2));
    tem(:,6)=t2(a+2,1:size(imc,2));
    tem(:,7)=t2(a+3,1:size(imc,2));
   
    
    
    figure
    imshow(tem,[])

end
