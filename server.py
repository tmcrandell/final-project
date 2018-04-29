import random
import json
from flask import (Flask,
                   request,
                   url_for,
                   render_template)
import requests
import serial

app = Flask(__name__)

@app.route("/")
def home():
    return render_template('home.html')

@app.route("/data.json")
def data():
    try:
        s=serial.Serial("/dev/ttyACM0",timeout=1)
        s.write('a')
        vals=s.readline()
        data=[int(x) for x in vals.split(',')]
        s.close()
    except:
        data=[51,49]
    
    indoor_temp = data[0]
    indoor_humidity = data[1]
    
    payload={'q':'Annapolis','units':'imperial','APPID':'fd62ac498230ff40fa081d310e14b042'} #identifies annapolis as city, and my app id, use imperial units because America
    r=requests.get('https://api.openweathermap.org/data/2.5/weather',params=payload) #sends the request, and saves weather response in r
    r_dict=json.loads(r.text) #creates python dictionary from text response

    #assigns outdoor humidity and temp from dictionary
    outdoor_humidity=r_dict['main']['humidity']
    outdoor_temp=r_dict['main']['temp']
    
    # send the result as JSON
    return json.dumps({
        "indoor_temp": indoor_temp,
        "indoor_humidity": indoor_humidity,
        "outdoor_temp": outdoor_temp,
        "outdoor_humidity": outdoor_humidity})


@app.route("/cheep",methods=['POST'])
def cheep():
    f1=open("./cheeps.log",'a') #open cheep log
    name = request.form['name'] #request the name id from webpage
    message = request.form['message'] #... message id...
    print("got a cheep from [%s]: %s" % (name,message))
    f1.write('['+name+': '+message+']'+'\n')
    f1.close()
    # system time    
    # TODO: display the cheep on the kit LCD
    try:
        s=serial.Serial("/dev/ttyACM0",timeout=1)
        s.write('b') #code that signals cheep
        s.write(name.encode('latin-1'))
        s.write(';') #end name character
        s.write(message.encode('latin-1'))
        s.write(':') #end message character
        s.close()
    except:
        return render_template('error.html') #error page
    
    return render_template('thankyou.html')

@app.route("/test")
def testfunc():
    return "so good"
