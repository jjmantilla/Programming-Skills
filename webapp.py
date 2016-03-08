from db_marche import Database
from db_marche.process.step_detection import StepDetection
from db_marche.process.pattern import Pattern
import time
from flask import Flask, render_template
import numpy as np
from bokeh.models.widgets import Panel, Tabs,TextInput,Slider,RadioButtonGroup
from bokeh.plotting import figure, gridplot,hplot
from bokeh.resources import CDN
from bokeh.embed import file_html

from bokeh.io import output_file, show, vform

from os.path import join as j
from csv import DictReader
DATA_DIR='/Users/jjmantilla/Documents/CMLA/Course/raw/'
SENSORS = ['Pied Droit', 'Pied Gauche', 'Ceinture', 'Tete']
N_SENSORS = ['2AC', '2B5', '2BB', '2BC']
CAPTOR_ID = '_00B41'


#source = ColumnDataSource(data=dict(tit="bhh"))
app = Flask(__name__)

db=Database(debug=1)
list_exercises = db.get_data()
urls3={}
jex=1
for ex1 in list_exercises:
    urls3[ex1.fname] = '/list2/'+ex1.fname
    jex=jex+1
del(list_exercises)

@app.route('/')
def home():

    return render_template('home.html')



@app.route('/my-link/<s1>')
def my_link(s1):
    ex = db.get_data(fname=s1)[0]
    # patterns = []
    # for foot in range(2):
    #     for st in ex.steps_annotation[foot]:
    #           if st[1]-st[0] < 30:
    #               continue
    #     patterns += [Pattern(dict(coord='RY', l_pat=st[1]-st[0],
    #                                       foot='right' if foot else 'left'),
    #                                  ex.data_sensor[6*foot+4, st[0]:st[1]])]
    #     patterns += [Pattern(dict(coord='AZ', l_pat=st[1]-st[0],
    #                                       foot='right' if foot else 'left'),
    #                                  ex.data_sensor[6*foot+2, st[0]:st[1]])]
    #     patterns += [Pattern(dict(coord='AV', l_pat=st[1]-st[0],
    #                                       foot='right' if foot else 'left'),
    #                                  ex.data_earth[6*foot+2, st[0]:st[1]])]
    # stepDet = StepDetection(patterns=patterns, lmbd=.8, mu=.1)
    # steps, steps_label = stepDet.compute_steps(ex)
    # print('steps: ',steps)


    seg = ex.seg_annotation
    print('segm: ',seg)
    print(ex.DAZ[0][seg[1]:seg[2]].T)

    T = len(ex.DAZ[0][seg[0]:seg[1]])
    t = np.arange(T)/100
    plot = figure(width=350, plot_height=250, title="Aller")
    plot.line(t,ex.DAZ[0][seg[0]:seg[1]])

    T = len(ex.DAZ[0][seg[1]:seg[2]])
    t = np.arange(T)/100
    plot1 = figure(width=350, plot_height=250, title="u-Turn")
    plot1.line(t,ex.DAZ[0][seg[1]:seg[2]])

    T = len(ex.DAZ[0][seg[2]:seg[3]])
    t = np.arange(T)/100
    plot2 = figure(width=350, plot_height=250, title="Return")
    plot2.line(t,ex.DAZ[0][seg[2]:seg[3]])

    p = hplot(plot, plot1, plot2)

    tab1 = Panel(child=p, title="Segmentation")

    tabs = Tabs(tabs=[tab1])
    text_input = TextInput(value=ex.fname, title="Enregistrement: ")
    layout = vform(text_input, tabs)
    html = file_html(layout, CDN, "home2")
    return html





@app.route('/list/<s1>')
def list(s1):
    s=int(s1)
    print("Exercise n: ", s)
    #output_file("home.html")
    exercise = list_exercises[s]
    T = exercise.X.shape[1]
    t = np.arange(T)/100
    plot = figure(width=350, plot_height=250, title="Droit Acceleration X")
    plot.line(t,exercise.get_signal("DAX")[0])
    plot2=figure(width=350, plot_height=250, title="Droit Acceleration Y")
    plot2.line(t,exercise.get_signal("DAY")[0])
    plot3=figure(width=350, plot_height=250, title="Droit Acceleration Z")
    plot3.line(t,exercise.get_signal("DAZ")[0])
    plot4=figure(width=350, plot_height=250, title="Droit Rotation X")
    plot4.line(t,exercise.get_signal("DRX")[0])
    plot5=figure(width=350, plot_height=250, title="Droit Rotation X")
    plot5.line(t,exercise.get_signal("DRY")[0])
    plot6=figure(width=350, plot_height=250, title="Droit Rotation X")
    plot6.line(t,exercise.get_signal("DRZ")[0])
    #p = hplot(plot, plot2)
    p = gridplot([[plot, plot2, plot3], [plot4, plot5, plot6]])
    html = file_html(p, CDN, "home")
    return html


@app.route('/list2/<s1>')
def list2(s1):
    #output_file("home.html")
    #s=int(s1)
    print("Exercise n: ", s1)
    exercise = db.get_data(fname=s1)[0]
    #exercise = list_exercises[s]

    T = exercise.X.shape[1]
    t = np.arange(T)/100

    plot = figure(width=350, plot_height=250, title="Acceleration X")
    plot.line(t,exercise.get_signal("DAX")[0])
    plot2=figure(width=350, plot_height=250, title=" Acceleration Y")
    plot2.line(t,exercise.get_signal("DAY")[0])
    plot3=figure(width=350, plot_height=250, title=" Acceleration Z")
    plot3.line(t,exercise.get_signal("DAZ")[0])
    plot4=figure(width=350, plot_height=250, title=" Rotation X")
    plot4.line(t,exercise.get_signal("DRX")[0])
    plot5=figure(width=350, plot_height=250, title=" Rotation Y")
    plot5.line(t,exercise.get_signal("DRY")[0])
    plot6=figure(width=350, plot_height=250, title=" Rotation Z")
    plot6.line(t,exercise.get_signal("DRZ")[0])
    p1 = gridplot([[plot, plot2, plot3], [plot4, plot5, plot6]])
    tab1 = Panel(child=p1, title="Pied Droite")


    plot = figure(width=350, plot_height=250, title="Acceleration X")
    plot.line(t,exercise.get_signal("GAX")[0])
    plot2=figure(width=350, plot_height=250, title=" Acceleration Y")
    plot2.line(t,exercise.get_signal("GAY")[0])
    plot3=figure(width=350, plot_height=250, title=" Acceleration Z")
    plot3.line(t,exercise.get_signal("GAZ")[0])
    plot4=figure(width=350, plot_height=250, title=" Rotation X")
    plot4.line(t,exercise.get_signal("GRX")[0])
    plot5=figure(width=350, plot_height=250, title=" Rotation Y")
    plot5.line(t,exercise.get_signal("GRY")[0])
    plot6=figure(width=350, plot_height=250, title=" Rotation Z")
    plot6.line(t,exercise.get_signal("GRZ")[0])
    p2 = gridplot([[plot, plot2, plot3], [plot4, plot5, plot6]])
    tab2 = Panel(child=p2, title="Pied Gauche")

    plot = figure(width=350, plot_height=250, title="Acceleration X")
    plot.line(t,exercise.get_signal("CAX")[0])
    plot2=figure(width=350, plot_height=250, title=" Acceleration Y")
    plot2.line(t,exercise.get_signal("CAY")[0])
    plot3=figure(width=350, plot_height=250, title=" Acceleration Z")
    plot3.line(t,exercise.get_signal("CAZ")[0])
    plot4=figure(width=350, plot_height=250, title=" Rotation X")
    plot4.line(t,exercise.get_signal("CRX")[0])
    plot5=figure(width=350, plot_height=250, title=" Rotation Y")
    plot5.line(t,exercise.get_signal("CRY")[0])
    plot6=figure(width=350, plot_height=250, title=" Rotation Z")
    plot6.line(t,exercise.get_signal("CRZ")[0])
    p = gridplot([[plot, plot2, plot3], [plot4, plot5, plot6]])
    tab3 = Panel(child=p, title="Ceinture")


    plot = figure(width=350, plot_height=250, title="Acceleration X")
    plot.line(t,exercise.get_signal("TAX")[0])
    plot2=figure(width=350, plot_height=250, title=" Acceleration Y")
    plot2.line(t,exercise.get_signal("TAY")[0])
    plot3=figure(width=350, plot_height=250, title=" Acceleration Z")
    plot3.line(t,exercise.get_signal("TAZ")[0])
    plot4=figure(width=350, plot_height=250, title=" Rotation X")
    plot4.line(t,exercise.get_signal("TRX")[0])
    plot5=figure(width=350, plot_height=250, title=" Rotation Y")
    plot5.line(t,exercise.get_signal("TRY")[0])
    plot6=figure(width=350, plot_height=250, title=" Rotation Z")
    plot6.line(t,exercise.get_signal("TRZ")[0])
    p = gridplot([[plot, plot2, plot3], [plot4, plot5, plot6]])
    tab4 = Panel(child=p, title="Tête")
    tabs = Tabs(tabs=[ tab1, tab2, tab3, tab4])
    text_input = TextInput(value=exercise.fname, title="Enregistrement: ")
    layout = vform(text_input, tabs)

    #show(layout)
    html = file_html(layout, CDN, "home")
    return html




def load_raw_course(fn):
    scale_A=1
    scale_R=1
    delimiter='\t'
    X=[]
    fps = []
    for ns in N_SENSORS:
        fname = fn+ CAPTOR_ID+ns+'.txt'
        print(fname)
        res = []
        with open(j(DATA_DIR, fname)) as f:
            t=f.readline()
            l_spr = f.readline()
            f.readline()
            f.readline()

            # Parse categorie name (except sampling rate)
            for row in DictReader(f, delimiter=delimiter):
                res.append([float(row['Acc_X'])*scale_A,
                            float(row['Acc_Y'])*scale_A,
                            float(row['Acc_Z'])*scale_A,
                            float(row['Gyr_X'])*scale_R,
                            float(row['Gyr_Y'])*scale_R,
                            float(row['Gyr_Z'])*scale_R])
        X += [np.transpose(res)]
    #assert((np.array(fps) == fps[0]).all())
    return X


@app.route('/course/<files>')
def course(files):
    #output_file("home.html")
    start = time.clock()



    i=0
    for ir in range(5):
        r=files + str(i+1)
        print(r)
        Xr=load_raw_course(r)
        T = len(Xr[0][0][:])
        #print(Xr[0][0][:])
        t = np.arange(T)
        #print(len(Xr[0][0][:]))
        plot1 = figure(width=350, plot_height=250, title="Acceleration  X ")
        plot1.line(t,Xr[0][0][:])
        plot2 = figure(width=350, plot_height=250, title="Acceleration Y " )
        plot2.line(t,Xr[0][1][:])
        plot3 = figure(width=350, plot_height=250, title="Acceleration Z")
        plot3.line(t,Xr[0][2][:])
        plot4 = figure(width=350, plot_height=250, title="Rotation X")
        plot4.line(t,Xr[0][3][:])
        plot5 = figure(width=350, plot_height=250, title="Rotation Y")
        plot5.line(t,Xr[0][4][:])
        plot6 = figure(width=350, plot_height=250, title="Rotation Z")
        plot6.line(t,Xr[0][5][:])
        p = gridplot([[plot1, plot2, plot3], [plot4, plot5, plot6]])
        tab1 = Panel(child=p, title="Tête")
        T = len(Xr[1][0][:])
        t = np.arange(T)/100
        plot1 = figure(width=350, plot_height=250, title="Acceleration X" )
        plot1.line(t,Xr[1][0][:])
        plot2 = figure(width=350, plot_height=250, title="Acceleration Y")
        plot2.line(t,Xr[1][1][:])
        plot3 = figure(width=350, plot_height=250, title="Acceleration Z")
        plot3.line(t,Xr[1][2][:])
        plot4 = figure(width=350, plot_height=250, title="Rotation X")
        plot4.line(t,Xr[1][3][:])
        plot5 = figure(width=350, plot_height=250, title="Rotation Y")
        plot5.line(t,Xr[1][4][:])
        plot6 = figure(width=350, plot_height=250, title="Rotation Z")
        plot6.line(t,Xr[1][5][:])
        p2 = gridplot([[plot1, plot2, plot3], [plot4, plot5, plot6]])
        tab2 = Panel(child=p2, title="Ceinture")
        T = len(Xr[2][0][:])
        t = np.arange(T)
        plot1 = figure(width=350, plot_height=250, title="Acceleration X")
        plot1.line(t,Xr[2][0][:])
        plot2 = figure(width=350, plot_height=250, title="Acceleration Y")
        plot2.line(t,Xr[2][1][:])
        plot3 = figure(width=350, plot_height=250, title="Acceleration Z")
        plot3.line(t,Xr[2][2][:])
        plot4 = figure(width=350, plot_height=250, title="Rotation X")
        plot4.line(t,Xr[2][3][:])
        plot5 = figure(width=350, plot_height=250, title="Rotation Y")
        plot5.line(t,Xr[2][4][:])
        plot6 = figure(width=350, plot_height=250, title="Rotation Z")
        plot6.line(t,Xr[2][5][:])
        p3 = gridplot([[plot1, plot2, plot3], [plot4, plot5, plot6]])
        tab3 = Panel(child=p3, title="Pied Gauche")
        T = len(Xr[3][0][:])
        t = np.arange(T)
        plot1 = figure(width=350, plot_height=250, title="Acceleration X")
        plot1.line(t,Xr[3][0][:])
        plot2 = figure(width=350, plot_height=250, title="Acceleration Y")
        plot2.line(t,Xr[3][1][:])
        plot3 = figure(width=350, plot_height=250, title="Acceleration Z")
        plot3.line(t,Xr[3][2][:])
        plot4 = figure(width=350, plot_height=250, title="Rotation X")
        plot4.line(t,Xr[3][3][:])
        plot5 = figure(width=350, plot_height=250, title="Rotation Y")
        plot5.line(t,Xr[3][4][:])
        plot6 = figure(width=350, plot_height=250, title="Rotation Z")
        plot6.line(t,Xr[3][5][:])
        p4 = gridplot([[plot1, plot2, plot3], [plot4, plot5, plot6]])
        tab4 = Panel(child=p4, title="Pied Droite")
        tabs = Tabs(tabs=[tab1, tab2 , tab3, tab4])
        i=i+1
        if i==1:
            l1=vform(tabs)
        if i==2:
            l2=vform(tabs)
        if i==3:
            l3=vform(tabs)
        if i==4:
            l4=vform(tabs)
        if i==5:
            l5=vform(tabs)

    ex1 = Panel(child=l1, title="Marche V1:confortable  2min")
    ex2 = Panel(child=l2, title="Marche V2:4km/h 2min")
    ex3 = Panel(child=l3, title="Marche V3:limit 1min")
    ex4 = Panel(child=l4, title="Course V3:marche limit 1min")
    ex5 = Panel(child=l5, title="Course V4:limit 2min")
    tabsE = Tabs(tabs=[ex1, ex2, ex3, ex4, ex5])
    text_input = TextInput(value=files, title="Enregistrement" )
    l=vform(text_input,tabsE)
    stop = time.clock()
    print(stop - start)
    html = file_html(l, CDN, "home")
    return html


urls2 = {
    'MAN-Jua': '/course/MAN-Jua-Yo-',
    'VIE-Ali': '/course/VIE-Ali-Yo-',
    'WAN-Dan': '/course/WAN-Dan-Yo-'

}

@app.route('/Course/')
def patients(): # why was there urls=urls here before?
    return render_template('patientsc.html',urls=urls2)


@app.route('/Marche/')
def patients2(): # why was there urls=urls here before?
    return render_template('patients.html',urls=urls3)


if __name__ == '__main__':
    app.run(debug=True)
